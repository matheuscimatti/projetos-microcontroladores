/************************************************************
 Biblioteca para LCD utilizando a placa PICGenios - PICSimLab
 Compilador XC8
 IDE: MPLAB X
 ***********************************************************/

#ifndef LCD_H
#define LCD_H

#include <string.h>

void PIC_init(){
    TRISD = 0b00000000;//Configura a Porta D como saída
    TRISE = 0b00000000;//Configura a Porta E como saída
}

void config_lcd(){
    PORTEbits.RE2 = 0;//Inicia a recepcao de comandos do LCD
    char i;
    char config[7] = { //Conjunto de comandos para configurar o LCD
                    0x30, //3 comandos para estabilizar o LCD
                    0x30, 
                    0x30, 
                    0x38,//Comunicacao de 8bits. Display de duas ou mais linhas. Matriz de 8x5. 0x3C -> 10x5
                    0x0F,//Liga o cursor com alternancia.
                    0x06,//Desloca o cursor para a direita quando um caractere e? inserido, mas nao desloca a mensagem.
                    0x01//Limpa a tela do display e desloca o cursor para a linha 1 e coluna 1. Apaga o conteu?do da DDRAM.
                  };
  
    for(i=0;i<7;i++){
        PORTEbits.RE1 = 1;//Habilita o LCD para receber comando ou dado
         PORTD = config[i];//Envia o comando
        __delay_us(50);
        PORTEbits.RE1 = 0;//Desabilita o LCD para receber comando ou dado
        __delay_us(50);
    }  
    PORTEbits.RE2 = 1;//Finaliza a recepcao de comandos do LCD
}


void cursor_lcd_pos(char posicao){
    PORTEbits.RE2 = 0;//Inicia a recepcao de comandos do LCD
    PORTEbits.RE1 = 1;
    PORTD = posicao;
    __delay_us(50);
    PORTEbits.RE1 = 0;
    __delay_us(50);
    PORTEbits.RE2 = 1;//Finaliza a recepcao de comandos do LCD
}


void escrever_lcd(char texto[]){
    char length, i;
    length = strlen(texto);//Tamanho da string a ser escrita
    for(i=0;i<length;i++){
        PORTEbits.RE1 = 1;
        PORTD = texto[i];//Envia um caracter por ver para o LCD
        __delay_ms(50); //Se quiser uma escrita imperceptivel, reduzir essa espera até o mínimo de 50us.
        PORTEbits.RE1 = 0;
        __delay_us(50);
    }
}

void escrever_char(char letra){
    PORTEbits.RE1 = 1;
    PORTD = letra;//Envia um caracter por vez para o LCD
    __delay_us(50); //Se quiser uma escrita imperceptivel, reduzir essa espera até o mínimo de 50us.
    PORTEbits.RE1 = 0;
    __delay_us(50);
}
#endif