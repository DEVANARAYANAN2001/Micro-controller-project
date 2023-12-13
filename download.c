/*
 * File:   download.c
 * Author: Admin
 *
 * Created on December 10, 2023, 8:30 PM
 */


#include <xc.h>
#include "main.h"
#include "uart.h"

extern unsigned int menu_flag,down_flag;

void download_log()
{
    unsigned char data,address=0x00;
    for(int i=0;i<10;i++)
    {
        putch(i + '0');
        putch (' '); 
        for(int j=0;j<14;j++)
        {
            if(j==8 || j==11)
            putch(' ');
            else if(j==2||j==5)
                putch(':');
            else
            {
                data = read_extern_eeprom(address++);
            putch(data);
            }
        }
        puts("\n\r");
    }
    down_flag=0;
    menu_flag=1;
    return;
}

