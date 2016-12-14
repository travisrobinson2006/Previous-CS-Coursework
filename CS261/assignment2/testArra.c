#include <stdio.h>
#include <stdlib.h>
#include "dynamicArray.h"



int main(int argc, char* argv[])
{
   	DynArr *dyn;
	dyn = createDynArr(2);

   	printf("\n\nTesting addDynArr...\n");
	addDynArr(dyn, 3);
	addDynArr(dyn, 4);
	addDynArr(dyn, 10);
	addDynArr(dyn, 5);
	addDynArr(dyn, 6);

   	removeAtDynArr(dyn, 1);
    printf("Position 0 is: %f \n",getDynArr(dyn, 0));
    printf("Position 1 is: %f \n",getDynArr(dyn, 1));
    printf("Position 2 is: %f \n",getDynArr(dyn, 2));
    printf("Position 3 is: %f \n",getDynArr(dyn, 3));

    printf("The top of the stack is %f \n",topDynArr(dyn));


}
