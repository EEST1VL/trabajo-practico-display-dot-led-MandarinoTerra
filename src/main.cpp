#include <Arduino.h>

#include "wels.c"

#define set_bit(reg, bit) reg |= (1 << bit)
#define clear_bit(reg, bit) reg &= ~(1 << bit)
int n = 65;

int scroll_time = 100;

uint8_t mux_vel;
uint64_t mux_time = 0;
uint8_t led_buff[8] = {

    0b11111111,
    0b00000001,
    0b00000010,
    0b00000100,
    0b00001000,
    0b00010000,
    0b00100000,
    0b01000000,

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

    uint8_t hola[MATRIX_BUFF_LEN] = {0xFF, 0xaa, 0x55, 0x00, 0xFF, 0xaa, 0x55, 0x00, 0xFF, 0xaa, 0x55, 0x00, 0xFF, 0xaa, 0x55, 0x00, 0xFF, 0xaa, 0x55, 0x00, 0xFF, 0xaa, 0x55, 0x00, 0xFF, 0xaa, 0x55, 0x00, 0xFF, 0xaa, 0x55, 0x00, 0xFF, 0xaa, 0x55, 0x00, 0xFF, 0xaa, 0x55, 0x00};

    char str[] = {"hola"};

    uint8_t scroll_pos = 0;

    mostrar_str(&str[0], &hola[0]);

    uint8_t scroll_save;
    while (1)
    {
        if (scroll_time == 0)
        {
            scroll_time = 50;
            scroll_save = hola[0];
            for (size_t i = 0; i < 59; i++)
            {
                hola[i] = hola[i + 1];
            }
            hola[59] = scroll_save;
        }
        mux_leds(&hola[scroll_pos]);
    }
}
ISR(TIMER1_COMPA_vect)
{

    if (scroll_time)
        scroll_time--;
    mux_time++;
    if (mux_time >= 1)
    {

        mux_time = 0;
    }
}
