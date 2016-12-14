#include<climits>
#include<iostream>
#include<stdlib.h>
#include <time.h>
#include <stdio.h>
using std::cin;
using std::cout;
using std::endl;
using std::max;



// Returns value of maximum subarray sum arr[l..h]
int maxSubArraySum3(int arr[], int l, int h);


int main()
{
    //For testing
   //int arr[] = {-1,-2,-8,1,2,3,-7,-15};

    int numberElements = 0;

    cout<<"Enter number of elements: ";
    cin>>numberElements;

    int arr[numberElements];

   int n = sizeof(arr)/sizeof(arr[0]);

    for(int index = 0; index<n;index++)
    {
        arr[index] = (rand() % 501) - 250;
    }

    //for(int index = 0; index<n; index++)
    //{
    //    cout<<arr[index]<<"\n";
    //}
        clock_t tStart = clock();
   int max_sum = maxSubArraySum3(arr, 0, n-1);
    printf("Time taken: %.10fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
   cout << "Max sum is " << max_sum << endl;
   return 0;
}


int maxSubArraySum3(int arr[], int l, int h)
{
   // Base Case: single element
   if (l == h){
     return arr[l];
   }

   // Find middle point
   int m = (l + h)/2;

    //Find the maximum sub arrays in the left and right halves
    int leftMaxSubArraySum = maxSubArraySum3(arr, l, m);
    int rightMaxSubArraySum = maxSubArraySum3(arr, m+1, h);

    //Get the max sub array which crosses the midpoint

    //Left side of midpoint
    int sum = 0;
    int leftSum = INT_MIN;
    for (int i = m; i >= l; i--)
    {
        sum = sum + arr[i];
        if (sum > leftSum){
            leftSum = sum;
        }
    }

    // Right side of midpoint
    sum = 0;
    int rightSum = INT_MIN;
    for (int i = m+1; i <= h; i++)
    {
        sum = sum + arr[i];
        if (sum > rightSum){
            rightSum = sum;
        }
    }
    int crossingSum = leftSum + rightSum;

    //Find and return the maximum
    int maxSubArrayValue = max(leftMaxSubArraySum, rightMaxSubArraySum);
    maxSubArrayValue = max(maxSubArrayValue, crossingSum);
    return maxSubArrayValue;
}
