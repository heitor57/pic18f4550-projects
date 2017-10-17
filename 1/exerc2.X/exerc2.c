/*
 * File:  main.c
 * Author: Heitor
 *
 * Created on 2 de Abril de 2017, 15:26
 */


#include <xc.h>
#include "atraso.h"
#include "display7s.h"
#include "config.h"

unsigned int r=0,n=10;

void setup(){
    PORTD=0;
    r=((n*873)+32346)/10;
}

void loop(){
    PORTD=display7s((r%10000)/1000);
    PORTAbits.RA2=1;
    atraso_ms(3);
    PORTAbits.RA2=0;
    PORTD=display7s((r%1000)/100);
    PORTAbits.RA3=1;
    atraso_ms(3);
    PORTAbits.RA3=0;
    PORTD=display7s((r%100)/10);
    PORTAbits.RA4=1;
    atraso_ms(3);
    PORTAbits.RA4=0;
    PORTD=display7s(r%10);
    PORTAbits.RA5=1;
    atraso_ms(3);
    PORTAbits.RA5=0;
}