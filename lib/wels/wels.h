#ifndef __TEST_H_
#define __TEST_H_

#include <Arduino.h>

#ifdef __cplusplus
extern "C"
{
#endif
//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------

void timer1(void);
void wels_col(uint64_t data);
void wels_fila(uint8_t fila);
/*
char str[20];
strcpy(str,"hola mundo");

sprintf(str,"hola mundo%d",)

str[0]='H';
str[1]='o';
str[2]='l';
str[3]='a';
*/
/*a esta funcion le paso el texto a mostrar y lo convierte y multiplexa en el display*/
void mostrar_str(char* texto);

/*
esta funcion recibe un string y lo convierte en la representacion
 en memoria de los leds que se deben prender en la matrix
*/
void text_to_leds(char* texto, uint8_t *led_buff);


/*esta funcion hace el multiplexado de lineas*/
void mux_leds(uint8_t led_buff[], uint8_t hola[]);
/*
esta funcion agarra el vector que me dice que leds prender y envia a los registros una fila

*/
void shift_line(uint8_t* led_buff, uint8_t fila);


//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------






#ifdef __cplusplus
}
#endif

#endif //__TEST_H_