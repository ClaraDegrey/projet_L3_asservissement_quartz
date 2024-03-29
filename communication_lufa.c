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

// Lightweight USB Framework for AVRs, www.fourwalledcubicle.com/LUFA.php

 int main(void)
 {
int values[3]={4, 5, 7};
char buffer[50];
int i;

buffer[0]='\0';

for(i =0; i<3; i++){
	sprintf(buffer + strlen(buffer), "%d", values[i]);
}

//sprintf(buffer, "%d, %d, %d", values[0], values[1], values[2]);
printf("%s", buffer); 
printf("%s"," "); 
 //char ReportString[20] = "1578\r\n\0";

 SetupHardware();
 /* Create a regular character stream for the interface so that it can be used with the stdio.h functions */
 CDC_Device_CreateStream(&VirtualSerial_CDC_Interface, &USBSerialStream);
 GlobalInterruptEnable();

 for (;;)
 {
 //fprintf(&USBSerialStream,"␣");
 fputs(buffer, &USBSerialStream);

 // les 3 lignes ci-dessous pour accepter les signaux venant du PC
 CDC_Device_ReceiveByte(&VirtualSerial_CDC_Interface);

 CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
 USB_USBTask();
 _delay_ms(500);
 }
 }
