#include <stdbool.h>
#include <stdint.h>
#include "keypad.c"
#include "lcd.c"
#include "driverlib/sysctl.h"
#include "calculation.c"
#include "math.h"
#include "string.h"

int main(void) 
{
  row_init();
  col_init();
  LCD_init();
  SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
  LCD_Print("calculator is on", " "); //Print 2 lines
  SysCtlDelay(10000000); //Delay
  LCD_Clear(); 
START: /* detecting the first character of the first number*/
  LCD_Clear();
  while(1){
    num1 = 0;
    num1_dec=0;
    num2 = 0;
    result = 0;
    res=' ';
    func = '+';
    sign1=1;
    sign2=1;
    decimal=0;
    rem=0;
    hit =key_pressed(); //save the character pressed to the hit variable
    SysCtlDelay(50000);
    switch(hit){
      case('0'):num1=hit-48;break; //(hit-48) to convert the ascii character into integer by 					
      case('1'):num1=hit-48;break;
      case('2'):num1=hit-48;break;						
      case('3'):num1=hit-48;break;
      case('4'):num1=hit-48;break;						
      case('5'):num1=hit-48;break;
      case('6'):num1=hit-48;break;						
      case('7'):num1=hit-48;break;
      case('8'):num1=hit-48;break;						
      case('9'):num1=hit-48;break;
      case('-'):sign1=-1;break;
      case('C'):goto START;
    default:goto START;}
    LCD_Show(hit); //display character
    SysCtlDelay(500000);
  op:/*detecting the characters after the first character until a function is pressed
       then we go the op2
    */
    hit =key_pressed();
    SysCtlDelay(5000);
    switch(hit){
      /*multiplying the num1 previous value by 10 and add the new number pressed to it 
       //if num1=2 and we pressed 1 then the result of num1 will be 
         num1=(2*10)+('1'-48)-->num1=20+1 -->num1=21 
      */
      case('0'):num1=(num1*10)+(hit-48);LCD_Show(hit);SysCtlDelay(500000); goto op; 						
      case('1'):num1=(num1*10)+(hit-48);LCD_Show(hit);SysCtlDelay(500000); goto op;
      case('2'):num1=(num1*10)+(hit-48);LCD_Show(hit);SysCtlDelay(500000); goto op;						
      case('3'):num1=(num1*10)+(hit-48);LCD_Show(hit);SysCtlDelay(500000); goto op;
      case('4'):num1=(num1*10)+(hit-48);LCD_Show(hit);SysCtlDelay(500000); goto op;						
      case('5'):num1=(num1*10)+(hit-48);LCD_Show(hit);SysCtlDelay(500000); goto op;
      case('6'):num1=(num1*10)+(hit-48);LCD_Show(hit);SysCtlDelay(500000); goto op;						
      case('7'):num1=(num1*10)+(hit-48);LCD_Show(hit);SysCtlDelay(500000); goto op;
      case('8'):num1=(num1*10)+(hit-48);LCD_Show(hit);SysCtlDelay(500000); goto op;						
      case('9'):num1=(num1*10)+(hit-48);LCD_Show(hit);SysCtlDelay(500000); goto op;
      case('+'):LCD_Show(hit);func=hit;break;						
      case('-'):LCD_Show(hit);func=hit;break;
      case('/'):LCD_Show(hit);func=hit;break;
      case('*'):LCD_Show(hit);func=hit;break;
      case('c'):goto START;
    default:goto op;}
    num1=num1*sign1; //change the sign of the first number as there will be no other modification to it
  op2:/*detecting the first character of the second number*/
    hit = key_pressed();
    SysCtlDelay(5000);
    switch(hit){
      case('0'):num2=hit-48;break;						
      case('1'):num2=hit-48;break;
      case('2'):num2=hit-48;break;						
      case('3'):num2=hit-48;break;
      case('4'):num2=hit-48;break;						
      case('5'):num2=hit-48;break;
      case('6'):num2=hit-48;break;						
      case('7'):num2=hit-48;break;
      case('8'):num2=hit-48;break;						
      case('9'):num2=hit-48;break;
      case('-'):sign2=-1;break;
      case('C'):goto START;
    default:goto op2;}
    LCD_Show(hit); 
    SysCtlDelay(500000); 
  calc:/*detecting the characters after the first character until a function is pressed
       then we calculate the result
    */
    hit =key_pressed();
    SysCtlDelay(500000);
    switch(hit){ 
      /*multiplying the num1 previous value by 10 and add the new number pressed to it 
       //if num1=2 and we pressed 1 then the result of num1 will be 
         num1=(2*10)+('1'-48)-->num1=20+1 -->num1=21 
      */
      case('0'):num2=(num2*10)+(hit-48);LCD_Show(hit);SysCtlDelay(500000);goto calc;						
      case('1'):num2=(num2*10)+(hit-48);LCD_Show(hit);SysCtlDelay(500000);goto calc;
      case('2'):num2=(num2*10)+(hit-48);LCD_Show(hit);SysCtlDelay(500000);goto calc;						
      case('3'):num2=(num2*10)+(hit-48);LCD_Show(hit);SysCtlDelay(500000);goto calc;
      case('4'):num2=(num2*10)+(hit-48);LCD_Show(hit);SysCtlDelay(500000);goto calc;						
      case('5'):num2=(num2*10)+(hit-48);LCD_Show(hit);SysCtlDelay(500000);goto calc;
      case('6'):num2=(num2*10)+(hit-48);LCD_Show(hit);SysCtlDelay(500000);goto calc;						
      case('7'):num2=(num2*10)+(hit-48);LCD_Show(hit);SysCtlDelay(500000);goto calc;
      case('8'):num2=(num2*10)+(hit-48);LCD_Show(hit);SysCtlDelay(500000);goto calc;						
      case('9'):num2=(num2*10)+(hit-48);LCD_Show(hit);SysCtlDelay(500000);goto calc;
      /*if '=' character is pressed then we calculate the result*/
      /*num2=num2*sign2; --> change the sign of the second number before calculation*/
      case('='):LCD_Show(hit);SysCtlDelay(500000);num2=num2*sign2;result=calc (num1, num2,func);break;
      case('C'):goto START;
    default:goto calc;}
    
    /*remove the -ve sign from the result if it is negative
      to be able to print it and adding the -ve manually
    */
    if(result<0){
      LCD_Show('-');
      result*=-1;}
    
    /*printing '0' manulally if the result is zero*/
    else if(result==0)
    {LCD_Show('0');}
    
    /*Detecting the mathematical error of dividing a number by 0
      and printing an error message
    */
    if((num1 !=0)&&(func=='/')&&(num2==0))
    {LCD_Print("Math Error          ","Press C           ");}
    
    
    num1_dec=num1;  //num_dec used in the decimal detection
    num1=result;   //this line is an addtional feature used to make another operation on the result
    
    /*print result without decimals*/
    count=-1;
    /*
      the first while loop converts the integer number into
      an array of integers
    */
    while(result !=0)
    {
      count++;
      ans[count]=(result%10);
      result/=10;
    }
    /*
    
    */
    while(count!=-1){
      res=(ans[count])+48;
      LCD_Show(res);
      SysCtlDelay(500000);
      count--;}
    /*       decimal     */
    rem=num1_dec % num2;                   //check if the result have a decimal 
    decimal=(int)((rem/num2)*1000000000);  //converting the decimal into integer 
    if((func=='/')&&(rem !=0))             //check there is a remainder and the function is '/' divison
    {
      LCD_Show('.');                       //show the '.' and then print the decimal number after it 
      while(decimal !=0){
        count++;
        ans_dec[count]=(decimal%10);
        decimal/=10;}
      while(count!=-1){
        res_dec=(ans_dec[count])+48;
        LCD_Show(res_dec);
        SysCtlDelay(500000);
        count--;}
    }
    goto op;
  }
}