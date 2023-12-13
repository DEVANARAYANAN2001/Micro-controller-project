#include <xc.h>
#include "main.h"

unsigned char start_flag = 0, ind_flag = 0;
extern unsigned int over_flow = 0, lap = 0;
unsigned char stor[10];
extern unsigned int speed,dash_board_flag=1,view_flag=0,menu_flag=0,pass_flag=1,clear_flag=0,change_pass_flag=0,down_flag=0,set_time_flag=0;

void menu(void) {
    char menu[][17] = {"VIEW LOG  ", "CLEAR LOG    ", "DOWNLOAD LOG  ", "SET TIME      ", "CHANGE PASS   "};
    unsigned char key1;
    long int menu_timer = 0, menu_timer2 = 0,cur_flag=0;

    while (1) {
        key1 = read_switches(LEVEL_CHANGE);
        if (key1 == MK_SW12) 
        {
            menu_timer2++;
        }
        else if ((menu_timer2 > 0) && (menu_timer2 < 300)) 
        {
            menu_timer2 = 0;
            if (start_flag == 0) 
            {
                start_flag = 1;
            }
            else if (ind_flag < 3) 
            {
                ind_flag++;
            }
            cur_flag=start_flag+ind_flag;
        } 
        else if (menu_timer2 > 300) 
        {
                        start_flag = ind_flag = 0;

            menu_timer2 = 0;
            menu_flag=0;
            view_flag=0;
            clear_flag=0;
            change_pass_flag=0;
            set_time_flag=0;
            pass_flag=1;
            dash_board_flag=1;
            CLEAR_DISP_SCREEN;
            return;
        }
        else
            menu_timer2 = 0;

        
        if (key1 == MK_SW11) 
        {
            menu_timer++;
        } 
        else if ((menu_timer > 0) && (menu_timer < 500)) 
        {
            menu_timer = 0;
            if (start_flag == 1) 
            {
                start_flag = 0;
            }
            else if (ind_flag > 0) 
            {
                ind_flag--;
            }
            cur_flag=start_flag+ind_flag;
        } 
        
        else if (menu_timer > 500) 
        {
                        start_flag = ind_flag = 0;

            menu_timer = 0;
            if (cur_flag == 0) 
            {
                CLEAR_DISP_SCREEN;
                menu_flag=0;
                view_flag=1;
                clear_flag=0;
                pass_flag=1;
                return;
            }
            else if (cur_flag == 1) 
            {
                clear_flag = 1;
                menu_flag = 0;
                view_flag = 0;
                pass_flag=0;
                return;
            }
            else if (cur_flag == 2) 
            {
                clear_flag = 0;
                menu_flag = 0;
                view_flag = 0;
                pass_flag=0;
                down_flag=1;
                change_pass_flag=0;
                return;
            }
            else if (cur_flag == 3) 
            {
                clear_flag = 0;
                menu_flag = 0;
                view_flag = 0;
                pass_flag=0;
                change_pass_flag=0;
                set_time_flag=1;
                pass_flag=0;
                return;
            }
             else if (cur_flag == 4) 
             {
                clear_flag = 0;
                menu_flag = 0;
                view_flag = 0;
                pass_flag=0;
                change_pass_flag=1;
                return;
            } 
            
            
            
        } else
            menu_timer = 0;


        //CLEAR_DISP_SCREEN;
        if (start_flag == 0) 
        {
            clcd_putch('*', LINE1(0));
            clcd_putch(' ', LINE2(0));
        } else {
            clcd_putch(' ', LINE1(0));
            clcd_putch('*', LINE2(0));
        }

        clcd_print(menu[ind_flag], LINE1(2));
        clcd_print(menu[ind_flag + 1], LINE2(2));
    }
}
