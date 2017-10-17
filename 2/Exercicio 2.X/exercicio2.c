/*
 * File:   exercicio2.c
 * Author: ALUNO
 *
 * Created on 14 de Junho de 2017, 12:09
 */


#include <xc.h>
#include "adc.h"
#include "config.h"
#include "itoa.h"
#include "lcd.h"
#include "pwm.h"
#include "atraso.h"
char buffer[6]; 
void setup(){
    lcd_init();
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Heitor");
    adc_init();
    
    PWM1_Init(5000);
    PWM1_Start();
    PWM1_Set_Duty(120);
}
unsigned int val=0;
void loop(){
    lcd_cmd(L_L2);
    val = adc_amostra(0);
    itoa((val*50000l)/1023,buffer);
    lcd_dat(buffer[0]);
    lcd_dat('.');
    lcd_str(buffer+1);
    lcd_dat('V');
    PWM1_Set_Duty(  ((float)val / 1023)*127);// 50% | n=10 |n * 4 + 10 = 50
}
