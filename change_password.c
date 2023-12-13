/*
 * File:   change_password.c
 * Author: Admin
 *
 * Created on December 10, 2023, 8:32 PM
 */



#include <xc.h>
#include<string.h>
#include"main.h"
//static int attempt = 3;
extern char pass[5];
extern unsigned int menu_flag,change_pass_flag;
void change_password_log()
{
unsigned char key;
        unsigned int i=0, j=0, count=0, count1=0;
        unsigned char newpw[5] = {}, cnewpw[5] = {};
    while (1) {

        if (i < 4) {
            clcd_print("Enter new password", LINE1(0));
            if (count++ < 1000)
                clcd_putch('_', LINE2(i));
            else if (count < 2000)
                clcd_putch(' ', LINE2(i));
            key = read_switches(STATE_CHANGE);
            if (key == MK_SW11) {
                clcd_putch('*', LINE2(i));
                newpw[i++] = '0';

            } else if (key == MK_SW12) {
                clcd_putch('*', LINE2(i));
                newpw[i++] = '1';
            }
            //        if(i==3)
            //            new_flag=1;
        } else if (j < 4) {
            if(j==0)
            CLEAR_DISP_SCREEN;
            clcd_print("Re-enter password", LINE1(0));
            if (count1++ < 1000)
                clcd_putch('_', LINE2(j));
            else if (count1 < 2000)
                clcd_putch(' ', LINE2(j));
            key = read_switches(STATE_CHANGE);
            if (key == MK_SW11) {
                clcd_putch('*', LINE2(j));
                cnewpw[j++] = '0';

            } else if (key == MK_SW12) {
                clcd_putch('*', LINE2(j));
                cnewpw[j++] = '1';
            }
        } else {
            CLEAR_DISP_SCREEN;
            if (strcmp(newpw, cnewpw) == 0) {
                //strcpy(pass, newpw);
                for(int i=0;i<4;i++)
        write_extern_eeprom(change_pass_flag++,cnewpw[i]);
        change_pass_flag=120;
                clcd_print("CHANGED PASSWORD", LINE1(0));
                clcd_print("SUCCESSFULLY", LINE2(0));
                for (int wait = 10000; wait--;)
                    for (int wait = 50; wait--;);
                    menu_flag=1;
                     CLEAR_DISP_SCREEN;
                    return;
            } else {
                clcd_print("PASSWORD", LINE1(0));
                clcd_print("MISMATCH", LINE2(0));
                for (int wait = 10000; wait--;)
                    for (int wait = 50; wait--;);
                    menu_flag=1;
                     CLEAR_DISP_SCREEN;
                    return;
            }

        }
    }
}
