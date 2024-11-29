#include <Arduino.h>

#include "wels.c"

#define set_bit(reg, bit) reg |= (1 << bit)
#define clear_bit(reg, bit) reg &= ~(1 << bit)
uint32_t seg_st = 0;
uint16_t volt;
int scroll_time = 0;
int main()
{
    adc_init();
    TCCR1A = 0b00000000; // CTC
    TCCR1B = 0b00001011; // clk/64
    TCCR1C = 0;
    OCR1A = 249;
    TIMSK1 = (1 << OCIE1A);
    sei();

    set_bit(DDRB, PB0); // led 8
    set_bit(DDRB, PB1); // led 8
    set_bit(DDRB, PB2); // led 8
    set_bit(DDRB, PB5); // led 8

    char str[50];
    while (1)
    {
        sprintf(&str[0], "%d.%dV  ", volt/1000,volt%1000);
        strtupapa(&str[0], &scroll_time);
        if (seg_st >= 100)
        {
            volt = (uint32_t)adc_read(0)*5000/1024;
            seg_st = 0;
        }
    }
}
ISR(TIMER1_COMPA_vect)
{
    seg_st++;
}
