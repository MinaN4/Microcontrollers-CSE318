#include "tm4c123gh6pm.h"
#include "math.h"
#include "string.h"
/*main three operands*/
int num1;      // First number
int num2;     // Second number
char func;    // Function to be performed among two numbers
/*aiding variables*/
int result ;  
char res;
char hit;
int ans[16];
int count;
/*negative numbers aiding variables*/
int sign1;
int sign2;
/*decimals aiding variables*/
int decimal;
double rem;
char res_dec;
int ans_dec[16];
int num1_dec;

/*this function is used to calculate the result usign the 3 parameters
n1->first number
n2->second number
func->function
and return the result
*/
int calc (int n1, int n2,char func)
{
  switch(func){ 
    case('+'):result =(n1+n2);break;
    case('-'):result =(n1-n2);break;
    case('*'):result =(n1*n2);break;
    case('/'):result =(n1/n2);break;}
  return result;
}

