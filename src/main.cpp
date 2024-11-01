#include <Arduino.h>

#include "wels.c"

#define set_bit(reg, bit) reg |= (1 << bit)
#define clear_bit(reg, bit) reg &= ~(1 << bit)
int n = 65;

int scroll_time = 1000;

uint8_t mux_vel;
uint64_t mux_time = 3;

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

    char str[] = {"18m:14s"};
    while (1)
    {
        str[0] = '3';
        strtupapa(str, &scroll_time);
        str[0] = '4';
        strtupapa(str, &scroll_time);

    }
}
ISR(TIMER1_COMPA_vect)
{
}
