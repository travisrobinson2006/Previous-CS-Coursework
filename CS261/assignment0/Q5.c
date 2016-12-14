/* CS261- Assignment 1 - Q.5*/
/* Name:Travis Robinson
 * Date:07/03/2015
 * Solution description: Write a functin that accepts a user created word
 * and gives it sticky words (alternating caps an non-caps)
 */

#include <stdio.h>
#include <stdlib.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
     return ch-'a'+'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch){
     return ch-'A'+'a';
}
/*********************************************************************
** Function: sticky
** Description: Accepts a word and alters it into alternating capital and
** non-capital letters, with the first letter being capital
** Parameters: Pointer to an array of chars
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/
void sticky(char* word){
     /*Convert to sticky caps*/
     int index = 0;

     while (word[index] != '\0')
     {
         if(index%2 == 0)
         {
             if (!isupper(word[index]))
             {
                 word[index] = toUpperCase(word[index]);
             }
         }
         else if(index%2 == 1)
         {
             if (!islower(word[index]))
             {
                 word[index] = toLowerCase(word[index]);
             }
         }
         index++;
     }
}

int main(){
    /*Read word from the keyboard using scanf*/
    char str [81];
    printf("Enter a string: ");
    scanf("%80s", str);

    /*Call sticky*/
    sticky(str);

    /*Print the new word*/
    printf("%s \n", str);

    return 0;
}
