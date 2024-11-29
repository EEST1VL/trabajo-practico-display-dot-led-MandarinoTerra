#include <Arduino.h>

#include "wels.c"

#define set_bit(reg, bit) reg |= (1 << bit)
#define clear_bit(reg, bit) reg &= ~(1 << bit)

#define boton3 (PIND >> PD4 & 1)
#define boton2 (PIND >> PD3 & 1)
#define boton1 (PIND >> PD2 & 1)

int scroll_time = 1;

void anti_reb1(void);
void anti_reb2(void);
void anti_reb3(void);
void anti_reb4(void);

uint8_t flag_bot1, e_a_b1;
uint8_t flag_bot2, e_a_b2;
uint8_t flag_bot3, e_a_b3;
uint8_t flag_bot4, e_a_b4;

enum sexo_fernandez
{
    seteo,
    star_stop,
    titilar,
    titilarge,
    finazilo
};
enum sexo_fernandez estado = seteo;
uint32_t seg_st = 0;

uint16_t velo = 1000;
uint8_t pausa = 0;
int8_t angle = 10;
int8_t mins = 3, segs = 59, mins_save, segs_save;

ISR(INT0_vect) // me interrumpio el PD2
{
    (PIND & 0b00001000) ? angle-- : angle++; // le pregunto el estado al PD3
}

ISR(INT1_vect) // me interrumpio el PD3
{
    (PIND & 0b00000100) ? angle++ : angle--; // le pregunto el estado al PD2
}

int main()
{
    adc_init();
    TCCR1A = 0b00000000; // CTC
    TCCR1B = 0b00001011; // clk/64
    TCCR1C = 0;
    OCR1A = 249;
    TIMSK1 = (1 << OCIE1A);

    initInterrupts();
    sei();

    set_bit(PORTD, PD5);
    clear_bit(PORTD, PD6);

    clear_bit(PORTB, PB5);
    clear_bit(DDRD, PD2); // boton 1
    set_bit(PORTD, PD2);

    clear_bit(DDRD, PD3); // boton 2
    set_bit(PORTD, PD3);

    clear_bit(DDRD, PD4); // boton 3
    set_bit(PORTD, PD4);

    set_bit(DDRB, PB0); // led 8
    set_bit(DDRB, PB1); // led 8
    set_bit(DDRB, PB2); // led 8
    set_bit(DDRB, PB5); // led 8

    char str[] = {"83m14s "};

    uint8_t titi = 0;

    while (1)
    {
        switch (estado)
        {
        case seteo:
            sprintf(&str[0], "%dm%ds  ", mins, segs);
            strtupapa(&str[0], &scroll_time);
            segs = angle;

            if (mins < 20)
            {
                if (segs > 59)
                {
                    mins++;
                    angle = 0;
                }
                if (segs < 0)
                {
                    if (mins > 0)
                    {
                        angle = 59;
                        mins--;
                    }
                    else
                    {
                        angle = 0;
                    }
                }
            }

            if (boton3 == 0) // deteccion de flanco bot3
            {
                estado = star_stop;
                mins_save = mins;
                segs_save = segs;
            }
            break;
        case star_stop:
            sprintf(&str[0], "%dm%ds   ", mins, segs);
            strtupapa(&str[0], &scroll_time);
            if (boton3 == 0) // deteccion de flanco bot3
                pausa = !pausa;
            if (pausa == 0)
            {
                if (seg_st >= 1000)
                {
                    seg_st = 0;
                    if (segs >= 1)
                    {
                        segs--;
                    }
                    else
                    {
                        if (mins >= 1)
                        {
                            mins--;
                            segs = 59;
                        }
                        else
                            estado = titilar;
                    }
                }
            }

            break;
        case titilar:
            sprintf(&str[0], "   \3\2 ");
            strtupapa(&str[0], &scroll_time);
            if (titi <= 20)
            {
                if (seg_st >= 500)
                {
                    titi++;
                    estado = titilarge;
                    seg_st = 0;
                }
            }
            else
            {
                titi = 0;
                estado = finazilo;
            }
            break;
        case titilarge:
            sprintf(&str[0], "  \3  \2");
            strtupapa(&str[0], &scroll_time);
            if (titi <= 20)
            {
                if (seg_st >= 500)
                {
                    titi++;
                    seg_st = 0;
                    estado = titilar;
                }
            }
            else
            {
                titi = 0;
                estado = finazilo;
            }
            break;
        case finazilo:
            mins = mins_save;
            segs = segs_save;
            estado = seteo;

            break;
        default:
            break;
        }
    }
}
ISR(TIMER1_COMPA_vect)
{
    // set_bit(PINB, PB5);
    seg_st++;
}
