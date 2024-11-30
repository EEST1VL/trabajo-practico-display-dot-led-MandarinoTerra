#include <Arduino.h>
#include "encoder.c"
#define set_bit(reg, bit) reg |= (1 << bit)
#define clear_bit(reg, bit) reg &= ~(1 << bit)

int8_t angle = 10;
ISR(INT0_vect) // me interrumpio el PD2
{
    (PIND & 0b00001000) ? angle-- : angle++; // le pregunto el estado al PD3
}

ISR(INT1_vect) // me interrumpio el PD3
{
    (PIND & 0b00000100) ? angle++ : angle--; // le pregunto el estado al PD2
}
int main(void)
{
    initInterrupts();
    sei();
    set_bit(DDRB, PB0);
    set_bit(DDRB, PB1);
    while (1)
    {
        if (angle > 10)
        {
            set_bit(PORTB, PB0);
            angle = 10;
            clear_bit(PORTB, PB1);
        }
        if (angle < 10)
        {
            set_bit(PORTB, PB1);
            clear_bit(PORTB, PB0);
            angle = 10;
        }
    }
}
