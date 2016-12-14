/* CS261- Assignment 1 - Q.4*/
/* Name:Travis Robinson
 * Date:07/03/2015
 * Solution description: Sort the student struct from Q0 in ascending order
 * (least to greatest) by score
 */

#include <stdio.h>
#include <stdlib.h>

struct student{
	int id;
	int score;
};
/*********************************************************************
** Function: sort
** Description: Sort students from least to greatest by score
** Parameters: Pointer to an array of students, and an integer of student size
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/
void sort(struct student* students, int n){
     /*Sort the n students based on their score*/
     printf("sorted here \n");
     int smallestScore;
     int locationSmallestScore;
     int count = 0;
     //int temp = (students+sizeof(struct students*))->score;
     //(students+sizeof(struct students*))->score = students->score;
     //students->score = temp;

     while (count < (n-1))
     {
         smallestScore = (students+count*sizeof(struct student*))->score;
         locationSmallestScore = count;
         int index = count+1;
         while(index < n)
         {
             if ((students+index*sizeof(struct student*))->score < smallestScore)
             {
                 smallestScore = (students+index*sizeof(struct student*))->score;
                 locationSmallestScore = index;
             }
             index++;
          //   printf("smallest score is %d and it is in position %d \n", smallestScore,locationSmallestScore);
         }
         int tempScore = (students+locationSmallestScore*sizeof(struct student*))->score;
         int tempID = (students+locationSmallestScore*sizeof(struct student*))->id;
         (students+locationSmallestScore*sizeof(struct student*))->score = (students+count*sizeof(struct student*))->score;
         (students+locationSmallestScore*sizeof(struct student*))->id = (students+count*sizeof(struct student*))->id;
         (students+count*sizeof(struct student*))->score = tempScore;
         (students+count*sizeof(struct student*))->id = tempID;

         /*
         int tempScore = (students+locationSmallestScore*sizeof(struct students*))->score;
         int tempID = (students+locationSmallestScore*sizeof(struct students*))->id;
         (students+sizeof(struct students*))->score = (students+count*sizeof(struct students*))->score;
         (students+sizeof(struct students*))->id = (students+count*sizeof(struct students*))->id;
         (students+count*sizeof(struct students*))->id = tempID;
         (students+count*sizeof(struct students*))->score = tempScore;*/
         count++;
     }
}

int main(){
    /*Declare an integer n and assign it a value.*/
    int n = 10;

    /*Allocate memory for n students using malloc.*/
    struct student* students = malloc(n*sizeof(struct student*));

    /*Generate random IDs and scores for the n students, using rand().*/
 //    time_t t;
 //    srand((unsigned) time(&t));
     int index = 0;
     while (index < n)
     {
         int numberAvailable = 1;
         int newIndex = 0;
         int potentialID = rand() % n + 1;

         while (newIndex < (index))
         {
             if (potentialID == (students+(newIndex*sizeof(struct student*)))->id)
             {
                 numberAvailable = 0;
                 break;
             }
             newIndex++;
         }
         if (numberAvailable == 1)
         {
             (students+index*sizeof(struct student*))->id = potentialID;
             (students+(index*sizeof(struct student*)))->score = rand() % 100;
             index++;
         }
     }

    /*Print the contents of the array of n students.*/
    int indexOutput = 0;
    struct student* studentsOutput = students;
    while (indexOutput < n)
    {
        printf("%d %d \n",studentsOutput->id, studentsOutput->score);
        studentsOutput = studentsOutput+sizeof(struct student*);
        indexOutput++;
    }

    /*Pass this array along with n to the sort() function*/
    sort(students,n);

    /*Print the contents of the array of n students.*/
    indexOutput = 0;
    studentsOutput = students;
    while (indexOutput < n)
    {
        printf("%d %d \n",studentsOutput->id, studentsOutput->score);
        studentsOutput = studentsOutput+sizeof(struct student*);
        indexOutput++;
    }

    return 0;
}
