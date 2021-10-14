#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "string.h"
/*aiding constants*/
#define LCDPORT         GPIO_PORTB_BASE
#define LCDPORTENABLE   SYSCTL_PERIPH_GPIOB
#define RS              GPIO_PIN_0
#define E               GPIO_PIN_1
#define D4              GPIO_PIN_4
#define D5              GPIO_PIN_5
#define D6              GPIO_PIN_6
#define D7              GPIO_PIN_7
/*functions*/
void LCD_init(void);                                //LCD initialization
void LCD_Command(unsigned char c);                  //Send command
void LCD_Show(unsigned char d);                     //Show a char
void LCD_Print(char *s, char *d);                   //Print 2 lines
void LCD_PrintLn(char i, char *s);                  //Print specific line
void LCD_Cursor(char x, char y);                    //Set cursor
void LCD_Clear(void);
/* pins connection to lcd
B0->RS
B1->E
ground ->R/W
gound->K
gound->VDD
VBUS->VSS
VBUS->A
B4->D4
B5->D5
B6->D6
B7->D7
*/
/*
potentiometer connection
1->VBUS
2->V0
3->ground
*/
void LCD_init() 
{
  SysCtlPeripheralEnable(LCDPORTENABLE);
  GPIOPinTypeGPIOOutput(LCDPORT, 0xFF);//let the pins act as output
  SysCtlDelay(50000);
  GPIOPinWrite(LCDPORT, RS,  0x00 );//RS disanle
  
  GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7,  0x30 );//wake up
  GPIOPinWrite(LCDPORT, E, 0x02);//E enable
  SysCtlDelay(10);
  GPIOPinWrite(LCDPORT, E, 0x00);//E disbale
  SysCtlDelay(50000);
  
  GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7,  0x30 ); //wake up
  GPIOPinWrite(LCDPORT, E, 0x02);//E enable
  SysCtlDelay(10);
  GPIOPinWrite(LCDPORT, E, 0x00);//E disable
  SysCtlDelay(50000);
  
  GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7,  0x28 );//2 lines and 5x7 character (4-bit data, D4 to D7)
  GPIOPinWrite(LCDPORT, E, 0x02);//E enable
  SysCtlDelay(10);
  GPIOPinWrite(LCDPORT, E, 0x00);//E disable
  SysCtlDelay(50000);
  
  LCD_Command(0x0F); //Turn on Lcd
  LCD_Clear(); //Clear screen
}
/*LCD COMMAND  (4 BIT MODE)*/
/*since its a 4-bit mode then we will divide the 
data into two parts and send them to the same 4 pins
*/
void LCD_Command(unsigned char c)
{
  /*the second 4-bits which are (4,5,6,7) are send first to our pins*/
  GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (c & 0xf0) );
  GPIOPinWrite(LCDPORT, RS, 0x00);//RS disabled
  GPIOPinWrite(LCDPORT, E, 0x02);//E enabled
  SysCtlDelay(10);
  
  GPIOPinWrite(LCDPORT, E, 0x00);//E disabled
  SysCtlDelay(50000);
  /*the first 4 bits which are (4,5,6,7) are send first to our pins
    (c&0x0f) detects the first 4-bits which are (0,1,2,3)
    (<<4) the left shift operand shifted these bits to the (4,5,6,7) bits 
    to be able to send them to our pins
  */
  GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (c & 0x0f) << 4 );
  GPIOPinWrite(LCDPORT, RS, 0x00);//RS disabled
  GPIOPinWrite(LCDPORT, E, 0x02);//E enabled
  SysCtlDelay(10);
  
  GPIOPinWrite(LCDPORT, E, 0x00);//E disabled
  SysCtlDelay(50000);
}
/*SHOW CHAR */
/*since its a 4-bit mode then we will divide the 
data into two parts and send them to the same 4 pins
*/
void LCD_Show(unsigned char d)
{
  /*the second 4-bits which are (4,5,6,7) are send first to our pins*/
  GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (d & 0xf0) );
  GPIOPinWrite(LCDPORT, RS, 0x01);//RS enable
  GPIOPinWrite(LCDPORT, E, 0x02);//E enable
  SysCtlDelay(50000);
  
  GPIOPinWrite(LCDPORT, E, 0x00);//E disable
  SysCtlDelay(50000);
   /*the first 4 bits which are (4,5,6,7) are send first to our pins
    (c&0x0f) detects the first 4-bits which are (0,1,2,3)
    (<<4) the left shift operand shifted these bits to the (4,5,6,7) bits 
    to be able to send them to our pins
  */
  GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (d & 0x0f) << 4 );
  GPIOPinWrite(LCDPORT, RS, 0x01);//RS enable
  GPIOPinWrite(LCDPORT, E, 0x02);//E enable
  SysCtlDelay(50000);
  
  GPIOPinWrite(LCDPORT, E, 0x00);//E disable
  SysCtlDelay(50000);
}
/*LCD CURSOR */
void LCD_Cursor(char x, char y)
{
  if (x==0) {
    LCD_Command(0x80 + (y % 16));//(0x80) force cursor to the first line//(y%16) to detect which bit the cursor will be on
    return;
  }
  LCD_Command(0xC0 + (y % 16));//(0xC0) force cursor to the second line//(y%16) to detect which bit the cursor will be on
}
/*CLEAR DISPLAY */
void LCD_Clear(void)
{
  LCD_Command(0x01);//
  SysCtlDelay(10);
}
/*LCD PRINT TWO LINE*/
void LCD_Print(char *s, char *d)
{
    int j;
    for (j=0; j<16; j++) {
      if (j<strlen(s)) {
        LCD_Cursor(0,j);// 0-> first line
        LCD_Show(s[j]);
      }
      if (j<strlen(d)) {
        LCD_Cursor(1,j);// 1-> second line
        LCD_Show(d[j]);
      }
    }
    LCD_Command(0xC0 + 16); //Hide cursor
}