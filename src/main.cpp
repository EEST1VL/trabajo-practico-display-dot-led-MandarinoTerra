#include <Arduino.h>

#include "wels.c"

#define set_bit(reg, bit) reg |= (1 << bit)
#define clear_bit(reg, bit) reg &= ~(1 << bit)
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
        0b11111111,
        0b00000000,
        0b00100100,
        0b00100100,
        0b00111100,
        0b00100100,
        0b00100100,
        0b00000000,

        0b00000000,
        0b00100100,
        0b00100100,
        0b00111100,
        0b00100100,
        0b00100100,
        0b00000000,
        
        0b00000000,
        0b00100100,
        0b00100100,
        0b00111100,
        0b00100100,
        0b00100100,
        0b00000000,
        
        0b00000000,
        0b00100100,
        0b00100100,
        0b00111100,
        0b00100100,
        0b00100100,
        0b00000000,
        
        0b00000000,
        0b00100100,
        0b00100100,
        0b00111100,
        0b00100100,
        0b00100100,
        0b00000000,
        };
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

    int8_t indice = 1;
    while (1)
    {
        if (indice < 8)
        {
            wels_col((uint64_t)(hola[indice])<<32);
            wels_fila( (1<<indice) );

            set_bit(PORTB, latch_pin);
            clear_bit(PORTB, latch_pin);
            indice++;
        }
        else
        {
            indice=1;
            wels_col(hola[indice]);
            wels_fila(mux_vec[indice]);

            set_bit(PORTB, latch_pin);
            clear_bit(PORTB, latch_pin);
        }
    }
}
ISR(TIMER1_COMPA_vect)
{
}
