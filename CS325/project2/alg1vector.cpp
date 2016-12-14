#include <numeric>
#include <iostream>
#include <climits>
#include <vector>
using namespace std;

vector<int> changeslow(int A,int inputArray[],int length);

int main()
{
    int testArray1[] = {1,2,4,8};
    int testA1 = 15;
    int testA2 = 29;
    int length = sizeof(testArray1)/sizeof(int);
    int output[length];

    vector<int> returned(length);
    returned = changeslow(testA1,testArray1,length);
    for(int index = 0;index<length;index++)
    {
        cout<<returned[index]<<" ";
    }

}

vector<int> changeslow(int A,int inputArray[],int length)
{
    vector<int> vectorToReturn;
    for(int index = 0;index<length;index++)
    {
        vectorToReturn.push_back(INT_MAX/length);
    }
    //base case
    if (A == 0)
    {
          for (int index = 0;index<length;index++)
          {
              vectorToReturn[index]=0;
          }
          return vectorToReturn;
    }
    for(int index = 0;index<length;index++)
    {
        if(inputArray[index]<=A)
        {
            vector<int> vectorReturned(length);
            vectorReturned = changeslow(A-inputArray[index],inputArray,length);
            vectorReturned[index]=vectorReturned[index]+1;
            int returnedSum=0;
            int currentSum=0;
            returnedSum = accumulate(vectorReturned.begin(),vectorReturned.end(),0);
            currentSum = accumulate(vectorToReturn.begin(),vectorToReturn.end(),0);
            if(returnedSum<currentSum)
            {
                vectorToReturn=vectorReturned;
            }
        }
    }
    return vectorToReturn;
}
