
// PIC18F4550 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1L
#pragma config PLLDIV = 1       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 1       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)

// CONFIG1H
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator (HS))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = OFF        // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = OFF     // CCP2 MUX bit (CCP2 input/output is multiplexed with RB3)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = OFF     // Stack Full/Underflow Reset Enable bit (Stack full/underflow will not cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config ICPRT = OFF      // Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define _XTAL_FREQ 4000000

#include <xc.h>
#include <proc/pic18f4550.h>
#include "atividadelcd.h"

void encerra(){
    limpa_lcd();
    cursor_lcd_pos(0x80);
    escrever_lcd("  Obrigado por  ");
    cursor_lcd_pos(0xC0);
    escrever_lcd("     jogar!     ");
    cursor_lcd_pos(0x90);
    __delay_ms(1000);
    escrever_lcd("   Feito por:   ");
    cursor_lcd_pos(0xD0);
    escrever_lcd(" Matheus Cimatti");
    while(1){
        
    }
}

void proxima(){
    __delay_ms(1000);
    cursor_lcd_pos(0x90);
    escrever_lcd("Proxima pergunta");
    cursor_lcd_pos(0xD0);
    escrever_lcd("em 5 segundos...");
    __delay_ms(5000);
}

void pergunta3(){
    limpa_lcd();
    cursor_lcd_pos(0x80);
    escrever_lcd("O que nasceu");
    cursor_lcd_pos(0xC0);
    escrever_lcd("primeiro?");
    cursor_lcd_pos(0x90);
    escrever_lcd("a)o ovo");
    cursor_lcd_pos(0xD0);
    escrever_lcd("b)a galinha");
    while(1){
        if(PORTBbits.RB1 == 0){
            limpa_lcd();
            cursor_lcd_pos(0x80);
            escrever_lcd("Entao o almoco");
            cursor_lcd_pos(0xC0);
            escrever_lcd("sera ovo frito!");
            __delay_ms(1000);
            cursor_lcd_pos(0x90);
            escrever_lcd("Encerrando jogo");
            cursor_lcd_pos(0xD0);
            escrever_lcd("em 5 segundos...");
            __delay_ms(5000);
            encerra();
        }
        else if(PORTBbits.RB2 == 0){
            limpa_lcd();
            cursor_lcd_pos(0x80);
            escrever_lcd("Entao o almoco");
            cursor_lcd_pos(0xC0);
            escrever_lcd("sera galinhada!");
            __delay_ms(1000);
            cursor_lcd_pos(0x90);
            escrever_lcd("Encerrando jogo");
            cursor_lcd_pos(0xD0);
            escrever_lcd("em 5 segundos...");
            __delay_ms(5000);
            encerra();
        }
    }
}

void pergunta2(){
    limpa_lcd();
    cursor_lcd_pos(0x80);
    escrever_lcd("Se o pato perde");
    cursor_lcd_pos(0xC0);
    escrever_lcd("a pata ele fica:");
    cursor_lcd_pos(0x90);
    escrever_lcd("a)manco");
    cursor_lcd_pos(0xD0);
    escrever_lcd("b)viuvo");
    while(1){
        if(PORTBbits.RB1 == 0){
            limpa_lcd();
            cursor_lcd_pos(0x80);
            escrever_lcd("Eu acho que fica");
            cursor_lcd_pos(0xC0);
            escrever_lcd("viuvo. Coitado.");
            proxima();
            pergunta3();
        }
        else if(PORTBbits.RB2 == 0){
            limpa_lcd();
            cursor_lcd_pos(0x80);
            escrever_lcd("Eu acho que fica");
            cursor_lcd_pos(0xC0);
            escrever_lcd("manco. Coitado.");
            proxima();
            pergunta3();
        }
    }
}

void pergunta1(){
    limpa_lcd();
    cursor_lcd_pos(0x80);
    escrever_lcd("Qual o contrario");
    cursor_lcd_pos(0xC0);
    escrever_lcd("de simpatia?");
    cursor_lcd_pos(0x90);
    escrever_lcd("a)antipatia");
    cursor_lcd_pos(0xD0);
    escrever_lcd("b)nao pro tio");
    while(1){
        if(PORTBbits.RB1 == 0){
            limpa_lcd();
            cursor_lcd_pos(0x80);
            escrever_lcd("Voce eh muito");
            cursor_lcd_pos(0xC0);
            escrever_lcd("serio! Ria mais!");
            proxima();
            pergunta2();
        }
        else if(PORTBbits.RB2 == 0){
            limpa_lcd();
            cursor_lcd_pos(0x80);
            escrever_lcd("Essa piada foi");
            cursor_lcd_pos(0xC0);
            escrever_lcd("pessima! XD");
            proxima();
            pergunta2();
        }
    }
}

void instrucoes(){
    limpa_lcd();
    cursor_lcd_pos(0x80);
    escrever_lcd("   Instrucoes:  ");
    cursor_lcd_pos(0xC0);
    escrever_lcd(" a)RB1    b)RB2");
    cursor_lcd_pos(0x90);
    escrever_lcd("  Precione RB0");
    cursor_lcd_pos(0xD0);
    escrever_lcd("  para iniciar");
    while(1){
        if(PORTBbits.RB0 == 0){
            pergunta1();
        }
    }
}

void main(void) {
    PIC_init();
    config_lcd();
    
    TRISB = 0b11111111; //PORTB configurado como entrada
    
    instrucoes();
    return;
}
