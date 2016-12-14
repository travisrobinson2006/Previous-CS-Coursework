#include <iostream>
#include <climits>

using namespace std;

int main()
{
    int testArray1[] = {1,2,4,8};
    int testArray2[] = {1,10,21,50};
    int testArray3[] = {1,2,4,8,16};
    int testA1 = 15;
    int testA2 = 63;
    int testA3 = 120;

    int length = (sizeof(testArray1)/sizeof(int));

    int arrayC[(testA1+1)][length];

    for(int index = 0;index<length; index++)
    {
        arrayC[0][index] = 0;
    }

    for(int rows = 1; rows<=testA1;rows++)
    {
        for (int columns = 0; columns<length;columns++)
        {
            int denomination;
            int m=INT_MAX;
            for(int i = length-1;i>=0;i--)
            {
                if(testArray1[i]<=rows)
                {
                    int offset = rows-testArray1[i];
                    //denomination = i;
                    //int offset = rows-testArray1[denomination];
                    int subM = 0;
                    for (int h = 0; h<length;h++)
                    {
                        subM = subM+arrayC[offset][h];
                    }
                    if(subM<m)
                    {
                        m = subM;
                        denomination = i;
                    }
                }
            }
            for(int j = 0;j<length;j++)
            {
                int offset = rows-testArray1[denomination];
                arrayC[rows][j]=arrayC[offset][j];
            }
            arrayC[rows][denomination]++;
        }
    }
    for(int rows = 0; rows<=testA1;rows++)
    {
        for(int columns = 0; columns<length;columns++)
        {
            cout<<arrayC[rows][columns]<<" ";
        }
        cout<<endl;
    }
}
