
#include <pic18f4550.h>
#include "atraso.h"
unsigned char intrp1=0,intrp2=0;

void interrupt isr(void){
    if(INTCONbits.TMR0IF){
        INTCONbits.TMR0IF=0;
        TMR0H = 0b11111111;
        TMR0L =  0b11100001;
        intrp1++;
        if(intrp1==250){
            intrp1=0;
            PORTDbits.RD0=1;
            atraso_ms(50);
            PORTDbits.RD0=0;
        }
        
    }
    if(PIR1bits.TMR1IF){
        intrp2++;
        TMR1H = 0xF6;
        TMR1L = 0x3C;
        PIR1bits.TMR1IF=0;
        if(intrp2==200){
            intrp2=0;
            PORTDbits.RD1=1;
            atraso_ms(50);
            PORTDbits.RD1=0;
        }
    }
}
void setup(){
    // 4000 us = (4/8MHz)*256*(65536-TMR0L_ini)
    // TMR0L_ini = 65504
    //config TMR0
    T0CONbits.T0CS = 0;
    T0CONbits.PSA = 0;
    T0CONbits.T0PS2 = 1; //Prescale Select bits = 256 
    T0CONbits.T0PS1 = 1;
    T0CONbits.T0PS0 = 1;
    T0CONbits.T08BIT = 0;//TIMER0 modo 16bits
    TMR0H = 0b11111111;
    TMR0L =  0b11100001;
    INTCONbits.TMR0IF = 0;
    // 10 ms = (4/8MHz)*8*(65536-TMR1L_ini)
    // TMR0L_ini = 63036
    //config TMR1
    T1CONbits.TMR1ON = 0;
    T1CONbits.TMR1CS = 0;
    T1CONbits.T1CKPS1 = 1; //Prescale Select bits = 8
    T1CONbits.T1CKPS0 = 1;
    TMR1H = 0xF6; //63036=0xF63C
    TMR1L = 0x3C; 
    PIR1bits.TMR1IF = 0;
    //configura interrupçoes
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.TMR0IE = 1;
    PIE1bits.TMR1IE = 1;
    //ligando os timers
    T0CONbits.TMR0ON = 1;
    T1CONbits.TMR1ON = 1;
   //Desligando LEDs
    PORTD=0x00;
    PORTB=0x00;
}

void loop(){
}