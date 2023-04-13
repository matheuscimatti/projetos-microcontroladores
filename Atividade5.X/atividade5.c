
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
#pragma config CCP2MX = ON      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
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
#include "lcd5.h"

int opc = 0;//variavel para controle da opcao selecionada
int flag = 0;//variavel flag para iniciar e finalizar a operação apenas uma vez por click do botão

void __interrupt(high_priority) atv5Int(void){
    if(INTCONbits.INT0IF && INTCONbits.INT0IE){
        if(opc<4){
            flag = 1;
            opc++;
        }else{
            flag = 1;
            opc = 0;
        }
        INTCONbits.INT0IF = 0;//Limpa a flag da interrupção
    }
}

void main(void) {
    PIC_init();
    
    TRISBbits.RB0 = 1;//Configura o pino RB0 como entrada (INT0)
    RCONbits.IPEN = 1;//Ativa as prioridades de interrupções
    INTCONbits.GIEH = 1;//Ativa as interrupções de alta prioridade
    INTCONbits.GIEL = 0;//Desativa as interrupções de baixa prioridade
    INTCONbits.INT0IF = 0;//Limpa a flag de interrupção
    INTCON2bits.INTEDG0 = 0;//Borda de descida
    INTCONbits.INT0IE = 1;//Ativa a interrupção
    
    TRISCbits.RC2 = 0;//Configura pino RC2 como saída (CCP1)
    TRISCbits.RC1 = 0;//Configura pino RC1 como saída (CCP2)
    PR2 = 199;//Configura o tempo total de ciclo
    CCPR1L = 0;//Configura o duty cicle em zero (ventilador parado)
    CCPR2L = 0;//Configura o duty cicle em zero (aquecedor desligado)
    CCP1CON = 0b00001111;//Configura o CCP1 para o uso do PWM
    CCP2CON = 0b00001111;//Configura o CCP2 para o uso do PWM
    T2CON = 0b00000111;//Configura o timer2 com prescaler de 1:16 e ativa
    
    config_lcd();
    escrever_lcd("     Opcao:");
    cursor_lcd_pos(0xC5);
    escrever_lcd("Neutro");
    
    while(1){
        if(flag){
            switch(opc){
                case 0:
                    CCPR1L = 0;//ventuinha desligada
                    CCPR2L = 0;//aquecedor desligado
                    cursor_lcd_pos(0xC0);
                    escrever_lcd("     Neutro     ");
                    flag = 0;//Limpa a flag para não ficar em loop
                    break;
                case 1:
                    CCPR1L = PR2/2;//ventuinha ligada 50% do tempo (velocidade média)
                    cursor_lcd_pos(0xC0);
                    escrever_lcd("  Resfr. Leve   ");
                    flag = 0;//Limpa a flag para não ficar em loop
                    break;
                case 2:
                    CCPR1L = PR2;//ventuinha ligada 100% do tempo (velocidade máxima)
                    cursor_lcd_pos(0xC0);
                    escrever_lcd("  Resfr. Max.   ");
                    flag = 0;//Limpa a flag para não ficar em loop
                    break;
                case 3:
                    CCPR1L = 0;//ventuinha desligada
                    CCPR2L = PR2/2;//aquecedor ligado 50% do tempo (aquecimento médio)
                    cursor_lcd_pos(0xC0);
                    escrever_lcd("  Aquec. Leve   ");
                    flag = 0;//Limpa a flag para não ficar em loop
                    break;
                case 4:
                    CCPR2L = PR2;//aquecedor ligado 100% do tempo (aquecimento máximo)
                    cursor_lcd_pos(0xC0);
                    escrever_lcd("  Aquec. Max.   ");
                    flag = 0;//Limpa a flag para não ficar em loop
                    break;
            }
        }
    }
    
    return;
}
