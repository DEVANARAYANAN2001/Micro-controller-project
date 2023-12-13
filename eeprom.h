#ifndef EEPROM_H
#define EEPROM_H

#define EEPROM_READ 0xA1
#define EEPROM_WRITE 0xA0


void write_extern_eeprom(unsigned char address,unsigned char data); 
unsigned read_extern_eeprom(unsigned char address);
void storing(unsigned char *event,unsigned char*timer,int speed);
#endif