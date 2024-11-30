#include <Arduino.h>

#include "wels.c"

#define set_bit(reg, bit) reg |= (1 << bit)
#define clear_bit(reg, bit) reg &= ~(1 << bit)

#define boton3 (PIND >> PD4 & 1)
#define boton2 (PIND >> PD3 & 1)
#define boton1 (PIND >> PD7 & 1)



void anti_reb1(void);

uint8_t flag_bot1, e_a_b1;
uint8_t flag_bot2, e_a_b2;
uint8_t flag_bot3, e_a_b3;
uint8_t flag_bot4, e_a_b4;

uint32_t seg_st = 0;
int8_t angle = 10;


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
    timer1();

    initInterrupts();
    sei();

    clear_bit(PORTB, PB5);
    clear_bit(DDRD, PD2); // boton 1
    set_bit(PORTD, PD2);

    clear_bit(DDRD, PD3); // boton 2
    set_bit(PORTD, PD3);

    clear_bit(DDRD, PD4); // boton 3
    set_bit(PORTD, PD4);
    clear_bit(DDRD, PD7); // boton 3
    set_bit(PORTD, PD7);

    set_bit(DDRB, PB0); // led 8
    set_bit(DDRB, PB1); // led 8
    set_bit(DDRB, PB2); // led 8
    set_bit(DDRB, PB5); // led 8
    char str[50];
    uint16_t volt;
    uint8_t titi = 0;
    uint8_t pausa = 0;
    int8_t mins = 3, mins_save, segs_save;
    enum sexo_fernandez
    {
        seteo,
        star_stop,
        titilar,
        titilarge,
        finazilo,
        Voltimetro
    };
    enum sexo_fernandez estado = seteo;
    while (1)
    {
        switch (estado)
        {
        case seteo:
            sprintf(&str[0], "%dm%ds  ", mins, angle);
            strtupapa(&str[0]);
            if (mins < 20)
            {
                if (angle > 59)
                {
                    mins++;
                    angle = 0;
                }
                if (angle < 0)
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
            else
            {
                mins = 0;
                angle = 0;
            }
            if (boton3 == 0)
            {
                estado = star_stop;
                mins_save = mins;
                segs_save = angle;
            }
            if (flag_bot1 == 1 && e_a_b1 == 0) // deteccion de flanco bot1
            {
                estado = Voltimetro;
            }
            e_a_b1 = flag_bot1;
            break;
        case star_stop:
            sprintf(&str[0], "%dm%ds   ", mins, angle);
            strtupapa(&str[0]);
            if (boton3 == 0) // deteccion de flanco bot3
                pausa = !pausa;
            if (pausa == 0)
            {
                if (seg_st >= 300)
                {
                    seg_st = 0;
                    if (angle >= 1)
                    {
                        angle--;
                    }
                    else
                    {
                        if (mins >= 1)
                        {
                            mins--;
                            angle = 59;
                        }
                        else
                            estado = titilar;
                    }
                }
            }

            break;
        case titilar:
            sprintf(&str[0], "   \3\2 ");
            strtupapa(&str[0]);
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
            strtupapa(&str[0]);
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
            angle = segs_save;
            estado = seteo;

            break;
        case Voltimetro:
            sprintf(&str[0], "%d.%dV  ", volt / 1000, volt % 1000);
            strtupapa(&str[0]);
            if (seg_st >= 100)
            {
                volt = (uint32_t)adc_read(0) * 5000 / 1024;
                seg_st = 0;
            }
            if (flag_bot1 == 1 && e_a_b1 == 0) // deteccion de flanco bot1
            {
                estado = seteo;
            }
            e_a_b1 = flag_bot1;
            break;

        default:
            sprintf(&str[0], "%d.%dV  ", volt / 1000, volt % 1000);
            strtupapa(&str[0]);
            if (seg_st >= 100)
            {
                volt = (uint32_t)adc_read(0) * 5000 / 1024;
                seg_st = 0;
            }

            break;
        }
    }
}
ISR(TIMER1_COMPA_vect)
{
    // set_bit(PINB, PB5);
    seg_st++;
    anti_reb1();
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
