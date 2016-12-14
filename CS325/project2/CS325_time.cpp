#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <climits>
#include <time.h>
#include <ctime>
#include <chrono>
#include <numeric>

using namespace std;
using namespace std::chrono;


vector<int> changeslow(int A,int inputArray[],int length);
int* changegreedy(int A, int inputArray[], int length,int outPutArray[]);
int* changedp(int A, int inputArray[],int length,int outputArray[]);


int main(int argc, char *argv[])
{

    int length = 5;
    int V[5];
    int outputArrayGreedy[5];
    int outputArrayDP[5];
    vector<int> outputVectorSlow;
    int greedySum;
    int DPSum;
    int slowSum;


    //Set coin denominations
    V[0] = 1;
    V[1] = 5;
    V[2] = 10;
    V[3] = 25;
    V[4] = 50;

//    for(int i = 1; i < 16; i++){
//        V[i] = i * 2;
//    }

    //Open file
    string filename = "time.txt";
    ofstream outputFile;
    outputFile.open(filename.c_str(),ofstream::out|ofstream::app);

    //Initial write to file
    //outputFile << "Amount" << "\t" << "Greedy" << "\t" << "Dynamic" << "\t" << "Slow" << endl;

    for(int i = 1990000; i <=2000000 ; i++){
        //Initialize vars to 0
        greedySum = 0;
        DPSum = 0;
        slowSum = 0;

      //  for (int index = 0; index < length; index++)
       // {
        //    outputArrayGreedy[index] = 0;
        //    outputArrayDP[index] = 0;
        //    outputVectorSlow[index] = 0;

        //}



        //Run the algorithms

        outputFile << i << "\t";

        //Greedy
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        //changegreedy(i, V, length, outputArrayGreedy);
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
        //outputFile << time_span.count() << "\n";

        //DP
        t1 = high_resolution_clock::now();
        changedp(i, V, length, outputArrayDP);
        t2 = high_resolution_clock::now();
        time_span = duration_cast<duration<double>>(t2 - t1);
        outputFile << time_span.count() << "\n";

        //Slow
        /*t1 = high_resolution_clock::now();
        outputVectorSlow = changeslow(i, V, length);
        t2 = high_resolution_clock::now();
        time_span = duration_cast<duration<double>>(t2 - t1);
        outputFile << time_span.count() << endl;*/

        //Sum the arrays (Uncomment the below code if you want to print min coins instead of time)
        /*
        for(int i = 0; i < length; i++){
            greedySum += outputArrayGreedy[i];
            DPSum += outputArrayDP[i];
            slowSum += outputVectorSlow[i];
        }
        */
        //Uncomment this to print values to file
        //outputFile << i << "\t" << greedySum << "\t" << DPSum << "\t" << slowSum << endl;


    }
    //Print array to check it
    //for(int i = 0; i < 16; i++){
    //    cout << V[i] << " ";
    //}


    outputFile.close();
    return 0;
}

//****************************************************************************************************************************************
//*****************************************************insert changeslow here*************************************************************
//****************************************************************************************************************************************
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
