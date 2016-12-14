#include<iostream>
#include<stdlib.h>
#include <time.h>
#include <stdio.h>

using namespace std;

int main()
{
    cout<<"Program starting\n";
    int numberElements = 0;

    cout<<"Enter number of elements: ";
    cin>>numberElements;

    int testArray[numberElements];
    int sizeOfArray = sizeof(testArray)/sizeof(int);
    int sum;
    int maxSum = -1000000;
    int lowIndex = 0;
    int highIndex = sizeOfArray;
    for(int index = 0; index<sizeOfArray;index++)
    {
        testArray[index] = (rand() % 501) - 250;
    }

//    for(int index = 0; index<sizeOfArray; index++)
//   {
//       cout<<testArray[index]<<"\n";
//    }
    clock_t tStart = clock();
    for (int index = 0; index< sizeOfArray; index++)
    {
        sum = 0;
        for(int i = index; i < sizeOfArray; i++)
        {
            sum = sum+testArray[i];
            if (sum > maxSum)
            {
                maxSum = sum;
                lowIndex = index;
                highIndex = i;
            }
        }
    }
    printf("Time taken: %.10fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    cout<<"The sum is: "<<maxSum<<"\n";
/*
    cout<<"The sum is: "<<maxSum<<"\n";
    cout<<"The max sub array is: [ ";
    for(int indexPrint = lowIndex; indexPrint <= highIndex; indexPrint++)
    {
        cout<<testArray[indexPrint]<<" ";
    }
    cout<<"]\n";*/
    cout<<"Program ending\n";

    return 0;
}
