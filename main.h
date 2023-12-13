#ifndef MAIN_H
#define MAIN_H

#include <xc.h>
#include "mkp.h"
#include "clcd.h"
#include "adc.h"
#include "dash_board_display.h"
#include "password.h"
#include "i2c.h"
#include "rtc.h"
#include "eeprom.h"
#include "string.h"



#define CLEAR_LOG 0
#define LED1				RB0
#define ON				1
#define OFF				0
#define SUCCESS 1
#define FAILURE 0

#define SECOND 0X00
#define MINUTE 0X01
#define HOUR 0x02

//#define flag1 FGEARFLAG
//#define flag2 RGEARFLAG

void init_config(void);
void view_log(unsigned int,unsigned int);
void menu();
void view_display(unsigned char eeprom_address,unsigned int view_ind_flag);
void clear_log();
void download_log();
void set_time_log();
void change_password_log();
void storing(unsigned char *event, unsigned char*time, int speed);





#endif

