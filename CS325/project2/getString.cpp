#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int*> getValues(string fileName);

int main()
{
    vector<int*> values;
    values = getValues("Coin1.txt");
    int* coinArray;

    for (int index = 0; index < values.size();index++)
    {
        coinArray = values[index];

        int length = *values[index];

        cout<<"[";
        for(int i = 1; i<= length;i++)
        {
            cout<<*(coinArray+i)<<" ";
        }
        cout<<"]"<<endl;

    }

    cout<<endl;

    return 0;
}

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
            char* temp = (char *)malloc(40);
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
