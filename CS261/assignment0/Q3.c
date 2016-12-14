/* CS261- Assignment 1 - Q.3*/
/* Name:Travis Robinson
 * Date:07/01/2015
 * Solution description: Create an array of random integers and sort
 * and them in ascending order (least to greatest)
 */

#include <stdio.h>
/*********************************************************************
** Function: sort
** Description: Sort numbers from least to greatest
** Parameters: Pointer to an array of numbers
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/
void sort(int* number, int n){
     /*Sort the given array number , of length n*/
     int smallestNumber;
     int locationSmallestNumber;
     int count = 0;
     while (count < (n-1))
     {
         smallestNumber = *(number+(count*sizeof(int*)));
         locationSmallestNumber = count;
         int index = count+1;
         while(index < n)
         {
             if (*(number+(index*sizeof(int*))) < smallestNumber)
             {
                 smallestNumber = *(number+(index*sizeof(int*)));
                 locationSmallestNumber = index;
             }
             index++;
         }
         int temp = *(number+locationSmallestNumber*sizeof(int*));
         *(number+(locationSmallestNumber*sizeof(int*))) = *(number+(count*sizeof(int*)));
         *(number+(count*sizeof(int*))) = temp;
         count++;
     }
}

int main(){
    /*Declare an integer n and assign it a value of 20.*/
    int n =20;

    /*Allocate memory for an array of n integers using malloc.*/
    int* numberArray = malloc(n*sizeof(int*));

    /*Fill this array with random numbers, using rand().*/
    int index = 0;
    int* number = numberArray;
//    time_t t;
 //   srand((unsigned) time(&t));
    while(index<n)
    {
        *number = rand()%20;
        number = number+sizeof(int*);
        index++;
    }
    index = 0;
    number = numberArray;

    /*Print the contents of the array.*/
    while(index<n)
    {
        printf("Number %d is %d \n",index,*number);
        number = number+sizeof(int*);
        index++;
    }
    index = 0;
    number = numberArray;

    /*Pass this array along with n to the sort() function of part a.*/
    sort(numberArray, n);

    /*Print the contents of the array.*/
    while(index<n)
    {
        printf("Number %d is %d \n",index,*number);
        number = number+sizeof(int*);
        index++;
    }
    index = 0;
    number = numberArray;
    return 0;
}
