MCU=atmega32u4
EXEC=communication_lufa
DFU=dfu-programmer
	

all:	$(EXEC).hex

$(EXEC).out: $(EXEC).o 
	avr-gcc -L /home/etudiant/lufa/VirtualSerial_lib/ -mmcu=atmega32u4 -g -Os -o $(EXEC).out $(EXEC).o -lVirtualSerial
	avr-objdump -dSt $(EXEC).out > $(EXEC).lst

$(EXEC).hex: $(EXEC).out
	avr-objcopy -O binary $(EXEC).out $(EXEC).bin
	avr-objcopy -O ihex $(EXEC).out $(EXEC).hex

$(EXEC).o: $(EXEC).c
	avr-gcc -I /home/etudiant/lufa/VirtualSerial_example/ \
        -I /home/etudiant/lufa/lufa-LUFA-140928 -mmcu=atmega32u4 \
        -DF_USB=16000000UL -std=gnu99 -Os -Wall -c $(EXEC).c

clean:
	rm *.o $(EXEC).out *.lst *aux *log

install: $(EXEC).hex
		$(DFU) $(MCU) erase
		$(DFU) $(MCU) flash $(EXEC).hex
		$(DFU) $(MCU) reset
		
	
