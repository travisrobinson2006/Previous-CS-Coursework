/* CS261- Assignment 1 - Q.1*/
/* Name: Travis Robinson
 * Date: 06/30/2015
 * Solution description: Create an array of struct students,
 * give them random ID's and scores, output the scores and delete the
 * students array
 */

#include <stdio.h>
#include<stdlib.h>
#include<math.h>

struct student{
	int id;
	int score;
};
/*********************************************************************
** Function: allocate
** Description: Allocate memory for an array of student structs
** Parameters: N/A
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/
struct student* allocate(){
     /*Allocate memory for ten students*/
     struct student* ptr = malloc(10*sizeof(struct student*));

     /*return the pointer*/
     return ptr;
}

/*********************************************************************
** Function: generate
** Description: Create random ID's and scores for 10 students
** Parameters: Pointer to the array of students
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/
void generate(struct student* students){
     /*Generate random ID and scores for ten students, ID being between 1 and 10, scores between 0 and 100*/
 //    time_t t;
 //    srand((unsigned) time(&t));
     int index = 0;
     while (index < 10)
     {
         int numberAvailable = 1;
         int newIndex = 0;
         int potentialID = rand() % 10 + 1;
      //   printf("%d \n", potentialID);

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
}
/*********************************************************************
** Function: output
** Description: Prints the ID's and Scores of the students
** Parameters: Pointer to the array of students
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/
void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
    int x = 0;
    while (x < 10)
    {
        printf("%d %d \n",students->id, students->score);
        students = students+sizeof(struct student*);
        x++;
    }
}

/*********************************************************************
** Function: summary
** Description: Print the minimum, maximum and average scores of the students
** Parameters: Pointer to the array of students
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/
void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the ten students*/
     int minimum = 100;
     int maximum = 0;
     int average = 0;
     struct student* firstStudent = students;

     int index = 0;
     while (index < 10)
     {
         if (students->score < minimum)
             {
                 minimum = students->score;

             }
         students = students+sizeof(struct student*);
         index++;
     }
     printf("Minimum: %d\n", minimum);

     students = firstStudent;
     index = 0;
     while (index < 10)
     {
         if (students->score > maximum)
             {
                 maximum = students->score;
             }
         students = students+sizeof(struct student*);
         index++;
     }
     printf("Maximum: %d \n", maximum);

     students = firstStudent;
     index = 0;
     while (index < 10)
     {
         average = average + students->score;
         students = students+sizeof(struct student*);
         index++;
     }
     average = average/10;

     printf("Average: %d \n", average);
}

/*********************************************************************
** Function: Deallocate
** Description: Release the memory allocated by the allocate function
** Parameters: Pointer to the array of students
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/
void deallocate(struct student* stud){
     /*Deallocate memory from stud*/

     if(stud != 0)
     {
              free(stud);
              stud = NULL;
     }
}

int main(){
    struct student* stud = NULL;

    /*call allocate*/
    stud = allocate();

    /*call generate*/
    generate(stud);

    /*call output*/
    output(stud);

    /*call summary*/
    summary(stud);

    /*call deallocate*/
    deallocate(stud);

    return 0;
}
