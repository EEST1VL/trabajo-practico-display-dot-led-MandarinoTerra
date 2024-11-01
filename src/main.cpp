#include <Arduino.h>

#include "wels.c"

#define set_bit(reg, bit) reg |= (1 << bit)
#define clear_bit(reg, bit) reg &= ~(1 << bit)

#define boton1 (PIND >> PD4 & 1)
#define boton2 (PIND >> PD3 & 1)
#define boton3 (PIND >> PD2 & 1)

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
    titilar
};
enum sexo_fernandez estado = seteo;
uint16_t seg_st = 0;

uint16_t velo = 1000;
uint8_t pausa = 0;
uint8_t mins = 59, segs = 0, mins_save, segs_save;
int main()
{
    TCCR1A = 0b00000000; // CTC
    TCCR1B = 0b00001011; // clk/64
    TCCR1C = 0;
    OCR1A = 249;
    TIMSK1 = (1 << OCIE1A);

    sei();

    clear_bit(PORTB, PB5);
    clear_bit(DDRD, PD2); // boton 1
    set_bit(PORTD, PD2);

    clear_bit(DDRD, PD3); // boton 2
    set_bit(PORTD, PD3);

    clear_bit(DDRD, PD4); // boton 3
    set_bit(PORTD, PD4);

    set_bit(DDRB, PB0); // led 7
    set_bit(DDRB, PB1); // led 8
    set_bit(DDRB, PB2); // led 8
    set_bit(DDRB, PB5); // led 8

    char str[] = {"83m14s "};

    while (1)
    {
        switch (estado)
        {
        case seteo:
            sprintf(&str[0], "%dm%ds  ", mins, segs);
            strtupapa(&str[0], &scroll_time);
            if (flag_bot1 == 1 && e_a_b1 == 0) // deteccion de flanco bot1
            {
                if (mins < 59)
                {
                    mins++;
                }
                else
                    mins = 0;
            }
            e_a_b1 = flag_bot1;

            if (flag_bot2 == 0 && e_a_b2 == 1) // deteccion de flanco bot2
            {
                if (segs < 59)
                {
                    segs++;
                }
                else
                    segs = 0;
            }
            e_a_b2 = flag_bot2;

            if (flag_bot3 == 0 && e_a_b3 == 1) // deteccion de flanco bot3
            {
                estado = star_stop;
                mins_save = mins;
                segs_save = segs;
            }
            e_a_b3 = flag_bot3;
            break;
        case star_stop:
            sprintf(&str[0], "%dm%ds   ", mins, segs);
            strtupapa(&str[0], &scroll_time);
            if (flag_bot3 == 0 && e_a_b3 == 1) // deteccion de flanco bot3
            {
                pausa = !pausa;
            }
            e_a_b3 = flag_bot3;
            if (pausa == 0)
            {
                if (seg_st >= 100)
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
            sprintf(&str[0], "Fin\3 \2 ");
            strtupapa(&str[0], &scroll_time);
            if (flag_bot1 == 1 && e_a_b1 == 0) // deteccion de flanco bot1
            {
                mins = mins_save;
                segs = segs_save;
                estado = seteo;
            }
            e_a_b1 = flag_bot1;
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

    anti_reb1();
    anti_reb2();
    anti_reb3();
}

void anti_reb1(void)
{
    static uint8_t cont_bot1 = 0;
    if (boton1 == 0)
    {
        if (cont_bot1 < 200)
        {
            cont_bot1++;
        }
    }
    else
    {
        cont_bot1 = 0;
    }
    if (cont_bot1 > 50)
    {
        flag_bot1 = 1;
        set_bit(PINB, PB5);
    }
    else
    {

        flag_bot1 = 0;
    }
}

void anti_reb2(void)
{
    static uint8_t cont_bot2 = 0;
    if (boton2 == 0)
    {
        if (cont_bot2 < 200)
        {
            cont_bot2++;
        }
    }
    else
    {
        cont_bot2 = 0;
    }
    if (cont_bot2 > 50)
    {
        flag_bot2 = 1;
        set_bit(PINB, PB5);
    }
    else
    {
        flag_bot2 = 0;
    }
}

void anti_reb3(void)
{
    static uint8_t cont_bot3 = 0;
    if (boton3 == 0)
    {
        if (cont_bot3 < 200)
        {
            cont_bot3++;
        }
    }
    else
    {
        cont_bot3 = 0;
    }
    if (cont_bot3 > 50)
    {
        flag_bot3 = 1;
        set_bit(PINB, PB5);
    }
    else
    {
        flag_bot3 = 0;
    }
}