#include<iostream>
#include<stdlib.h>
#include <time.h>
#include <stdio.h>

using namespace std;
int maxSubArraySum(int a[], int length)
{
    int low;
    int high;
    int highIndex = length;
    int lowIndex = 0;
    int max_sum = a[0];
    int ending_here_sum = a[0];

    for(int j = 1; j<length;j++)
    {
        highIndex = j;
        if (ending_here_sum>0)
        {
            ending_here_sum = ending_here_sum+a[j];
        }
        else
        {
            lowIndex = j;
            ending_here_sum = a[j];
        }
        if (ending_here_sum > max_sum)
        {
            max_sum = ending_here_sum;
            low = lowIndex;
            high = highIndex;
        }
    }

    for(int i = low;i<=high;i++)
    {
        cout<<a[i]<<" ";
    }
    cout<<"\n"<<"Sum is: "<<max_sum<<"\n";
  /* for (int i = 1; i < size; i++)
   {
        curr_max = max(a[i], curr_max+a[i]);
        max_so_far = max(max_so_far, curr_max);
   }
   return max_so_far;*/
}
int main()
{
    cout<<"Program starting\n";
    /*int numberElements = 0;

    cout<<"Enter number of elements: ";
    cin>>numberElements;
*/
    int testArray[] = {2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
    int sizeOfArray = sizeof(testArray)/sizeof(int);
    int sum;
    int maxSum = -1000000;
    int lowIndex = 0;
    int highIndex = sizeOfArray;
    /*for(int index = 0; index<sizeOfArray;index++)
    {
        testArray[index] = (rand() % 501) - 250;
    }*/

//    for(int index = 0; index<sizeOfArray; index++)
//    {
//        cout<<testArray[index]<<"\n";
//    }
    //clock_t tStart = clock();
    int summer = maxSubArraySum(testArray,sizeOfArray);
    //printf("Time taken: %.10fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    //cout<<"The sum is: "<<sum<<"\n";
    cout<<summer<<"\n";
    return 0;
}



