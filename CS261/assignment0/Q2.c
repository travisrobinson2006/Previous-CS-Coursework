/* CS261- Assignment 1 - Q.2*/
/* Name: Travis Robinson
 * Date: 06/30/2015
 * Solution description:Write a function that manipulates integers that
 * are passed to it. Print out the integers before and after manipulation.
 */

#include <stdio.h>
#include <stdlib.h>

/*********************************************************************
** Function: foo
** Description: Manipulate integers that are passed to it as values and as
** pointers
** Parameters: Pointer to two integers and an integer value
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/
int foo(int* a, int* b, int c){
    /*Set a to double its original value*/
    *a= *a *2;

    /*Set b to half its original value*/
    *b= *b /2;

    /*Assign a+b to c*/
    c = *a + *b;

    /*Return c*/
    return c;
}

int main(){
    /*Declare three integers x,y and z and initialize them to 5, 6, 7 respectively*/
    int x = 5;
    int y = 6;
    int z = 7;
    int fooReturn;

    /*Print the values of x, y and z*/
    printf("x: %d \n",x);
    printf("y: %d \n",y);
    printf("z: %d \n",z);

    /*Call foo() appropriately, passing x,y,z as parameters*/
    fooReturn = foo(&x,&y,z);

    /*Print the value returned by foo*/
    printf("Returned by foo: %d \n",fooReturn);

    /*Print the values of x, y and z again*/
    printf("x: %d \n",x);
    printf("y: %d \n",y);
    printf("z: %d \n",z);

    /*Is the return value different than the value of z?  Why?*/
    /*
    The return value is not the same as z. The reason is that when variables are passed
    to a function, it's a copy of those variables that are then operated on in those
    functions. x and y were altered though because the function used pointers to those
    values to alter the values themselves. z was not altered because it was a copy of z
    in the function foo, which existed only for the scope of the function.
    */
    return 0;
}


