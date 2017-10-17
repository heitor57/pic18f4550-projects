/*
 * File:   exercicio3.c
 * Author: Heitor
 *
 * Created on 18 de Junho de 2017, 02:09
 */


#include <xc.h>
#include "lcd.h"
#include "serial.h"
#include "itoa.h"
#include "atraso.h"
#define _VENT 0x00
#define _VSAI 0x01
#define _AQUE 0x02
#define _RESF 0x03
#define _AGIT 0x04
#define _LIGA 0x01

#define _BALT 0x10
#define _BBAI 0x11
#define _TMIN 0x12
#define _TMAX 0x13

#define _ATMI 0x20
#define _ATMA 0x21

#define _VOLU 0x30
#define _TEMP 0x31

#define _LIGA 0x01
#define _DESLIGA 0x00
#define n 10
void setup(){
    TRISCbits.TRISC7 = 1;
    lcd_init();
    serial_init();
    lcd_cmd(L_CLR);
    serial_tx(0xFF);
    serial_tx(0xFF);
    serial_tx(0xFF);
}
unsigned char valor,buffer[6];
unsigned int volume_maximo;
void etapa(int num){
    lcd_cmd(L_L1);
    lcd_str("Etapa ");
    lcd_dat(num+0x30);
}
unsigned int mostravol() {
    unsigned char valorh,valorl;
    unsigned int valori;
    serial_tx(_VOLU);
    valorh = serial_rx(0);
    valorl = serial_rx(0);
    valori = (valorh << 8) | valorl;
    lcd_cmd(L_L2);
    lcd_str(itoa(valori,buffer));
    lcd_str("l");
    return valori;
}

unsigned int mostratemp(){
    unsigned char valorh,valorl;
    unsigned int valori;
    serial_tx(_TEMP);
    valorh = serial_rx(0);
    valorl = serial_rx(0);
    valori = (valorh << 8) | valorl;
    lcd_cmd(L_L2+7);
    lcd_str(itoa(valori,buffer)+2);
    lcd_str("C");
    
    return valori;
}
void loop(void) {
    serial_tx(_VENT);
    serial_tx(_LIGA);
    serial_tx(_VSAI);
    serial_tx(_DESLIGA);
    etapa(1);
    do {
        serial_tx(_BALT);
        valor = serial_rx(0);
        mostravol();
        mostratemp();
    } while (!valor);
    volume_maximo = mostravol();
    serial_tx(_VENT);
    serial_tx(_DESLIGA);
    serial_tx(_ATMA);
    serial_tx(0);
    serial_tx(40);// (n = 10) n + 30 = 40
    etapa(2);
    serial_tx(_AQUE);
    serial_tx(_LIGA);
    etapa(3);
    do {//espera atingir 40
        serial_tx(_TMAX);
        valor = serial_rx(0);
        mostratemp();
    } while (!valor);
    serial_tx(_AQUE);
    serial_tx(_DESLIGA);
    etapa(4);
    serial_tx(_AGIT);
    serial_tx(_LIGA);
    atraso_ms(2000);
    serial_tx(_AGIT);
    serial_tx(_DESLIGA);
    etapa(5);
    serial_tx(_VSAI);
    serial_tx(_LIGA);
    do {
        mostratemp();
    } while (mostravol() > volume_maximo/2);
    serial_tx(_VSAI);
    serial_tx(_DESLIGA);
    etapa(6);
    serial_tx(_RESF);
    serial_tx(_LIGA);
    do{
        
    }while(mostratemp()>18);
    etapa(7);
    serial_tx(_RESF);
    serial_tx(_DESLIGA);
    serial_tx(_VSAI);
    serial_tx(_LIGA);
    do {
        serial_tx(_BBAI);
        valor = serial_rx(0);
        mostravol();
        mostratemp();
    }while(valor);
    etapa(8);
}