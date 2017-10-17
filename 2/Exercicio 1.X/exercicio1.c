/*
 * File:   exercicio1.c
 * Author: ALUNO
 *
 * Created on 14 de Junho de 2017, 11:03
 */


#include <xc.h>
#include "config.h"
#include "lcd.h"
#include "serial.h"
#include "itoa.h"
int n =10;
char buffer[6];
void setup(){
    lcd_init();
    lcd_str("10 Heitor");
    serial_init();
    for(int i=1;i<=n+1;i++){
        serial_tx_str("\r\n");
        serial_tx_str("Heitor ");
        serial_tx_str(itoa(i,buffer)+3); 
    }
}
void loop(){
    
}