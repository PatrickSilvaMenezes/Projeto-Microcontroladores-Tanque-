// CODIGO PARA LER O ESTADO DE DOIS SENSORES E FAZER O CONTROLE DE NÍVEL, E INDICAR EM DISPLAY DE 7 SEGMENTOS
// considerando valvulas NF e sensores NA
//obs: os botoes do simulador picsim são multiplexadas
//Codigo do tanque

//obs: as estradas est?o multiplexadas
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "lcd.h"
#include "config.h"
#include "adc.h"
#include "rotina.h"
#define _XTAL_FREQ 4000000 // Especifique o FREQ de cristal XTAL


void main() 
{
    // CONFIGURANDO OS SENSORES
    
    TRISB = 0b00011000;
    PORTB = 0b00011000;
    // Configuração Valvulas
        // RB3 -> entrada sensor nivel baixo NB
        // RB4 -> entrada sensor nivel alto NA
     
    // Configuração Aquecedor
        // RB7 -> Aquecedor
  
    // CONFIGURANDO QUAIS PORTAS SERÃO ANALOGICAS OU DIGITAIS
    ADCON1 = 0x06;          //pinos AD como i/o
    //CONFIGURANDO DISPLAY LCD 2x16
    TRISD = 0; //configura todos pinos do portd como saída
    TRISE = 0; // configura todos pinos do porte como saída 
    PORTD = 0x00;// configura o display desligado
    
  
    
    // CONFIGURANDO VALVULAS DE SAÍDA/ENTRADA
    TRISCbits.RC0=0;        //saida valvula de entrada VE - rel? 1
    TRISEbits.RE0=0;        //saida valvula de sa?da VS - rel? 2
    
    // CONFIGURANDO MISTURADOR (COOLER)
    TRISCbits.RC2=0;        // Cooler como sa?da
    PORTCbits.RC2=0;        // Inicializa o cooler desligado
    TRISA=0;                //saida habilita display
    TRISD=0;                //saida segmentos do display
    
    // COMEÇA ENCHENDO O TANQUE
    PORTEbits.RE0=0;        //desliga a valvula de sa?da rele 2      
    PORTCbits.RC0=1;        //liga a valvula de entrada rele 1
    //PORTA=0b00100000;       //habilita display
    //PORTD=0b11111001;       //escreve E no display (enchendo))
    
    // Configurando Display
 
    Inicializa_LCD();   // Iniciliza Display

    while(1) {
        if (PORTBbits.RB4==0){      // como o RB4 ? um bot?o multiplexado, por isso nivel alto
            turnon_coolerandheater();  // misturo e logo em seguida ligo a valvula de sáida
            potentiometer_temperature();
            turnoff_coolerandheater();
            __delay_ms(200);
            Comando_LCD(01); // limpa a tela do display
            printDisplayLCD(1,1, "Esvaziando!");    
            PORTEbits.RE0=1;  //liga a valvula de saida-rele 2;   
            __delay_ms(600);
   
 
        }
        
        else if (PORTBbits.RB3==1){ // quando estiver em nivel baixo
            PORTEbits.RE0=0; // nao ativa valvula de saida
            Comando_LCD(01); // limpa a tela do display
            printDisplayLCD(1,1, "Enchendo!");    
            PORTCbits.RC0=1; // ativa valvula de entrada
            __delay_ms(100);
        }               
    }
}