/*
 * File   : main.c
 * Author : R DEVANARAYANAN
 * TITLE  : CAR BLACK BOX
 * DATE   : 12 DEC 2023
 *
 */

#include <xc.h>
#include "main.h"
#include "uart.h"

static int ind = 0, switch_flag = 0;
static char Fgear[][3] = {"C ", "GN", "GR", "G1", "G2", "G3", "G4", "ON"};
unsigned char time[9];
unsigned int over_flow = 0, lap = 0;
unsigned int speed,dash_board_flag=1,view_flag=0,menu_flag=0,pass_flag=1,clear_flag=0,change_pass_flag=0,down_flag=0,set_time_flag=0;
unsigned char event[3];

void init_config(void) {
    init_matrix_keypad();
    ADCON1 = 0x0F;
    init_adc();
    init_i2c();
    init_ds1307();
    init_clcd();
    init_uart();
}

void main(void) {
    init_config();

    unsigned char key,keyy;
    unsigned short adc_reg_val;
    while (1) {
        adc_reg_val = read_adc(CHANNEL4);
        speed = adc_reg_val / 10.33;
        get_time();
        key = read_switches(STATE_CHANGE);
        if (key != ALL_RELEASED) {
            switch_flag = 1;
        }
        if (switch_flag == 0) 
        {
            switch_flag = 1;
            strcpy(event, Fgear[7]);
            storing(event, time, speed);
        }
        if (key == MK_SW1) {
            strcpy(event, Fgear[0]);
            storing(event, time, speed);
            ind = 0;
        }
        if (key == MK_SW2) {
            if (ind++ < 6) {
                strcpy(event, Fgear[ind]);
                storing(event, time, speed);

            } else {
                ind--;
            }
        }
        if (key == MK_SW3) {
            if (ind-- >= 2) {
                strcpy(event, Fgear[ind]);
                storing(event, time, speed);
            }
            else {
                ind++;
            }
        } 
        
        else if (key == MK_SW11 && pass_flag==1) 
        {
            CLEAR_DISP_SCREEN;
            dash_board_flag = 0;
            menu_flag=1;
           if(password() == SUCCESS) 
            {
                CLEAR_DISP_SCREEN;
                dash_board_flag=0;
               
            }
        }
        if (dash_board_flag==1) 
        {
            dash_board_display(event, time, speed);
        }
        if(menu_flag==1)
        {
            menu();
        }
       
         if (view_flag == 1) 
        {
            view_log(lap, over_flow);
            //mainfl = 0;
        }
        if (clear_flag == 1) 
        {
            clear_log();
        }
        if (down_flag == 1) 
        {
            CLEAR_DISP_SCREEN;
            download_log();
        }
        if (set_time_flag == 1) 
        {
            CLEAR_DISP_SCREEN;
            set_time_log();
        }
        if (change_pass_flag == 1) 
        {
            CLEAR_DISP_SCREEN;
            //clcd_print("hi all",LINE1(0));
            change_password_log();
        }
        //  
        //clcd_putch((sp/10)+'0', LINE2(14)); 
        //clcd_putch((sp%10)+'0' ,LINE2(15));
        //clcd_print(time,LINE2(0));
    }
    return;
        
        
}