
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

#include <xc.h>

/*
 *                              OBSERVAÇÃO
 * Usei a própria porta B para controlar o motor de passos
 * No caso, utilizei os 4 bits mais significativos
 * 
 * No simulador configurei as propriedades do motor de passo da seguinte forma:
 * Pin 1: RB7
 * Pin 2: RB6
 * Pin 3: RB5
 * Pin 4: RB4
 * 
 */

int change = 1;
int aux1 = 16;
int aux2 = 16;
int flag = 1;

void __interrupt(high_priority) funcIntHigh(void){
    if(INTCON3bits.INT1IE && INTCON3bits.INT1IF){
        change = !change;           
        if(change){                 
            aux1 = 16;              
            aux2 = 16;              
        }else{                      
            aux1 = 128;
            aux2 = 128;
        }
        
        INTCON3bits.INT1IF = 0; 
    }
}

void main(void) {
    TRISB = 0x0F;//Configura os pinos RB7:RB4 como saída (para o motor de passo)
                 //e os pinos RB3:RB0 como entrada (para usar botão RB1)
    T1CON = 0b11110100;//Timer 1 com prescaler 1:8 clock interno Fosc/4 
    TMR1 = 0x0000;//Zerar o valor do timer 1
    CCP2CON = 0b00001011;//CCP2 para reiniciar o timer quando ficar igual a CCPR2
    CCPR2L = 0xFF;
    CCPR2H = 0x0F; //CCPR2 = 4.095
    T1CONbits.TMR1ON = 1;//Ativa o timer
    
    //Configurando Interrupções e INT1
    RCONbits.IPEN = 1;//Configura para tratar interrupções de acordo com nivel de prioridade
    INTCONbits.GIEH = 1;//Habilita alta prioridade
    INTCONbits.GIEL = 0;//Desabilita baixa prioridade
    INTCON3bits.INT1IP = 1;//Configura INT1 como alta prioridade
    INTCON2bits.INTEDG1 = 0;//Borda de descida
    INTCON3bits.INT1IF = 0;//Limpa a flag de INT1
    INTCON3bits.INT1IE = 1;//Habilita INT1
    
    while(1){
        
        /*if(PORTBbits.RB1 == 0){       //Dá problema pois depende do tempo
            change = !change;           //que o botão fica pressionado
            if(change){                 
                aux1 = 16;              
                aux2 = 16;              //Preferi fazer com
            }else{                      //a interrupção INT1 como RB1
                aux1 = 128;             //que quando o botão é precionado
                aux2 = 128;             //realiza a ação somente uma vez
            }
        }*/
        
        if(PIR2bits.CCP2IF){
            PORTB = aux1 | aux2;//Envia o comando para o motor de passo
            if(change){
                
                if(flag){
                    aux1 = aux1 << 1;
                    flag = 0;
                }else{
                    aux2 = aux2 << 1;
                    flag = 1;
                }
                if(aux1 > 128)
                    aux1 = 16;
                if(aux2 > 128)
                    aux2 = 16;
            }else if(!change){
                if(flag){
                    aux1 = aux1 >> 1;
                    flag = 0;
                }else{
                    aux2 = aux2 >> 1;
                    flag = 1;
                }
                if(aux1 < 16)
                    aux1 = 128;
                if(aux2 < 16)
                    aux2 = 128;
            }
            PIR2bits.CCP2IF = 0;
        }
    }
    return;
}
