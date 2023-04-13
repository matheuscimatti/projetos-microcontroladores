
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
#pragma config WDT = ON         // Watchdog Timer Enable bit (WDT enabled)
#pragma config WDTPS = 1024     // Watchdog Timer Postscale Select bits (1:1024)

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
#include "lcd_projeto.h"

//Variaveis guardadas na EEPROM
char flreset = 1;//Flag de controle do reset geral do dispositivo
unsigned char dias, hora, min, seg;

//Variaveis gerais usadas para as funções de reset e teclado
int num = 0;
char auxctrl = 0x01;
char hcontrol = 1, h2control = 1, mcontrol = 1 ; //Variaveis para controle de entrada
                                                //(impede hora > 24 e min > 59 no relogio)

double valor = 0;//Variavel para conversao AD, guarda a temperatura

void verifica(){//Funcao que verifica cada caso para fazer o acionamento do relé
    if(dias == 0 || dias == 1){
        if((hora>=18) || ((hora>=0) && (hora<6)))
            PORTCbits.RC0 = 1;
        else{
            if(valor<31 && PORTCbits.RC0 == 0)
                PORTCbits.RC0 = 1;
            else if(valor > 33 && PORTCbits.RC0)
                PORTCbits.RC0 = 0;
        }
    }
    else if(dias == 2){
        if((hora>=19) || ((hora>=0) && (hora<6)))
            PORTCbits.RC0 = 1;
        else{
            if(valor<31 && PORTCbits.RC0 == 0)
                PORTCbits.RC0 = 1;
            else if(valor > 33 && PORTCbits.RC0)
                PORTCbits.RC0 = 0;
        }
    }
    else if(dias == 3 || dias == 4){
        if((hora>=19) || ((hora>=0) && (hora<6)))
            PORTCbits.RC0 = 1;
        else{
            if(valor<28 && PORTCbits.RC0 == 0)
                PORTCbits.RC0 = 1;
            else if(valor > 30 && PORTCbits.RC0)
                PORTCbits.RC0 = 0;
        }
    }
    else if(dias>=5 && dias<=7){
        if((hora>=19) || ((hora>=0) && (hora<6)))
            PORTCbits.RC0 = 1;
        else{
            if(valor<26 && PORTCbits.RC0 == 0)
                PORTCbits.RC0 = 1;
            else if(valor > 28 && PORTCbits.RC0)
                PORTCbits.RC0 = 0;
        }
    }
    else if(dias>=8 && dias<=15){
        if((hora>=0) && (hora<6))
            PORTCbits.RC0 = 1;
        else{
            if(valor<26 && PORTCbits.RC0 == 0)
                PORTCbits.RC0 = 1;
            else if(valor > 28 && PORTCbits.RC0)
                PORTCbits.RC0 = 0;
        }
    }
    else if(dias>=16 && dias<=20){
        if((hora>=0) && (hora<6))
            PORTCbits.RC0 = 1;
        else{
            if(valor<24 && PORTCbits.RC0 == 0)
                PORTCbits.RC0 = 1;
            else if(valor > 26 && PORTCbits.RC0)
                PORTCbits.RC0 = 0;
        }
    }
    else if(dias == 21){
        if((hora>=0) && (hora<6))
            PORTCbits.RC0 = 1;
        else{
            if(valor<22 && PORTCbits.RC0 == 0)
                PORTCbits.RC0 = 1;
            else if(valor > 24 && PORTCbits.RC0)
                PORTCbits.RC0 = 0;
        }
    }
    else if(dias>=22 && dias<=28){
        if((hora==23) || ((hora>=0) && (hora<6)))
            PORTCbits.RC0 = 1;
        else{
            if(valor<22 && PORTCbits.RC0 == 0)
                PORTCbits.RC0 = 1;
            else if(valor > 24 && PORTCbits.RC0)
                PORTCbits.RC0 = 0;
        }
    }
    else if(dias>=29 && dias<=35){
        if((hora>=22) || ((hora>=0) && (hora<6)))
            PORTCbits.RC0 = 1;
        else{
            if(valor<22 && PORTCbits.RC0 == 0)
                PORTCbits.RC0 = 1;
            else if(valor > 24 && PORTCbits.RC0)
                PORTCbits.RC0 = 0;
        }
    }
    else if(dias>=36 && dias<=42){
        if((hora>=21) || ((hora>=0) && (hora<6)))
            PORTCbits.RC0 = 1;
        else{
            if(valor<22 && PORTCbits.RC0 == 0)
                PORTCbits.RC0 = 1;
            else if(valor > 24 && PORTCbits.RC0)
                PORTCbits.RC0 = 0;
        }
    }
    else if(dias>=43){
        if((hora>=20) || ((hora>=0) && (hora<6)))
            PORTCbits.RC0 = 1;
        else{
            if(valor<22 && PORTCbits.RC0 == 0)
                PORTCbits.RC0 = 1;
            else if(valor > 24 && PORTCbits.RC0)
                PORTCbits.RC0 = 0;
        }
    }
    
    CLRWDT();//Limpa o temporizador do WDT
    
}

void __interrupt(high_priority) intProjeto(void){
    if(INTCONbits.TMR0IF && INTCONbits.TMR0IE){//Interrupção do TMR0
        cursor_lcd_pos(0x84);//Posiciona relogio centralizado
        escrever_timer(hora, min, seg);
        cursor_lcd_pos(0xC0);
        escrever_dias(dias);
        cursor_lcd_pos(0xD0);
        escrever_temp(valor, 2);
        if(seg < 59){
            seg++;
        }else{
            seg = 0;
            min++;
            ADCON0bits.GO = 1;      //Faz a conversao
            while(!ADCON0bits.DONE);//Aguarda terminar a vonversao
            valor = (10*5.0*((ADRESH<<8)+ADRESL))/1023;//Calcula o valor para simular a temperatura
            
            verifica();//A cada 1 minuto é feita a verificação
        }
        if(min > 59){
            min = 0;
            hora++;
        }
        if(hora > 23){
            hora = 0;
            dias++;
        }
        
        TMR0 = 8690;//timer inicial configurado para melhorar precisão
        
        CLRWDT();//Limpa o temporizador do WDT
        
        INTCONbits.TMR0IF = 0;//limpa a flag
    }
    
    if(INTCON3bits.INT1IE && INTCON3bits.INT1IF){//INT0 para fazer reset geral forçado no dispositivo
        flreset = 1;
        INTCONbits.TMR0IE = 0; //Desativa o timer, relogio trava até o WDT reiniciar o programa
                               //Com o timer0 desativado, o temporizador do WDT não é limpo
                               //Logo, o dispositivo é reiniciado
        INTCON3bits.INT1IF = 0;
    }
    
}

void teclado(){//Função para uso do teclado matricial
    PORTB = 0b11111111;//Porta B como entrada (colunas da matriz)
    PORTCbits.RC6 = 1;//Porta RC6 como saída, iniciando em 1 (linha 1)
    PORTCbits.RC7 = 1;//Porta RC7 como saída, iniciando em 1 (linha 2)
    int auxtec = 1;
    
    while(auxtec){
        if(PORTCbits.RC6 && auxctrl == 0x01){//Varre a primeira linha 
            auxctrl = 0x02;
            PORTCbits.RC6 = 0x00;
            PORTCbits.RC7 = 0x01;
            
            for(int i=0;i<100;i++)
                if(PORTCbits.RC6 == 0 && PORTBbits.RB3 == 0){
                    num = 1;
                    auxtec = 0;
                    break;
                }
            if(PORTCbits.RC6 == 0 && PORTBbits.RB4 == 0){
                num = 2;
                auxtec = 0;
                break;
            }
            if(PORTCbits.RC6 == 0 && PORTBbits.RB5 == 0 && hcontrol){
                num = 3;
                auxtec = 0;
                break;
            }
            if(PORTCbits.RC6 == 0 && PORTBbits.RB6 == 0 && hcontrol && h2control){
                num = 4;
                auxtec = 0;
                break;
            }
            if(PORTCbits.RC6 == 0 && PORTBbits.RB7 == 0 && hcontrol && h2control){
                num = 5;
                auxtec = 0;
                break;
            }
            __delay_ms(70);
        }
        else if(PORTCbits.RC7 && auxctrl == 0x02){//Varre a segunda linha
            auxctrl = 0x01;
            PORTCbits.RC6 = 0x01;
            PORTCbits.RC7 = 0x00;
            
            for(int i=0;i<100;i++)
                if(PORTCbits.RC7 == 0 && PORTBbits.RB3 == 0 && hcontrol && h2control && mcontrol){
                    num = 6;
                    auxtec = 0;
                    break;
                }
            if(PORTCbits.RC7 == 0 && PORTBbits.RB4 == 0 && hcontrol && h2control && mcontrol){
                num = 7;
                auxtec = 0;
                break;
            }
            if(PORTCbits.RC7 == 0 && PORTBbits.RB5 == 0 && hcontrol && h2control && mcontrol){
                num = 8;
                auxtec = 0;
                break;
            }
            if(PORTCbits.RC7 == 0 && PORTBbits.RB6 == 0 && hcontrol && h2control && mcontrol){
                num = 9;
                auxtec = 0;
                break;
            }
            if(PORTCbits.RC7 == 0 && PORTBbits.RB7 == 0){
                num = 0;
                auxtec = 0;
                break;
            }
            __delay_ms(70);
        }
        
        CLRWDT();//Limpa o temporizador do WDT
        
    }
    
    CLRWDT();//Limpa o temporizador do WDT
    
}

void iniciaDisp(){
    //Configurações para interrupções
    RCONbits.IPEN = 1; //Interrupções com prioridade
    INTCONbits.GIEH = 1; //Alta prioridade ativa
    INTCONbits.GIEL = 0; //Baixa prioridade desativada
    
    //Configurações INT0
    INTCON3bits.INT1IF = 0;//Limpa a flag de INT1
    INTCON3bits.INT1IP = 1;//INT1 com alta prioridade
    INTCON2bits.INTEDG1 = 0;//INT1 com borda de descida
    INTCON3bits.INT1IE = 1;//Ativa INT1
    
    //Configuracoes conversor AD
    TRISAbits.RA1 = 1; //Configura RA1 como entrada
    ADCON0 = 0b00000000; //Inicializa o conversor AD desligado no canal AN0
    ADCON1 = 0b00001110; //Configura tensao referencia interna e AN0 analogico
    ADCON2 = 0b10111100; //Configura AD com 20TAD Fosc/4
    ADCON0bits.ADON = 1; //Ativa o conversor AD
    ADCON0bits.GO = 1;      //Faz a conversao
    while(!ADCON0bits.DONE);//Aguarda terminar a vonversao
    valor = (10*5.0*((ADRESH<<8)+ADRESL))/1023;
    
    verifica();
    
    //Configurações Timer 0
    INTCONbits.TMR0IF = 0;//Limpa a flag do timer0
    INTCON2bits.TMR0IP = 1;//Configura timer0 como alta prioridade
    T0CON = 0b10000011;//Timer0 com CLK interno, 16 bits
                       //e prescaler 1:16
    TMR0 = 8690;//Inicia o timer em 3036, para melhor precisão no resultado (1 segundo por clk)
                //Considerando o clock de 4GHz, conforme visto em aula
    INTCONbits.TMR0IE = 1;//Ativa a interrupção
    
    CLRWDT();//Limpa o temporizador do WDT
    
    while(1);
}

void resetDisp(){
    if(flreset){
        dias = 0;
        hora = 0;
        min = 0;
        seg = 0;
        int d1, d2, h1, h2, m1, m2, s1, s2;
        cursor_lcd_pos(0x80);
        escrever_lcd("Idade animais:");
        cursor_lcd_pos(0xC0);
        escrever_lcd("    00 dias");
        cursor_lcd_pos(0xC4);
        teclado();
        d1 = num;
        escrever_char(d1+48);
        teclado();
        d2 = num;
        escrever_char(d2+48);
        desliga_cursor();
        __delay_ms(1000);
        dias = (d1*10)+d2;
        limpa_lcd();
        liga_cursor();
        escrever_lcd("Definir horario:");
        cursor_lcd_pos(0xC0);
        escrever_lcd("     00:00");
        cursor_lcd_pos(0xC5);
        hcontrol = 0;
        teclado();
        hcontrol = 1;
        h1 = num;
        escrever_char(h1+48);
        if(h1 == 2)
            h2control = 0;
        teclado();
        h2control = 1;
        h2 = num;
        escrever_char(h2+48);
        hora = (h1*10)+h2;
        cursor_lcd_pos(0xC8);
        mcontrol = 0;
        teclado();
        mcontrol = 1;
        m1 = num;
        escrever_char(m1+48);
        teclado();
        m2 = num;
        escrever_char(m2+48);
        desliga_cursor();
        __delay_ms(1000);
        min = (m1*10)+m2;
        limpa_lcd();
    }
    flreset = 0;
    
    CLRWDT();//Limpa o temporizador do WDT
    
    iniciaDisp();
}

void main(void) {
    PIC_init();
    config_lcd();
    TRISB = 0b11111111;
    TRISCbits.RC6 = 0;
    TRISCbits.RC7 = 0;
    TRISCbits.RC0 = 0;
    
    CLRWDT();//Limpa o temporizador do WDT
    
    resetDisp();
    
    return;
}
