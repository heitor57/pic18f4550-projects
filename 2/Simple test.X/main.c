/*
 * File:   main.c
 * Author: Aluno
 *
 * Created on 28 de Junho de 2017, 11:00
 */

//temperatura e led
// de acordo com o valor no conversor AD ele ira disponibilizar o nivel nos leds
// e também tera o valor do AD no LCD
#include <xc.h>

#include "pwm.h"
#include "adc.h"
#include "itoa.h"
#include "lcd.h"
unsigned char level=0;

void setup(){
    lcd_init();
    lcd_cmd(L_CLR);
    TRISB = 0x00;
    PORTB = 0x00;
    PWM1_Init(5000);
    adc_init();
    PWM1_Start();
    PWM1_Set_Duty(level);
    TRISAbits.TRISA2 = 1;
    PORTCbits.RC5 = 1;
}
char buffer[6];
void loop(){
    lcd_cmd(L_L1);
    level = adc_sample(2)/4;
    itoa(level*50000/255,buffer);
    lcd_dat(buffer[0]);
    lcd_dat(buffer[1]);
    lcd_dat(buffer[2]);
    lcd_dat('.');
    lcd_str(buffer+3);
    lcd_dat('C');
    PWM1_Set_Duty(level);
    if(level==255){
        PORTB = 0b11111111;
    }else if(level<=223 &&level>191  ){
        PORTB = 0b11111110;
    }else if(level<=191 && level>159 ){
        PORTB = 0b11111100;
    }else if(level<=159 && level>127 ){
        PORTB = 0b11111000;
    }else if(level<=127 && level>95 ){
        PORTB = 0b11110000;
    }else if(level<=95 && level>63 ){
        PORTB = 0b11100000;
    }else if(level<=63 && level>31 ){
        PORTB = 0b11000000;
    }else if(level<=31){
        PORTB = 0b10000000;
    }
}

