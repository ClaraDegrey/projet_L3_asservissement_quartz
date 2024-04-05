#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>

#include "VirtualSerial.h"
#include <util/delay.h>
extern USB_ClassInfo_CDC_Device_t VirtualSerial_CDC_Interface;
extern FILE USBSerialStream;
void pwm_configure()        // called once for initialization
{TCCR4A=0;
 TCCR4B=(1<<CS40);
 TCCR4C=0;
 TCCR4D=0;
 TC4H=0x03;
 OCR4C=150;//varie la fréquence
 TCCR4C|=0x09;              // Activate channel D
 DDRD|=1<<7; 
  
            // Set GPIO Output Mode
}
void pwmD_configure(short val) // Timer4 D: update duty cycle to val
{TC4H=(val>>8)&3;
 OCR4D=(char)(val&0xff);
}
int main (void){
	SetupHardware();
	CDC_Device_CreateStream(&VirtualSerial_CDC_Interface, &USBSerialStream);
	GlobalInterruptEnable();
	DDRE|=(1<<6);
	PORTE&=(~(1<<6));  
	 short res;
	 short d=0;
	 char s[8];
	pwm_configure();
	while (1){
		d=500;//if (d>1023) d=1; // varie le temps a l'etat haut
		pwmD_configure(d);
		_delay_ms(5);
		sprintf(s,"%04d ",d);
		fputs(s, &USBSerialStream);
		res=adc_read(7);
		sprintf(s,"%04d\r\n",res);
		fputs(s, &USBSerialStream);
		CDC_Device_ReceiveByte(&VirtualSerial_CDC_Interface);
		CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
		USB_USBTask();
	}
return 0;
}

