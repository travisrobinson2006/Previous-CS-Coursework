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

    int testArray[] = {1, 4, -9, 8, 1, 3, 3, 1, -1, -4, -6, 2, 8, 19, -10, -11};
    int sizeOfArray = sizeof(testArray)/sizeof(int);
    int sum;
    int maxSum = -1000000;
    int lowIndex = 0;
    int highIndex = sizeOfArray;
    //for(int index = 0; index<sizeOfArray;index++)
    //{
    //    testArray[index] = (rand() % 501) - 250;
    //}

//    for(int index = 0; index<sizeOfArray; index++)
//    {
//        cout<<testArray[index]<<"\n";
//    }

    clock_t tStart = clock();
    for (int index = 0; index < (sizeOfArray); index++)
    {
        for(int j= index; j <= sizeOfArray; j++)
        {
            sum = 0;
            for(int i = index; i < j; i++)
            {
                sum = sum+testArray[i];
            }
            if(sum > maxSum)
            {
                maxSum = sum;
                lowIndex = index;
                highIndex = j;
            }

        }
    }
    printf("Time taken: %.10fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    cout<<"The sum is: "<<maxSum<<"\n";
    cout<<"The max sub array is: [ ";
    for(int indexPrint = lowIndex; indexPrint < highIndex; indexPrint++)
    {
        cout<<testArray[indexPrint]<<" ";
    }
    cout<<"]\n";
    cout<<"Program ending\n";
    return 0;
}
