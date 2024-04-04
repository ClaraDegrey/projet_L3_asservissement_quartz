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
volatile uint16_t captureValue2=0;
volatile uint8_t captureFlag = 0;
volatile uint8_t d = 1;
// pmw
void pwm_configure()        // called once for initialization
{
 TCCR4B=(1<<CS40);
 TC4H=0x03;
 OCR4C=255;//varie la frèquence
 TCCR4C|=0x09;              // Activate channel D
 DDRD|=1<<7;
 
            // Set GPIO Output Mode
}
void adc_init() {
    DIDR0=0xff;
    ADMUX=(1<<REFS0);
    ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}
unsigned short adc_read(uint8_t channel) {
    channel &= 0x07;
    ADMUX=(ADMUX & 0xF8)|channel;
    ADCSRA |= (1<<ADSC);
    while(ADCSRA & (1<<ADSC));
return ADC;
}
void pwmD_configure(short val) // Timer4 D: update duty cycle to val
{TC4H=(val>>8)&3;
 OCR4D=(char)(val&0xff);
}
//input capture
ISR(TIMER1_CAPT_vect) {
    captureValue = ICR1;
    captureFlag = 1;
    d+=1;if (d>1023) d=1;
}
int main(void) {
    SetupHardware();
    CDC_Device_CreateStream(&VirtualSerial_CDC_Interface, &USBSerialStream);
    GlobalInterruptEnable();
    sei();
    DDRD &= ~(1 << DDD4);
    PORTD &= ~(1 << PORTD4);
    EICRA |= (1 << ISC01) | (1 << ISC00); // Déclencher sur front montant

    TIMSK1 |= (1 << ICIE1);
    TCCR1B |=(1<<CS10); //pas de prescaler;
    volatile uint16_t diff;
    //short res;
    //short d=0;
    //char s[8];
    pwm_configure();
    adc_init();

    while (1) {
    //d+=1;if (d>1023) d=1; // varie le temps a l'etat haut
    //pwmD_configure(d);
     //_delay_ms(2000);
    //sprintf(s,"%04d ",d);
    //fputs(s, &USBSerialStream);
    //res=adc_read(7);
    //sprintf(s,"%04d\r\n",res);
    //fputs(s, &USBSerialStream);
       
        //input capture
        if (captureFlag) {
            pwmD_configure(d);
            diff=captureValue-captureValue2;
            if ((captureValue-captureValue2)<0){
            diff=65536 + diff;
        }
            captureValue2=captureValue;
            char buffer[10];
            sprintf(buffer, "%u ", diff); // Conversion de captureValue en hexadécimal
            fputs(buffer, &USBSerialStream);
            sprintf(buffer, "%u\r\n", d); // Conversion de captureValue en hexadécimal
            fputs(buffer, &USBSerialStream);
            CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
            USB_USBTask();
            captureFlag = 0;
        }
    }
    return 0;
}





 
