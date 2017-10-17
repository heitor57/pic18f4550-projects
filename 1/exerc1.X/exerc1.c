/*
 * File:   main.c
 * Author: Heitor
 *
 * Created on 29 de Março de 2017, 20:13
 */


#include <xc.h>
#include "atraso.h"
#include "display7s.h"
unsigned char a=0,seg=0,chamada=10;

void setup(){
    TRISD=0x00;
    TRISAbits.RA2=0;
    TRISAbits.RA3=0;
    TRISAbits.RA4=0;
    TRISAbits.RA5=0;
          
    PORTB=0;
    PORTA=0;
}
unsigned aux1=0,aux2=0;
void loop(){
    PORTD=display7s((seg%65536)/4096);
    PORTAbits.RA2=1;
    atraso_ms(3);
    PORTAbits.RA2=0;
    PORTD=display7s((seg%4096)/256);
    PORTAbits.RA3=1;
    atraso_ms(3);
    PORTAbits.RA3=0;
    PORTD=display7s((seg%256)/16);
    PORTAbits.RA4=1;
    atraso_ms(3);
    PORTAbits.RA4=0;
    PORTD=display7s(seg%16);
    PORTAbits.RA5=1;
    atraso_ms(3);
    PORTAbits.RA5=0;
    if(PORTBbits.RB0 == 0){
        atraso_ms(1);
        if(PORTBbits.RB0 == 0 && aux1){
            if(seg<=chamada){
                 seg++;
                 aux1=0;
            }
        }
    }else{
        aux1=1;
    }
    if(PORTBbits.RB1 == 0){
        atraso_ms(1);
        if(PORTBbits.RB1 == 0 && aux2){
            if(seg>0){
                 seg--;
                 aux2=0;
            }
        }
    }else{
        aux2=1;
    }
}
