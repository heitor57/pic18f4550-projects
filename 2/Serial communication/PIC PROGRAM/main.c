/*
 * File:   main.c
 * Author: Heitor
 *
 * Created on 26 de Junho de 2017, 12:28
 */


#include <pic18f4550.h>

#include "config.h"
#include "atraso.h"
#include "serial.h"
#include "pwm.h"
#include "adc.h"
#include "lcd.h"
unsigned char valueh = 0,valuel = 0;
unsigned int value;
int i;
void setup(){
    TRISAbits.TRISA2 = 1;
    TRISCbits.TRISC7 = 1;
    PWM1_Init(5000);
    PWM1_Start();
    serial_init();
    adc_init();
    lcd_init();
    lcd_cmd(L_CLR);
    TRISD = 0x00; 
    TRISB = 0x00;
    PORTD = 0x00;
    PORTB = 0x00;
    PWM1_Set_Duty(0);
}

void loop(){
    switch(serial_rx(0)){
        case 'l':
            switch(serial_rx(0)){
                case '1':
                    lcd_cmd(L_L1);
                    for(i = 0 ; i<16 ; i++){
                        lcd_dat(serial_rx(0));
                    }
                    break;
                case '2':
                    lcd_cmd(L_L2);
                    for(i = 0 ; i<16 ; i++){
                        lcd_dat(serial_rx(0));
                    }
                    break;
            }
            break;
        case 't':
            value = adc_sample(2);
            serial_tx(value/2);
            break;
        case 'c':
            valueh = serial_rx(0);
            valuel = serial_rx(0);
            PWM1_Set_Duty(valueh+valuel);
            break;
        case '1':
            switch(serial_rx(0)){
                case 'C':
                    switch(serial_rx(0)){
                        case '5':
                            PORTCbits.RC5 = 1;
                            break;
                    }
                    break;
                case 'D':
                    switch(serial_rx(0)){
                        case '0':
                            PORTDbits.RD0 = 1;
                            break;
                        case '1':
                            PORTDbits.RD1 = 1;
                            break;
                        case '2':
                            PORTDbits.RD2 = 1;
                            break;
                        case '3':
                            PORTDbits.RD3 = 1;
                            break;
                        case '4':
                            PORTDbits.RD4 = 1;
                            break;
                        case '5':
                            PORTDbits.RD5 = 1;
                            break;
                        case '6':
                            PORTDbits.RD6 = 1;
                            break;
                        case '7':
                            PORTDbits.RD7 = 1;
                            break;
                        case 't':
                            PORTDbits.RD0 = 1;
                            PORTDbits.RD1 = 1;
                            PORTDbits.RD2 = 1;
                            PORTDbits.RD3 = 1;
                            PORTDbits.RD4 = 1;
                            PORTDbits.RD5 = 1;
                            PORTDbits.RD6 = 1;
                            PORTDbits.RD7 = 1;
                            break;
                    }
                    break;
                case 'B':
                    switch(serial_rx(0)){
                        case '0':
                            PORTBbits.RB0 = 1;
                            break;
                        case '1':
                            PORTBbits.RB1 = 1;
                            break;
                        case '2':
                            PORTBbits.RB2 = 1;
                            break;
                        case '3':
                            PORTBbits.RB3 = 1;
                            break;
                        case '4':
                            PORTBbits.RB4 = 1;
                            break;
                        case '5':
                            PORTBbits.RB5 = 1;
                            break;
                        case '6':
                            PORTBbits.RB6 = 1;
                            break;
                        case '7':
                            PORTBbits.RB7 = 1;
                            break;
                        case 't':
                            PORTBbits.RB0 = 1;
                            PORTBbits.RB1 = 1;
                            PORTBbits.RB2 = 1;
                            PORTBbits.RB3 = 1;
                            PORTBbits.RB4 = 1;
                            PORTBbits.RB5 = 1;
                            PORTBbits.RB6 = 1;
                            PORTBbits.RB7 = 1;
                            break;
                    }
                    break;
            }
            break;
        case '0':
            switch(serial_rx(0)){
                case 'C':
                    switch(serial_rx(0)){
                        case '5':
                            PORTCbits.RC5 = 0;
                            break;
                    }
                    break;
                case 'D':
                    switch(serial_rx(0)){
                        case '0':
                            PORTDbits.RD0 = 0;
                            break;
                        case '1':
                            PORTDbits.RD1 = 0;
                            break;
                        case '2':
                            PORTDbits.RD2 = 0;
                            break;
                        case '3':
                            PORTDbits.RD3 = 0;
                            break;
                        case '4':
                            PORTDbits.RD4 = 0;
                            break;
                        case '5':
                            PORTDbits.RD5 = 0;
                            break;
                        case '6':
                            PORTDbits.RD6 = 0;
                            break;
                        case '7':
                            PORTDbits.RD7 = 0;
                            break;
                        case 't':
                            PORTDbits.RD0 = 0;
                            PORTDbits.RD1 = 0;
                            PORTDbits.RD2 = 0;
                            PORTDbits.RD3 = 0;
                            PORTDbits.RD4 = 0;
                            PORTDbits.RD5 = 0;
                            PORTDbits.RD6 = 0;
                            PORTDbits.RD7 = 0;
                    }
                    break;
                case 'B':
                    switch(serial_rx(0)){
                        case '0':
                            PORTBbits.RB0 = 0;
                            break;
                        case '1':
                            PORTBbits.RB1 = 0;
                            break;
                        case '2':
                            PORTBbits.RB2 = 0;
                            break;
                        case '3':
                            PORTBbits.RB3 = 0;
                            break;
                        case '4':
                            PORTBbits.RB4 = 0;
                            break;
                        case '5':
                            PORTBbits.RB5 = 0;
                            break;
                        case '6':
                            PORTBbits.RB6 = 0;
                            break;
                        case '7':
                            PORTBbits.RB7 = 0;
                            break;
                        case 't':
                            PORTBbits.RB0 = 0;
                            PORTBbits.RB1 = 0;
                            PORTBbits.RB2 = 0;
                            PORTBbits.RB3 = 0;
                            PORTBbits.RB4 = 0;
                            PORTBbits.RB5 = 0;
                            PORTBbits.RB6 = 0;
                            PORTBbits.RB7 = 0;
                            break;
                    }
                    break;
            }
            break;
    }
}