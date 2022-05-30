/* 
 * File:   rotina.h
 * Author: Patrick
 *
 * Created on 30 de Maio de 2022, 15:20
 */

#ifndef ROTINA_H
#define	ROTINA_H

void printDisplayLCD(int line, int  col, char* text){
    Posiciona_LCD(line,col);  //linha, coluna
    Escreve_LCD(text);
    __delay_ms(100);    
}
void turnon_coolerandheater() {//liga misturador e aquecedor
    PORTBbits.RB7 = 1; // liga led representando o aquecedor
    PORTC=0x00;         //mantem a valvula VE fechada (N?O ENERGIZADA, 0V)
    PORTE=0b00000000;   //mantem a valvula VS fechada (N?O ENERGIZADA, 0V)
    PORTCbits.RC2= 1; // liga misturador
    Comando_LCD(01);// limpa a tela do display
    printDisplayLCD(1,1, "Misturando");    
    printDisplayLCD(2,1, "e Aquecendo!");
     __delay_ms(300); 
    
}
void turnoff_coolerandheater(){ //desliga misturador e aquecedor
    PORTCbits.RC2=0; // desliga misturador
    PORTBbits.RB7 = 0; // desliga o led representando o aquecedor
}

void potentiometer_temperature(){
#define vref 5.00 //voltagem de referencia
    float voltagem;
    float temperatura = 20;
    unsigned int digital;
    char temperatura_texto[10];
    Comando_LCD (01); // limpa a tela do display
    Inicializa_ADC(); //configurar conversor a/d
    printDisplayLCD(1,1,"Temperatura:");
    printDisplayLCD(2,8,"Celsius");

   //temperatura varia de 20 a 80
    while(temperatura!=80){
        digital = Ler_ADC(); // ler em analogico do potenciometro e converter para digital
        voltagem = digital*((float)vref/(float)1023);
        
        temperatura = 12*voltagem+20; //conversão da voltagem na temperatura
        sprintf(temperatura_texto,"%.2f",temperatura); // conversão do valor da temperatura em texto
        
        printDisplayLCD(2,1, temperatura_texto);
    }
}

#endif	/* ROTINA_H */

