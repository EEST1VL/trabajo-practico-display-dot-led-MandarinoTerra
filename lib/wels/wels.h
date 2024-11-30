#ifndef __TEST_H_
#define __TEST_H_

#include <Arduino.h>

#ifdef __cplusplus
extern "C"
{
#endif



#define LARGO_VECTOR_SALIDA 180

    void timer1(void);

    void send_fila(uint64_t data);

    void select_fila(uint8_t fila);

    void initInterrupts(void);

    void strtupapa(char *str);

    void mostrar_str(char *texto, uint8_t *bufffer);
    
    void mux_leds(uint8_t hola[]);

#ifdef __cplusplus
}
#endif

#endif //__TEST_H_