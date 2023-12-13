#include <xc.h>
#include "main.h"

unsigned int view_start_flag = 0, view_ind_flag = 0;
unsigned char data, eeprom_address;

void view_log(unsigned int lap, unsigned int over_flow) {
    CLEAR_DISP_SCREEN;
    clcd_print("Logs            ", LINE1(0));
    unsigned char view_key;
    unsigned int view_timer1 = 0, view_timer2 = 0;
    if (over_flow == 0) {
        view_start_flag = 0;
        view_ind_flag = 0;
    } else {
        view_start_flag = lap;
        view_ind_flag = 0;
    }

    while (1) {
        view_key = read_switches(LEVEL_CHANGE);
        if (view_key == MK_SW12) {
            view_timer1++;
        } else if (view_timer1 > 0 && view_timer1 < 300) {
            view_timer1 = 0;
            if (over_flow == 0) {
                if (view_ind_flag < lap - 1) {
                    view_ind_flag++;
                    eeprom_address = (((view_start_flag + view_ind_flag) % 10)*10);
                }
            }
            else {
                if (view_ind_flag < 9) {
                    view_ind_flag++;
                    eeprom_address = (((view_start_flag + view_ind_flag) % 10)*10);
                }
            }
        } else if (view_timer1 > 300) {
            view_timer1 = 0;
            CLEAR_DISP_SCREEN;
            return;
        }
        if (view_key == MK_SW11) {
            view_timer2++;
        } else if (view_timer2 > 0 && view_timer2 < 300) {
            view_timer2 = 0;
            if (view_ind_flag > 0) {
                view_ind_flag--;
                eeprom_address = (((view_start_flag + view_ind_flag) % 10)*10);
            }
        }
        view_display(eeprom_address, view_ind_flag);

    }
}

void view_display(unsigned char eeprom_address, unsigned int view_ind_flag) 
{
    clcd_putch(view_ind_flag + 48, LINE2(0));
    clcd_putch(' ', LINE2(1));
    data = read_extern_eeprom(eeprom_address);
    clcd_putch(data, LINE2(2));
    data = read_extern_eeprom(eeprom_address + 1);
    clcd_putch(data, LINE2(3));
    clcd_putch(':', LINE2(4));
    data = read_extern_eeprom(eeprom_address + 2);
    clcd_putch(data, LINE2(5));
    data = read_extern_eeprom(eeprom_address + 3);
    clcd_putch(data, LINE2(6));
    clcd_putch(':', LINE2(7));
    data = read_extern_eeprom(eeprom_address + 4);
    clcd_putch(data, LINE2(8));
    data = read_extern_eeprom(eeprom_address + 5);
    clcd_putch(data, LINE2(9));
    clcd_putch(' ', LINE2(10));
    data = read_extern_eeprom(eeprom_address + 6);
    clcd_putch(data, LINE2(11));
    data = read_extern_eeprom(eeprom_address + 7);
    clcd_putch(data, LINE2(12));
    data = read_extern_eeprom(eeprom_address + 8);
    clcd_putch(' ', LINE2(13));
    data = read_extern_eeprom(eeprom_address + 9);
    clcd_putch(data, LINE2(14));
    data = read_extern_eeprom(eeprom_address + 10);
    clcd_putch(data, LINE2(15));

}

