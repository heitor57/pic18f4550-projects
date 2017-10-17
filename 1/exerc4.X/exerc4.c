/*
 * File:   aula06.c
 * Author: ALUNO
 *
 * Created on 29 de Março de 2017, 10:52
 */


#include <xc.h>
#include "atraso.h"
#include "display7s.h"
unsigned char min=0,seg=0;
unsigned int aux=0;
void interrupt isr(void) {
    if (PIR1bits.TMR2IF) {
        PIR1bits.TMR2IF = 0;
        aux++;
        if (aux == 77){// 1/(0,013) = 77
            seg++;
            aux = 0;
            if(seg == 60){
                seg=0;
                min++;
                if(min==60){
                    min=0;
                }
            }
        }
        return;
    }
}
void setup() {
    //bit flag = 0 inicialmente
    PIR1bits.TMR2IF = 0;
    //Configura TMR2
    T2CONbits.T2CKPS1 = 1; //divide por 16
    T2CONbits.T2CKPS0 = 1;
    T2CONbits.TOUTPS3 = 1; //divide por 16
    T2CONbits.TOUTPS2 = 1;
    T2CONbits.TOUTPS1 = 1;
    T2CONbits.TOUTPS0 = 1;
    TMR2 =0;
    PR2 = 100; // 13ms = (4/8Mhz)*16*(100 + 1)*16
    //configura interrupçoes
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    PIE1bits.TMR2IE = 1;
    //liga timer
    T2CONbits.TMR2ON = 1;
    
    //portas para os displays em output        
    TRISAbits.RA2=0;
    TRISAbits.RA3=0;
    TRISAbits.RA4=0;
    TRISAbits.RA5=0;
    PORTA=0;
}
char auxiliar=0;
char onoff=1;
void loop() {
    PORTD=display7s(min/10);
    PORTDbits.RD7=onoff;
    PORTAbits.RA2=1;
    atraso_ms(3);
    PORTAbits.RA2=0;
    PORTD=display7s(min%10);
    PORTDbits.RD7=onoff;
    PORTAbits.RA3=1;
    atraso_ms(3);
    PORTAbits.RA3=0;
    PORTD=display7s(seg/10);
    PORTDbits.RD7=onoff;
    PORTAbits.RA4=1;
    atraso_ms(3);
    PORTAbits.RA4=0;
    PORTD=display7s(seg%10);
    PORTDbits.RD7=onoff;
    PORTAbits.RA5=1;
    atraso_ms(3);
    PORTAbits.RA5=0;
    if(PORTBbits.RB0==0){
        if(auxiliar){
            atraso_ms(1);
            if(PORTBbits.RB0 == 0){
                auxiliar=0;
                T2CONbits.TMR2ON ^=1;// operação ou exclusivo na atribuição
                if(T2CONbits.TMR2ON==1){
                    onoff=1;
                }else onoff=0;
                while(PORTBbits.RB0 == 0);
            }
        }
    }
    
    if(PORTBbits.RB1==0){
        seg=0;
        min=0;
    }else auxiliar=1;
}