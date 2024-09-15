#include <wels.h>
#include <Arduino.h>
#define data_pin PB2
#define clk_pin PB0
#define latch_pin PB1
#define set_bit(reg, bit) reg |= (1 << bit)
#define clear_bit(reg, bit) reg &= ~(1 << bit)
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

void wels_fila(uint8_t fila)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if ((fila & 0b0000001) != 0)
      set_bit(PORTB, data_pin);
    else
      clear_bit(PORTB, data_pin);

    fila = fila >> 1;
    set_bit(PORTB, clk_pin);
    //_delay_ms(250);
    clear_bit(PORTB, clk_pin);
    //_delay_ms(250);
  }

}
void wels_col(uint64_t data)
{
  for (uint64_t i = 0; i < 40; i++)
  {
    if ((data & 0b0000001) != 0)
      set_bit(PORTB, data_pin);
    else
      clear_bit(PORTB, data_pin);

    data = data >> 1;
    set_bit(PORTB, clk_pin);
    //_delay_ms(250);
    clear_bit(PORTB, clk_pin);
    //_delay_ms(250);
  }

}
void mostrar_str(char *texto) {}

/*
esta funcion recibe un string y lo convierte en la representacion
 en memoria de los leds que se deben prender en la matrix
*/
void text_to_leds(char *texto, uint8_t *led_buff) {}

/*esta funcion hace el multiplexado de lineas*/
void mux_leds(uint8_t *led_buff) {
  
}
/*
esta funcion agarra el vector que me dice que leds prender y envia a los registros una fila

*/
void shift_line(uint8_t *led_buff, uint8_t fila) {

}