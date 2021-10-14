#include "tm4c123gh6pm.h"
#include <stdint.h>
void row_init(void);      //initialize portE as the rows
void col_init(void);      //initialize portC as the columns
char key_pressed(void);   //detect the key which is pressed
void delayMs(int n);
//array of buttons
unsigned char keys[4][4]={{'1','2','3','+'},
                       {'4','5','6','-'},
                       {'7','8','9','c'},
                       {'*','0','=','/'}};
unsigned long r[4]={0x0E,0x0D,0x0B,0x07};//use this array to detect the rows respectively
unsigned long c[4]={0xE0,0xD0,0xB0,0x70};//use this array to detect the coloumns respectively

void row_init(void)
{
    //using the following pins (E0,E1,E2,E3)
    SYSCTL_RCGCGPIO_R |= 0x10;      //enable clock  
    GPIO_PORTE_DIR_R |= 0x0F;      //output
    GPIO_PORTE_DEN_R |= 0x0F;      //digital enable
    GPIO_PORTE_ODR_R |= 0x0F;     //pull down resistors 
}
void col_init(void)
{
    //using the following pins(C4,C5,C6,C7)
    SYSCTL_RCGCGPIO_R |= 0x04;      //enable clock 
    GPIO_PORTC_DIR_R &= ~0xF0;     //input
    GPIO_PORTC_DEN_R |= 0xF0;      //digital enable
    GPIO_PORTC_PUR_R |= 0xF0;     //pull up resistors       
}


char key_pressed(void)
{
  int col;
  while(1){
    for(int i=0;i<4;i++){
      for(int j=0;j<4;j++){
        GPIO_PORTE_DATA_R = r[j];   //enable row
        delayMs(20);
        col = GPIO_PORTC_DATA_R & 0xF0;   //detect which coloumn is pressed
        if(col == c[i]) {return keys[j][i];}  //return the char of the key pressed
      }
    } 
  }
}

void delayMs(int n)
{
  int i, j;
    for(i = 0 ; i < n; i++)
      for(j = 0; j < 3180; j++) {}   
}
