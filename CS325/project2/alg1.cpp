#include <iostream>
#include <climits>
#include <vector>
using namespace std;

int* changeslow(int A,int inputArray[],int length);

int main()
{
    int testArray1[] = {1,3,7,12};
    int testA1 = 5;
    int testA2 = 29;
    int length = sizeof(testArray1)/sizeof(int);
    int output[length];

    for(int index = 0;index<length;index++)
    {
        output[index] = INT_MAX/length;
    }

    for(int index = 0;index<length;index++)
    {
        //cout<<output[index]<<" ";
    }

    int* testptr;
    testptr = output;
    //cout<<testptr<<endl;
    changeslow(testA1,testArray1,length);
    //cout<<testptr<<endl;

    for(int index = 0;index<length;index++)
    {
        //cout<<output[index]<<" ";
    }

}
int* changeslow(int A,int inputArray[],int length)
{

    int* curMin;
    curMin = new int[length];
    int* tempptr;
    int* garbage;
    tempptr = new int[length];
    for(int i = 0;i<length;i++)
    {
        tempptr[i]=0;
    }

    if (A == 0)
    {
        return tempptr;  // base case
    }
    //cout<<"deleting garbage"<<endl;
    //garbage = tempptr;
    //delete garbage;
    //cout<<"garbage deleted"<<endl;

    for (int j = 0;j<length;j++)
    {
        curMin[j] = INT_MAX/length;
    }

    for (int index = 0;index<length;index++)
    {
        if(inputArray[index]<=A)
        {
            int curMinCount = 0;
            int tempCount = 0;
      //      cout<<"making recursive call"<<endl;
            tempptr = changeslow(A-inputArray[index],inputArray,length);
            tempptr[index]=tempptr[index]+1;
            for (int compare = 0;compare<length;compare++)
            {
                curMinCount = curMinCount+curMin[index];
            }
            for (int compare = 0;compare<length;compare++)
            {
                tempCount = tempCount+tempptr[index];
            }
            if(tempCount<curMinCount)
            {
                for (int counter = 0;counter<length;counter++)
                {
                    curMin[counter] = tempptr[counter];
                }
                delete tempptr;
                for (int index = 0; index<length;index++)
                {
                    cout<<curMin[index]<<" ";
                }
                cout<<endl;
            }
        }
        return curMin;
    }

}
