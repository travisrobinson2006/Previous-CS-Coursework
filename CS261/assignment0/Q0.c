/* CS261- Assignment 1 - Q. 0*/
/* Name: Travis Robinson
 * Date: 06/30/2015
 * Solution description: Create an integer x, print the address and values of x, and pass to a function which also prints the address and value of x,
 as well as the address of the pointer to x
 */

#include <stdio.h>
#include <stdlib.h>

/*********************************************************************
** Function: fooA
** Description: Print the address and value of an integer, and print the address
** of the pointer
** Parameters: Pointer to an integer
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/
void fooA(int* iptr){
     /*Print the value pointed to by iptr*/
     printf("The value pointed to by iptr is: %d \n",*iptr);

     /*Print the address pointed to by iptr*/
     printf("The address pointed to by iptr is: %d \n",iptr);

     /*Print the address of iptr itself*/
     printf("The address of iptr is: %d \n", &iptr);
}

int main(){

    /*declare an integer x*/
    int x = 8;

    /*print the address of x*/
    printf("The address for x is: %d \n",&x);

    /*Call fooA() with the address of x*/
    fooA(&x);

    /*print the value of x*/
    printf("The value for x is: %d \n", x);

    return 0;
}
