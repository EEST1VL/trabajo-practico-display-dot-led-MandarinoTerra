#include <encoder.h>
#include <Arduino.h>

void initInterrupts(void)
{
  EIMSK |= (1 << INT0);  // habilita interrupcion externa INT0 en PD2
  EIMSK |= (1 << INT1);  // habilita interrupcion externa INT1 en PD3
  EICRA |= (1 << ISC01); // configura flanco ascendente en interrupcion externa INT0
  EICRA |= (1 << ISC11); // configura flanco ascendente en interrupcion externa INT1
}
void timer1(void)
{
  /*
16Mhz/64bit * 249 = 1khz
*/
  TCCR1A = 0b00000000; // CTC
  TCCR1B = 0b00001011; // clk/64
  TCCR1C = 0;
  OCR1A = 249;
  TIMSK1 = (1 << OCIE1A);
}