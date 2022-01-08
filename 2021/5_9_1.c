#include "REG52.H"

void initial_myself();   
void initial_peripheral();

void delay_short(unsigned int uiDelayshort);
void delay_long(unsigned int uiDelaylong);
void led_flicker();

sbit led_dr=P3^5;  

void main()  
  {
   initial_myself();
   delay_long(100);
   initial_peripheral();
   while(1)
   {
      led_flicker();   
   }
}

void led_flicker() 
{
  led_dr=1;  
  delay_short(50000);  
  led_dr=0;  
  delay_long(100);    
}

void delay_short(unsigned int uiDelayShort)
{
   unsigned int i;  
   for(i=0;i<uiDelayShort;i++)
   {
     ;  
   }
}

void delay_long(unsigned int uiDelayLong)
{
   unsigned int i;
   unsigned int j;
   for(i=0;i<uiDelayLong;i++)
   {
      for(j=0;j<500;j++)  
          {
             ; 
          }
   }
}

void initial_myself()
{
  led_dr=0;  
}
void initial_peripheral() 
{
  ;   
}
