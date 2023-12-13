#include <xc.h>
#include "main.h"
void dash_board_display(char *Fgear, char *time, int speed) 
{
 //   CLEAR_DISP_SCREEN;
   clcd_print("  TIME   EVN SP ", LINE1(0));
    clcd_print(time, LINE2(0));
    clcd_print(Fgear, LINE2(10));
    clcd_putch(((speed / 10) + '0'), LINE2(14));
    clcd_putch(((speed % 10) + '0'), LINE2(15));

}

