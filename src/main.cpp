#include <Arduino.h>

#include "wels.c"

#define set_bit(reg, bit) reg |= (1 << bit)
#define clear_bit(reg, bit) reg &= ~(1 << bit)
uint64_t beats;
uint64_t beats_ini;
enum Matrix
{
    fila1,
    fila2,
    fila3,
    fila4,
    fila5,
    fila6,
    fila7
};
enum Matrix matris = fila4;
uint8_t mux_vec[8] = {
    0b11111111,
    0b01000000,
    0b00100000,
    0b00010000,
    0b00001000,
    0b00000100,
    0b00000010,
    0b00000001

};
uint8_t hola[41] =
    {
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00101110,
        0b00101010,
        0b00111010,
        0b00000000,
        0b00000010,
        0b00000010,
        0b00111110,
        0b00000000,
        0b00100010,
        0b00101010,
        0b00111110,
        0b00000000,
        0b00111100,
        0b00000010,
        0b0000100,
        0b00000010,
        0b00111100,
        0b00000000};
int main()
{
    TCCR1A = 0b00000000; // CTC
    TCCR1B = 0b00001011; // clk/64
    TCCR1C = 0;
    OCR1A = 249;
    TIMSK1 = (1 << OCIE1A);

    sei();

    set_bit(DDRB, PB0); // led 7
    set_bit(DDRB, PB1); // led 8
    set_bit(DDRB, PB2); // led 8

    while (1)
    {
        switch (matris)
        {
        case fila1:
            for (size_t i = 0; i < 40; i++)
            {
                beats_ini = 0b00000001 & (hola[i]);
                beats = beats | (beats_ini << i);
            }
            wels_col(beats);
            wels_fila(mux_vec[1]);
            set_bit(PORTB, PB1);
            clear_bit(PORTB, PB1);
            beats = beats_ini = 0;
            matris = fila2;
            break;
        case fila2:
            for (size_t i = 0; i < 40; i++)
            {
                beats_ini = 1 >> (0b00000010 & (hola[i]));
                beats = beats | (beats_ini << i);
            }
            wels_col(~beats);
            wels_fila(mux_vec[2]);
            set_bit(PORTB, PB1);
            clear_bit(PORTB, PB1);
            beats = beats_ini = 0;
            matris = fila3;
            break;
        case fila3:
            for (size_t i = 0; i < 40; i++)
            {
                beats_ini = (hola[i] >> 2) & 1;
                beats = beats | (beats_ini << i);
            }
            wels_col(beats);
            wels_fila(mux_vec[3]);
            set_bit(PORTB, PB1);
            clear_bit(PORTB, PB1);

            beats = beats_ini = 0;
            matris = fila4;
            break;
        case fila4:
            for (size_t i = 0; i < 40; i++)
            {
                beats_ini = (hola[i] >> 3) & 1;
                beats = beats | (beats_ini << i);
            }
            wels_col(beats);
            wels_fila(mux_vec[4]);
            set_bit(PORTB, PB1);
            clear_bit(PORTB, PB1);

            beats = beats_ini = 0;
            matris = fila5;
            break;
        case fila5:
            for (size_t i = 0; i < 40; i++)
            {
                beats_ini = (hola[i] >> 4) & 1;
                beats = beats | (beats_ini << i);
            }
            wels_col(beats);
            wels_fila(mux_vec[5]);
            set_bit(PORTB, PB1);
            clear_bit(PORTB, PB1);

            beats = beats_ini = 0;
            matris = fila6;
            break;
        case fila6:
            for (size_t i = 0; i < 40; i++)
            {
                beats_ini = (hola[i] >> 5) & 1;
                beats = beats | (beats_ini << i);
            }
            wels_col(beats);
            wels_fila(mux_vec[6]);
            set_bit(PORTB, PB1);
            clear_bit(PORTB, PB1);

            beats = beats_ini = 0;
            matris = fila7;
            break;
        case fila7:
            for (size_t i = 0; i < 40; i++)
            {
                beats_ini = (hola[i] >> 6) & 1;
                beats = beats | (beats_ini << i);
            }
            wels_col(beats);
            wels_fila(mux_vec[7]);
            set_bit(PORTB, PB1);
            clear_bit(PORTB, PB1);

            beats = beats_ini = 0;
            matris = fila1;
            break;
        }
    }
}
ISR(TIMER1_COMPA_vect)
{
}
