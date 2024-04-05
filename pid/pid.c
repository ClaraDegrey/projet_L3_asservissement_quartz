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
volatile uint8_t captureFlag = 0;
// pmw
void pwm_configure()        // called once for initialization
{
 TCCR4B=(1<<CS40);
 TC4H=0x03;
 OCR4C=255;//varie la fréquence
 TCCR4C|=0x09;              // Activate channel D
 DDRD|=1<<7;
          // Set GPIO Output Mode
}

void pwmD_configure(short val) // Timer4 D: update duty cycle to val
{TC4H=(val>>8)&3;
 OCR4D=(char)(val&0xff);
}
//input capture
ISR(TIMER1_CAPT_vect) {
    captureValue = ICR1;
    captureFlag = 1;
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
    volatile long diff;
    int16_t d = 512;
    uint16_t captureValue2=0;
    pwm_configure();
    short fc=9964;
    signed short erreur=0;
    signed short erreur2=0;
    char buffer[10];
    pwmD_configure(d);

    while (1) {
       //input capture
        if (captureFlag) {
           
            diff=captureValue-captureValue2;
            sprintf(buffer, "%ld ", diff); 
            fputs(buffer, &USBSerialStream);

            
          if (diff<0) diff+=65536;
          erreur2=erreur;
          erreur=fc-diff;
          
          /////////////////////////////////////////////////////
          sprintf(buffer, "%d ", erreur); 
            fputs(buffer, &USBSerialStream);
            /////////////////////////////////////////////////:
            /////////////////////////////////////////////////////
          sprintf(buffer, "%d ", erreur2); 
            fputs(buffer, &USBSerialStream);
            /////////////////////////////////////////////////:
          
          d+=((108*(erreur2-erreur))/100+(56*erreur)/100);
           if (d<0){
              d=0;
            }else if (d>1023){
                d=1023;
             }
            
            captureValue2=captureValue;
            
            pwmD_configure(d);
            ////////////////////////////////////////////
            sprintf(buffer, "%ld ", diff); 
            fputs(buffer, &USBSerialStream);
            sprintf(buffer, "%u\r\n", d); 
            fputs(buffer, &USBSerialStream);
            CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
            USB_USBTask();
            ///////////////////////////////////////////////////////:
            
            captureFlag = 0;
        }
    }
    return 0;
}

