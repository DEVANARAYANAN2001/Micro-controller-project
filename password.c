
#include <xc.h>
#include "main.h"

static int num = 3;

int password(void) {
    unsigned char key;
    static unsigned int flag = 1, count, i = 0,back_count=0;
    static unsigned char arr[5] = {};
    while (1) {
        if (i < 4) {
            clcd_print(" ENTER PASSWORD ", LINE1(0));
            if (count++ < 1000)
                clcd_putch('_', LINE2(i));
            else if (count < 2000)
                clcd_putch(' ', LINE2(i));
            key = read_switches(STATE_CHANGE);
            if (MK_SW12 == key) 
            {
                arr[i] = '0';
                clcd_putch('*', LINE2(i++));
                for (long int i = 10000; i--;);
                for (long int i = 50000; i--;);
            } 
            else if (key == MK_SW11) 
            {
                arr[i] = '1';
                clcd_putch('*', LINE2(i++));
                for (long int i = 10000; i--;);
                for (long int i = 50000; i--;);
            }
           
        }
        else {
            if (!strcmp(arr, PASSWORD)) {
                i=0;
                num=3;
                //        CLEAR_DISP_SCREEN;
                //           clcd_print("CORRECT PASSWORD", LINE1(0));
                //         clcd_print("   SUCCESS   ", LINE2(0));
                //       for(long int wait = 50000; wait--;);
                return SUCCESS;
            } else if (flag == 3) {
                CLEAR_DISP_SCREEN;
                int n = 61;
                clcd_print("YOU ARE BLOCKED", LINE1(0));
                clcd_print(" WAIT...    SEC", LINE2(0));
                while (n--) {
                    clcd_putch(((n / 10) + '0'), LINE2(9));
                    clcd_putch(((n % 10) + '0'), LINE2(10));
                    for (long int i = 20; i--;)
                        for (long int i = 25000; i--;);
                }
                CLEAR_DISP_SCREEN;
                return FAILURE;
                //   password();
            } else {
                flag++;
                CLEAR_DISP_SCREEN;
                clcd_print(" Try Again ", LINE1(0));
                clcd_putch('0' + (--num), LINE2(0));
                clcd_print(" Attempt left ", LINE2(1));
                for (long int i = 20; i--;)
                    for (long int i = 50000; i--;);
                i = 0;

                CLEAR_DISP_SCREEN;
                clcd_print(" ENTER PASSWORD ", LINE1(0));
            }
        }
    }
}


