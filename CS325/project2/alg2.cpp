#include <iostream>

using namespace std;

int main()
{
    int inputArray[] = {1,3,7,12};
    int A = 31;

    int runningTotal = A;
    int length = (sizeof(inputArray)/sizeof(int));
    int denomination = length-1;
    int outPutArray[length];

    for (int index = 0; index < length; index++)
    {
        outPutArray[index] = 0;
    }

    cout<<"variables initialized"<<endl;

    while(denomination >= 0)
    {
        if (inputArray[denomination] <= runningTotal)
        {
            runningTotal = runningTotal-inputArray[denomination];
            outPutArray[denomination]++;
        }
        else
        {
            denomination--;
        }
    }

    for(int index = 0; index < length; index++)
    {
        cout<<outPutArray[index]<<" ";
    }
    return 0;
}
