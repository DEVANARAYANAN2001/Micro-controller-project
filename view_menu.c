#include <xc.h>
#include "main.h"

unsigned int view_start_flag = 0, view_ind_flag=0;

void view_menu(unsigned int over_flow,unsigned int lap) {
    unsigned char view_key,data;
    unsigned int view_timer1 = 0, view_timer2 = 0;
    /*  clcd_print("helllo", LINE2(2));
        while(1);
        for(long int i =1000;i--;)
        for(long int i=1000;i--;);*/
    if (over_flow == 0) 
    {
        view_start_flag = 0;
        view_ind_flag = 0;
    } 
    else
        view_start_flag = lap;
    while (1)
    {
        view_key = read_switches(LEVEL_CHANGE);

        if (view_key == MK_SW12) 
        {
            view_timer1++;
        } 
        else if (view_timer1 > 0 && view_timer1 > 500) 
        {
            if (view_ind_flag < lap) 
            {
                view_ind_flag++;
            }
        } 
        else if (view_timer1 > 500) 
        {
            return;
        }

        if (view_key == MK_SW11) 
        {
            view_timer2++;
        } 
        else if (view_timer2 > 0 && view_timer2 > 500) 
        {
            if (view_ind_flag > 0) 
            {
                view_ind_flag--;
            }
        }
        clcd_putch(view_start_flag + 48, LINE2(0));
        clcd_putch(' ', LINE2(1));

        data = read_extern_eeprom(((view_start_flag+view_ind_flag) %10)/10);
        clcd_putch(data, LINE2(2));

                data = read_extern_eeprom(((view_start_flag+view_ind_flag) %10)/10+1);
        clcd_putch(data, LINE2(3));

        clcd_putch(':', LINE2(4));
        
                        data = read_extern_eeprom(((view_start_flag+view_ind_flag) %10)/10+2);
        clcd_putch(data, LINE2(5));

                        data = read_extern_eeprom(((view_start_flag+view_ind_flag) %10)/10+3);
        clcd_putch(data, LINE2(6));

        clcd_putch(':', LINE2(7));

                               data = read_extern_eeprom(((view_start_flag+view_ind_flag) %10)/10+4);
        clcd_putch(data, LINE2(8));

                                data = read_extern_eeprom(((view_start_flag+view_ind_flag) %10)/10+5);
        clcd_putch(data, LINE2(9));

        clcd_putch(' ', LINE2(10));

                                data = read_extern_eeprom(((view_start_flag+view_ind_flag) %10)/10+6);
        clcd_putch(data, LINE2(11));

                               data = read_extern_eeprom(((view_start_flag+view_ind_flag) %10)/10+7);
        clcd_putch(data, LINE2(12));


        clcd_putch(' ', LINE2(13));

                                data = read_extern_eeprom(((view_start_flag+view_ind_flag) %10)/10+8);

        clcd_putch(data, LINE2(14));

                                data = read_extern_eeprom(((view_start_flag+view_ind_flag) %10)/10+9);

        clcd_putch(data, LINE2(15));

    }
}