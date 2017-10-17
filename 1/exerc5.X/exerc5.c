/*
 * File:   exerc5.c
 * Author: Heitor
 *
 * Created on 6 de Abril de 2017, 16:52
 */


#include <xc.h>
#include "config.h"
#include "display7s.h"
#include "atraso.h"
#include "eeprom.h"
char nivel = 0, contador = 0;

void interrupt isr(void) {
    TMR0H = 11111111;
    TMR0L = 11111000;
    if (contador < nivel) {
        PORTCbits.RC5 = 1;
    } else {
        PORTCbits.RC5 = 0;
    }
    contador = contador + 1;
    if (contador == 10)contador = 0;
    INTCONbits.TMR0IF = 0;
}

void setup() {
    //Ttmr0= 1/1000 = (4/Fosc)*256*(65536 - 65528)
    //Ftmr0=1000Hz
    T0CONbits.PSA = 0;
    T0CONbits.T0PS = 0b111;
    T0CONbits.T08BIT = 0;
    T0CONbits.T0CS = 0;
    TMR0H = 11111111;
    TMR0L = 11111000;
    //interupções
    INTCONbits.GIE = 1;
    INTCONbits.TMR0IE = 1;
    INTCONbits.TMR0IF = 0;
    TMR0ON = 1;
    //display
    TRISAbits.RA4 = 0;
    TRISAbits.RA5 = 0;
    PORTD = 0;
    TRISBbits.RB0 = 1;
    TRISBbits.RB1 = 1;
    TRISBbits.RB2 = 1;
    TRISBbits.RB3 = 1;
    nivel = e2prom_r(10);
}
int cont = 0,cont2 = 0;

void loop() {
    PORTD = display7s(nivel % 10);
    PORTAbits.RA5 = 1;
    atraso_ms(3);
    PORTAbits.RA5 = 0;

    if (!PORTBbits.RB0) {
        atraso_ms(2);
        cont++;
        if (cont == 500) {
            if (!PORTBbits.RB0) {
                if (nivel < 9) {
                    nivel = nivel + 1;
                    cont = 0;
                }
            }
        }
    } else {
        cont = 0;
    }


    if (!PORTBbits.RB1) {
        atraso_ms(2);
        cont2++;
        if(cont2==500){
        if (!PORTBbits.RB1) {
            if (nivel > 0) {
                nivel = nivel - 1;
                cont2=0;
            }
        }
        }
    }else{
        cont2=0;
    }
    if (!PORTBbits.RB2) {
        atraso_ms(1);
        if (!PORTBbits.RB2) {
            nivel = 0;
        }
    }
    if (!PORTBbits.RB3) {
        atraso_ms(1);
        if (!PORTBbits.RB3) {
            nivel = 9;
        }
    }
    e2prom_w(10, nivel);
}