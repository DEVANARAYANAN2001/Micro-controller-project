
#include <xc.h> 
#include "main.h"


void write_extern_eeprom(unsigned char address,unsigned char data)
{
	i2c_start();
	i2c_write(EEPROM_WRITE);
	i2c_write(address);
	i2c_write(data);
	i2c_stop();
    __delay_ms(10);
}

unsigned read_extern_eeprom(unsigned char address)
{
	unsigned char data;

	i2c_start();
	i2c_write(EEPROM_WRITE);
	i2c_write(address);
	i2c_rep_start();
	i2c_write(EEPROM_READ);
	data = i2c_read();
	i2c_stop();

	return data;
}
