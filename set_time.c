/*
 * File:   set_time.c
 * Author: Admin
 *
 * Created on December 10, 2023, 8:24 PM
 */


#include <xc.h>
#include "main.h"
unsigned char hour=0,min=0,sec=0;
extern unsigned int menu_flag,set_time_flag;
void set_time_log()
{
    static char flagt=HOUR;
    unsigned char keytime;
    static int timet1=0,timet2=0;
    static unsigned long int count_flag=0;
    keytime = read_switches(LEVEL_CHANGE);
    
    
    clcd_print("HH:MM:SS",LINE1(0));
    if(flagt==HOUR)
    {
             
        if((count_flag++<300))
        {
            clcd_putch((hour/10)+'0',LINE2(0));
            clcd_putch((hour%10)+'0',LINE2(1));
        }
        else if( count_flag<700 )
        {
            clcd_putch(' ', LINE2(0));
            clcd_putch(' ', LINE2(1));
        }
        else
        {
            count_flag=0;
        }
    }
    else
    {
        clcd_putch((hour/10)+'0',LINE2(0));
        clcd_putch((hour%10)+'0',LINE2(1));
    }
    if(flagt==MINUTE)
    {
        if((count_flag++<300))
        {
            clcd_putch((min/10)+'0',LINE2(3));
            clcd_putch((min%10)+'0',LINE2(4));
        }
        else if(count_flag<700 )
        {
            clcd_putch(' ', LINE2(3));
            clcd_putch(' ', LINE2(4));
        }
        else
        {
            count_flag=0;
        }
    }
    else
    {
        clcd_putch((min/10)+'0',LINE2(3));
        clcd_putch((min%10)+'0',LINE2(4));
    }

    clcd_putch(':',LINE2(2));

    clcd_putch(':',LINE2(5));
    if(flagt==SECOND)
    {
        if((count_flag++<300))
        {
            clcd_putch((sec/10)+'0',LINE2(6));
            clcd_putch((sec%10)+'0',LINE2(7));
        }
        else if(count_flag<700 )
        {
            clcd_putch(' ', LINE2(6));
            clcd_putch(' ', LINE2(7));
        }
        else
        {
            count_flag=0;
        }
    }
    else
    {
        clcd_putch((sec/10)+'0',LINE2(6));
        clcd_putch((sec%10)+'0',LINE2(7));
    }
    

    
    if(keytime != ALL_RELEASED  && keytime == 11 )
    {
        timet1++;
    }
    
    else if((timet1) > 1 && (timet1 < 30))
    {
        timet1=0;
          if(flagt > SECOND)
          {
              flagt--;
              CLEAR_DISP_SCREEN;
          }
          else
          {
              flagt = HOUR;
          }
           
           
    }
    else if(timet1 >30)
      {
        timet1 = 0;
        write_ds1307(HOUR,(hour/10<<4) | (hour%10));
        write_ds1307(MINUTE,(min/10<<4) | (min%10));
        write_ds1307(SECOND,(sec/10<<4) | (sec%10));
          clcd_print("TIME SET",LINE1(0));
          clcd_print("SUCCESSFULLY",LINE2(0));
          for(unsigned int i=50000;i--;)
              for(unsigned int i=50;i--;);
          flagt=HOUR;
          menu_flag=1;
          CLEAR_DISP_SCREEN;
          
      }
      
      else
      {
          timet1 = 0;
      }
       
      if(keytime != ALL_RELEASED  && keytime==12)
      {
           timet2++;
      }
      else if(( timet2 > 1) && ( timet2 < 300))
      {
        
        if(flagt==HOUR)
        {
            if(hour<23)
            {
               hour++;
            }
            else
            {
                hour=0;
            }
        }
        if(flagt==MINUTE)
        {
            if(min<59)
            {
               min++;
            }
            else
            {
                min=0;
            }
        }
        if(flagt==SECOND)
        {
            if(sec<59)
            {
               sec++;
            }
            else
            {
                sec=0;
            }
        }
        timet2=0;
        CLEAR_DISP_SCREEN;
        
       }
      else if(timet2>30)
        {
          menu_flag=1;
          set_time_flag=0;
            CLEAR_DISP_SCREEN;
            timet2=0;
            
        }
        else
        {
           timet2 = 0;
        }
}