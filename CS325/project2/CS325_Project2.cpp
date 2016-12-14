#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <climits>
#include <time.h>
#include <numeric>

using namespace std;

vector<int*> getValues(string fileName);
vector<int> changeslow(int A,int inputArray[],int length);
int* changegreedy(int A, int inputArray[], int length,int outPutArray[]);
int* changedp(int A, int inputArray[],int length,int outputArray[]);
void fileWriter(int arrayResults[], int length, string file,string functionName);

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        cout<<"Parameters need to be program name and name of file"<<endl;
    }
    else{
        string file = argv[1];
        string filename = file;
        filename = filename+".txt";

        //retrieve values from text file
        vector<int*> values;
        values = getValues(filename);
        int* coinArray;
        int coinA;

        //retrieve arrays and values of A from vector
        for (int index = 0; index < values.size();index++)
        {
            if (index % 2 == 1)
            {
                coinA = *(values[index]+1);
                coinArray = values[index-1];
                int length = *values[index-1];
                int arrayV[length];
                for (int i = 1; i<=length;i++)
                {
                    arrayV[i-1] = *(coinArray+i);
                }
                //print statemants used to test and ensure arrays correctly made
                /*int sizeOfArray = sizeof(arrayV)/sizeof(int);
                cout<<"[";
                for (int print = 0; print<sizeOfArray;print++)
                {
                    cout<<arrayV[print]<<" ";
                }
                cout<<"]"<<endl;
                cout<<coinA<<endl<<endl;;*/
//***********************Send Array to algorithms here***************************
                //int changeGreedyArray;
                string outputFilename = file+"change"+".txt";
                ofstream outputFile;
                outputFile.open(outputFilename.c_str(),ofstream::out|ofstream::app);
                //print to file the array being examined
                outputFile << "For the input array [";
                for (int print = 0; print<length-1;print++)
                {
                    outputFile<<arrayV[print]<<",";
                }
                outputFile<<arrayV[length-1]<<"] with value A of "<<coinA<<"\n";
                outputFile.close();
            //create array for functions to alter
                int outputArray[length];
                int* outputArrayPointer=outputArray;
            //begin outputting
 //********************************************uncomment these lines for changeslow algorithm****************************************
                vector<int>vectorReturned(length);
                clock_t tStart = clock();
                vectorReturned=changeslow(coinA,arrayV,length);
                printf("Time taken for changeslow: %.10fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
                for (int counter = 0;counter<length;counter++)
                {
                    outputArray[counter]=vectorReturned[counter];
                }
                fileWriter(outputArray,length,file,"changeslow");
                tStart = clock();
                outputArrayPointer=changegreedy(coinA,arrayV,length,outputArray);
                printf("Time taken for changegreedy: %.10fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
                fileWriter(outputArray,length,file,"changegreedy");
                tStart = clock();
                outputArrayPointer=changedp(coinA,arrayV,length,outputArray);
                printf("Time taken for changedp: %.10fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
                fileWriter(outputArray,length,file,"changedp");

            }
        }
    }
    return 0;
}
/*
*This function accepts a file name and returns a vector of pointers to ints that contain the arrays read from fileName
*/
vector<int*> getValues(string fileName)
{
    //string fileName = "Coin1.txt";
    vector<int> denominationsV;
    vector<int*> toReturn;
    int counter = 0;
    string line;
    ifstream myfile (fileName.c_str());
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            char* pch;
            char* temp = (char *)malloc(500);
            strcpy(temp,line.c_str());
            pch = strtok(temp," ,[]");
            while(pch != NULL)
            {
                if(isdigit(*pch)==true)
                {
                    denominationsV.push_back(atoi(pch));
                    counter++;
                }
                pch = strtok (NULL, " ,[]");
            }
                int length = denominationsV.size();
                int* output;
                output = new int[length];

                //int output[denominationsV.size()-1];
                //int length = sizeof(output)/sizeof(int);
                //int A = denominationsV[denominationsV.size()-1];

                output[0] = length;
                for(int index = 1; index <= length; index++)
                {
                    output[index] = denominationsV[index-1];
                }
                /*for (int index = 0; index < length; index++)
                {
                    cout<< output[index]<<" ";
                }
                cout<<endl<<endl;*/

                toReturn.push_back(output);


                //cout<<"Array: ";
                //for(int index = 0; index<length;index++)
                //{
                //    cout<<output[index]<<" ";
                //}
                //cout<<endl<<"A: "<<A<<endl;

                denominationsV.clear();
        }
        myfile.close();
    }

    else cout << "Unable to open file";

    return toReturn;
}
//****************************************************************************************************************************************
//*****************************************************insert changeslow here*************************************************************
//****************************************************************************************************************************************
/*
*changeslow aka alg1
*/

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

/*
change greedy algorithm aka alg2;
*/
int* changegreedy(int A, int inputArray[], int length,int outPutArray[])
{
    int runningTotal = A;
    int denomination = length-1;
    //int outPutArray[length];

    for (int index = 0; index < length; index++)
    {
        outPutArray[index] = 0;
    }

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
//print statements used for testing
    /*cout<<"[";
    for(int index = 0; index < length; index++)
    {
        cout<<outPutArray[index]<<" ";
    }
    cout<<"]"<<endl<<endl;*/
    return 0;
}
/*
*changedp aka algorithm 3
*/
int* changedp(int A, int inputArray[],int length, int outputArray[])
{
        int arrayC[(A+1)][length];

    for(int index = 0;index<length; index++)
    {
        arrayC[0][index] = 0;
    }

    for(int rows = 1; rows<=A;rows++)
    {
        for (int columns = 0; columns<length;columns++)
        {
            int denomination;
            int m=INT_MAX;
            for(int i = length-1;i>=0;i--)
            {
                if(inputArray[i]<=rows)
                {
                    int offset = rows-inputArray[i];
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
                int offset = rows-inputArray[denomination];
                arrayC[rows][j]=arrayC[offset][j];
            }
            arrayC[rows][denomination]++;
        }
    }
//print statements used for testing
    /*    for(int rows = 0; rows<=A;rows++)
    {
        for(int columns = 0; columns<length;columns++)
        {
            cout<<arrayC[rows][columns]<<" ";
        }
        cout<<endl;
    }*/
    /*cout<<endl<<"[";
    for(int print = 0;print<length;print++)
    {
        cout<<arrayC[A][print]<<" ";
    }
    cout<<"]"<<endl<<endl;*/
    for (int index = 0;index<length;index++)
    {
        outputArray[index] = arrayC[A][index];
    }
}
/*
*fileWriter accepts the arrays we want to to print, and prints them.
*/
void fileWriter(int arrayResults[], int length, string file, string functionName)
{
    string filename = file+"change"+".txt";
    ofstream outputFile;
    outputFile.open(filename.c_str(),ofstream::out|ofstream::app);
    int numberCoins = 0;

    /*outputFile << "For the input array [";
    for (int print = 0; print<length-1;print++)
    {
        outputFile<<arrayInput[print]<<",";
    }
    outputFile<<arrayInput[length-1]<<"]"<<"\n";*/

    outputFile<<functionName<<":\n";

    outputFile << "[";
    for (int print = 0; print<length-1;print++)
    {
        outputFile<<arrayResults[print]<<",";
        numberCoins = numberCoins+arrayResults[print];
    }
    outputFile<<arrayResults[length-1]<<"]"<<"\n";
    numberCoins = numberCoins+arrayResults[length-1];
    outputFile<<numberCoins<<"\n";

    outputFile.close();
}
