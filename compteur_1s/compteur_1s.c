#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include "VirtualSerial.h"

extern USB_ClassInfo_CDC_Device_t VirtualSerial_CDC_Interface;
extern FILE USBSerialStream;

volatile uint16_t captureValue;
uint32_t captureValue2=16000000;
uint16_t diff;
volatile uint8_t captureFlag = 0;

ISR(TIMER1_CAPT_vect) {
    captureValue = ICR1;
    captureFlag = 1;
}



void adc_init() {
    // Initialisation de l'ADC
}
 

int main(void) {
    SetupHardware();
    CDC_Device_CreateStream(&VirtualSerial_CDC_Interface, &USBSerialStream);
    GlobalInterruptEnable();
    adc_init();
    sei();
    // Configuration du Timer1 pour le mode de capture
    // Configurer Timer1 avec le prescaler et le mode de fonctionnement souhaités
    // Activer le mode de capture en définissant les bons bits de configuration dans TCCR1B

    // Configurer le pin d'entrée pour la capture (par exemple, pin D8 sur Arduino Uno)
    // Exemple pour le front montant : configurer le pin en entrée sans résistance de tirage interne
    DDRD &= ~(1 << DDD4);
    PORTD &= ~(1 << PORTD4); //lire signal créneau en entrée

    // Configurer le registre EICRA pour déclencher la capture sur front montant
    EICRA |= (1 << ISC01) | (1 << ISC00); // Déclencher sur front montant

    // Activer l'interruption de capture Timer1
    TIMSK1 |= (1 << ICIE1);
    TCCR1B |=(1<<CS10); //pas de prescaler;
    
	

    while (1) {
        if (captureFlag) {
			diff=captureValue-captureValue2;
			captureValue2=captureValue;
			if((captureValue-captureValue2)<0){
				diff=65536+diff;
			}
            char buffer[10];
            sprintf(buffer, "%u\r\n", diff); // Conversion de captureValue en hexadécimal
            fputs(buffer, &USBSerialStream);
            CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
            USB_USBTask();
            captureFlag = 0;
        }
    }
    return 0;
}
