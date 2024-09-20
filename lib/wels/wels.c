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
    // Comienza desde el bit más significativo
    for (uint64_t i = 0; i < 40; i++)
    {
        // Extrae el bit en la posición correspondiente
        if ((data & (1ULL << (39 - i))) != 0) // Cambiado para obtener el bit más significativo primero
            set_bit(PORTB, data_pin);
        else
            clear_bit(PORTB, data_pin);

        // Genera un pulso de reloj
        set_bit(PORTB, clk_pin);
        //_delay_ms(250);
        clear_bit(PORTB, clk_pin);
        //_delay_ms(250);
    }
}
//void mostrar_str(char *texto) {}
//
///*
//esta funcion recibe un string y lo convierte en la representacion
// en memoria de los leds que se deben prender en la matrix
//*/
//void text_to_leds(char *texto, uint8_t *led_buff[]) {}
//
///*esta funcion hace el multiplexado de lineas*/
void mux_leds(uint8_t led_buff[], uint8_t hola[])
{
 static uint64_t beats;
 static uint64_t beats_ini;
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
  static enum Matrix matris = fila4;
  switch (matris)
  {
  case fila1:
    for (size_t i = 0; i < 40; i++)
    {
      beats_ini = 0b00000001 & (hola[i]);
      beats = beats | (beats_ini << i);
    }
    wels_col(beats);
    wels_fila(led_buff[1]);
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
    wels_fila(led_buff[2]);
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
    wels_fila(led_buff[3]);
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
    wels_fila(led_buff[4]);
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
    wels_fila(led_buff[5]);
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
    wels_fila(led_buff[6]);
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
    wels_fila(led_buff[7]);
    set_bit(PORTB, PB1);
    clear_bit(PORTB, PB1);
    beats = beats_ini = 0;
    matris = fila1;
    break;
  }
}
/*
esta funcion agarra el vector que me dice que leds prender y envia a los registros una fila

*/

//void shift_line(uint8_t *led_buff[], uint8_t fila)

//{

//}