/*
 * File:   storing.c
 * Author: Admin
 *
 * Created on December 10, 2023, 7:22 PM
 */


#include <xc.h>
#include "main.h"
extern unsigned int over_flow = 0, lap = 0;
extern unsigned char stor[10];
unsigned int eeprom_address1=0X00;
extern unsigned char eeprom_address;
extern unsigned int clear_flag,menu_flag,view_flag;


void storing(unsigned char *event, unsigned char*time, int speed) {
    stor[0] = time[0];
    stor[1] = time[1];
    stor[2] = time[3];
    stor[3] = time[4];
    stor[4] = time[6];
    stor[5] = time[7];
    stor[6] = event[0];
    stor[7] = event[1];
    stor[8] = (speed / 10) + 48;
    stor[9] = (speed % 10) + 48;

    for (int i = 0; i < 10; i++) 
    {
        write_extern_eeprom(lap * 10 + i, stor[i]);
    }
    lap++;
    if (lap == 10) {
        lap = 0;
        over_flow = 1;
    }
}


void clear_log()
{
            for(int i=0;i<100;i++)
                   write_extern_eeprom(eeprom_address1++,' ');
    CLEAR_DISP_SCREEN;
    eeprom_address=0X00;
    clcd_print("LOGS CLEARED",LINE1(0));
    for(int wait=10000;wait--;)
        for(int wait=50;wait--;);
       view_flag=0;
    clear_flag=0;
    menu_flag=1;
    CLEAR_DISP_SCREEN;
    return;
            
}


 
