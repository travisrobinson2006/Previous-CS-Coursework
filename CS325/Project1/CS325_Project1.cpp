#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace std;

struct result {
    int sum;
    int startIndex;
    int endIndex;
};

void removeBracket(vector<string>& v);
void runAlgorithms(const vector<int> &v, int size, int l, int h, ofstream &ofs, struct result *r);
void maxSubArraySum1(const vector<int> &v, int vectorSize, struct result *r);
void maxSubArraySum2(const vector<int> &v, int vectorSize, struct result *r);
struct result * maxSubArraySum3(const vector<int> &v, int l, int h);
void maxSubArraySum4(const vector<int> &v, int vectorSize, struct result *r);


int main()
{
    //initializing struct and struct pointer
    struct result newResult;
    newResult.sum = 0;
    newResult.startIndex = 0;
    newResult.endIndex = 0;
    struct result *r = &newResult;

    vector <vector <string> > data; //create vector of string vectors to hold arrays from file
    ifstream infile( "MSS_Problems.txt" );  //create instance of ifstream to read file

    while (infile)
    {
        string s;
        if (!getline( infile, s )) break;

        istringstream ss( s );
        vector <string> record;

        while (ss)
        {
            string s;
            if (!getline( ss, s, ',' )) break;  //separate each string by commas
            record.push_back( s );
        }

        data.push_back( record );
    }
    if (!infile.eof())
    {
        cerr << "End of file!\n";
    }

    //initialize output filestream
    ofstream ofs;
    ofs.open("MSS_Results.txt");

    vector <vector <int> > newData(data.size());    //initialize 2d vector of size data.size() to store integers

    //for each vector, call removeBracket to remove brackets and spaces then convert to ints and store in 2d vector of ints
    for (unsigned int i = 0; i < data.size(); i++)
    {
        removeBracket(data[i]);
        for (unsigned int j = 0; j < data[i].size(); j++)
        {
            int num = atoi(data[i].at(j).c_str());
            newData[i].push_back(num);
        }
    }

    //record data from each array and algorith to the file
    for (unsigned int i = 0; i < newData.size(); i++)
    {
        runAlgorithms(newData[i], newData[i].size(), 0, newData[i].size()-1, ofs, r);
    }

    //close the output filestream
    ofs.close();

    //explain program and close
    cout << "This program has run algorithms on the data from 'MSS_Problems.txt'." << endl;
    cout << "The max sum of a possible subarray using each algorithm is" << endl;
    cout << "listed in 'MSS_Results.txt'." << endl;

    return 0;
}
/*
*Remove Bracket:
*Takes as parameters a vector of strings and removes brackets from any string
*/
void removeBracket(vector<string>& v)
{
    for (unsigned int i = 0; i < v.size(); i++){
        for (unsigned int j = 0; j < v[i].size(); j++){
            if (v[i][j] == ']' || v[i][j] == '[' || v[i][j] == ' '){
                v[i].erase(j,1);
            }
        }
    }
}

/*
*Run Algorithms:
*Takes as parameters a vector of ints and an int containing the size of the array
*Outputs the maximum subarray and the maximum sum for each subarray
*/
void runAlgorithms(const vector<int> &v, int size, int l, int h, ofstream &ofs, struct result *r)
{

    ofs << "For the array [";
    for (unsigned int i = 0; i < v.size(); i++)
    {
        ofs << v[i];
        if (i != v.size()-1)
        {
            ofs << ", ";
        }
    }
    ofs << "]" << endl << endl;

    //run algorithm 1 and print to file
    maxSubArraySum1(v, v.size(), r);
    ofs << "Algorithm 1 found the subarray: \n[";
    for (unsigned int j = r->startIndex; j < r->endIndex + 1; j++)
    {
        ofs << v[j];
        if (j != r->endIndex)
        {
            ofs << ", ";
        }
    }
    ofs << "] \nWith a sum of " << r->sum << endl << endl;
    //cout << "Values for 1: " << r->sum << ", " << r->startIndex << ", " << r->endIndex << endl;

    //run algorithm 2 and print to file
    maxSubArraySum2(v, v.size(), r);
    ofs << "Algorithm 2 found the subarray: \n[";
    for (unsigned int j = r->startIndex; j < r->endIndex + 1; j++)
    {
        ofs << v[j];
        if (j != r->endIndex)
        {
            ofs << ", ";
        }
    }
    ofs << "] \nWith a sum of " << r->sum << endl << endl;
    //cout << "Values for 2: " << r->sum << ", " << r->startIndex << ", " << r->endIndex << endl;

    //run algorithm 3 and print to file
    r = maxSubArraySum3(v, 0, size - 1);
    ofs << "Algorithm 3 found the subarray: \n[";
    for (unsigned int j = r->startIndex; j < r->endIndex + 1; j++)
    {
        ofs << v[j];
        if (j != r->endIndex)
        {
            ofs << ", ";
        }
    }
    ofs << "] \nWith a sum of " << r->sum << endl << endl;
    //cout << "Values for 2: " << r->sum << ", " << r->startIndex << ", " << r->endIndex << endl;

    //run algorithm 4 and print to file
    maxSubArraySum4(v, v.size(), r);
    ofs << "Algorithm 4 found the subarray: \n[";
    for (unsigned int j = r->startIndex; j < r->endIndex + 1; j++)
    {
        ofs << v[j];
        if (j != r->endIndex)
        {
            ofs << ", ";
        }
    }
    ofs << "] \nWith a sum of " << r->sum << endl << endl;
    //cout << "Values for 4: " << r->sum << ", " << r->startIndex << ", " << r->endIndex << endl;


    ofs << endl;
}


/*
*Algorithm 1:
*Takes as parameters an array of ints and an int containing the size of the array
*Outputs the maximum subarray sum
*/
void maxSubArraySum1(const vector<int> &v,int vectorSize, struct result *r)
{
    //Special case for array containing 1 element
    if(vectorSize == 1){
        r->sum = v[0];
        r->startIndex = 0;
        r->endIndex = 0;
        return;
    }

    int sum;
    r->sum = -1000000;
    r->startIndex = 0;
    r->endIndex = vectorSize - 1;
    for (int index = 0; index < (vectorSize) + 1; index++)
    {
        for(int j= index; j < vectorSize + 1; j++)
        {
            sum = 0;
            for(int i = index; i < j; i++)
            {
                sum = sum+v[i];
                if(sum > r->sum)
                {
                    r->endIndex = i;
                }
            }
            if(sum > r->sum)
            {
                r->sum = sum;
                r->startIndex = index;

            }

        }
    }
}
/*
*Algorithm 2:
*Takes as parameters an array of ints and an int containing the size of the array
*Outputs the maximum subarray and the maximum sum
*/
void maxSubArraySum2(const vector<int> &v,int vectorSize, struct result *r)
{
    int sum;
    r->sum = -1000000;//arbitrary small number
    r->startIndex = 0;
    r->endIndex = vectorSize;
    for (int index = 0; index < vectorSize; index++)
    {
        sum = 0;
        for(int i = index; i < vectorSize; i++)
        {
            sum = sum+v[i];
            if (sum > r->sum)
            {
                r->sum = sum;
                r->startIndex = index;
                r->endIndex = i;
            }
        }
    }
}
/*
*Algorithm 3:
*Takes as parameters an array of ints, and ints containing the index of the first and last elements
*Outputs the maximum subarray sum
*/
struct result * maxSubArraySum3(const vector<int> &v, int l, int h)
{

    struct result * r = new struct result;
    r->sum = 0;
    r->startIndex = 0;
    r->endIndex = 0;

   // Base Case: single element
   if (l == h){
     r->sum = v[l];
     r->startIndex = l;
     r->endIndex = h;

     return r;
   }

   // Find middle point
   int m = (l + h)/2;

    //Find the maximum sub arrays in the left and right halves
    struct result * leftResult = maxSubArraySum3(v, l, m);
    struct result * rightResult = maxSubArraySum3(v, m+1, h);

    //Get the max sub array which crosses the midpoint

    //Left side of midpoint
    int sum = 0;
    int crossingStartIndex = 0;
    int leftSum = -1000000000;
    int leftIndex = m;          //For keeping track of subarray's starting index
    for (int i = m; i >= l; i--)
    {
        sum = sum + v[i];
        if (sum > leftSum){
            leftSum = sum;
            leftIndex = i;
        }
    }

    // Right side of midpoint
    sum = 0;
    int rightSum = -1000000000;
    int rightIndex = m + 1;         //For keeping track of subarray's ending index
    for (int i = m+1; i <= h; i++)
    {
        sum = sum + v[i];
        if (sum > rightSum){
            rightSum = sum;
            rightIndex = i;
        }
    }
    int crossingSum = leftSum + rightSum;

    //Find and return the maximum

    //Compare left and right max subarrays first
    if(leftResult->sum >= rightResult->sum){
        r->sum = leftResult->sum;
        r->startIndex = leftResult->startIndex;
        r->endIndex = leftResult->endIndex;
    }
    else{
        r->sum = rightResult->sum;
        r->startIndex = rightResult->startIndex;
        r->endIndex = rightResult->endIndex;
    }

    //Now compare the winner to the crossing sum and change r's values if necessary
    if(crossingSum > r->sum){
        r->sum = crossingSum;
        r->startIndex = leftIndex;
        r->endIndex = rightIndex;
    }

    delete leftResult;
    delete rightResult;

    return r;
}
/*
*Algorithm 4:
*Takes as parameters an array of ints and an int containing the size of the array
*Outputs the maximum subarray and the maximum sum
*/
void maxSubArraySum4(const vector<int> &v, int vectorSize, struct result *r)
{
    int highIndex = vectorSize - 1;
    int lowIndex = 0;
    r->sum = v[0];
    int ending_here_sum = v[0];

    for(int j = 1; j<vectorSize;j++)
    {
        highIndex = j;
        if (ending_here_sum>0)
        {
            ending_here_sum = ending_here_sum+v[j];
        }
        else
        {
            lowIndex = j;
            ending_here_sum = v[j];
        }
        if (ending_here_sum > r->sum)
        {
            r->sum = ending_here_sum;
            r->startIndex = lowIndex;
            r->endIndex = (highIndex);
        }
    }
}
