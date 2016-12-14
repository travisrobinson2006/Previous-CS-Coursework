#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    vector<int> numberBuffer;
    ifstream inputFile;
    inputFile.open ("MSS_testproblems.txt");
    while(inputFile.get() != 10)
    {
        if (isdigit(inputFile.get()))
        {
            cout<<inputFile.get();
        }

    }

    //if (isdigit(inputFile)==true)
    //{
    //    numberBuffer.push_back()
    //}
    inputFile.close();
    return 0;
}
