/************************************************************************
 *Author: Travis Robinson
 *05/30/2015
 *Assignment 9 Part 2
 *postfixEval function
 ************************************************************************/


#include <stack>
#include <cstdlib>
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

/*********************************************************************
**postfixEval function accepts c-string as paramter, evaluates it
**using postfix arithmetic notation, returns result as double
*********************************************************************/

double postfixEval (char evaluate[])
{
	double total = 0;//total value, to be returned by function-initialized to 0 for testing
	double number1, number2;//storage values, used to hold numbers pulled from stack for evaluation
	vector<string> temp;//vector, used as a transfer medium to move values from c-string to stack
	stack<double> holdForEval;//the stack that holds numbers for postfix evaluation
	char * pch;//char pointer, used for strkot function
	pch = strtok (evaluate," ");
	//while loop pushes values from c-string to the vector
	while (pch != NULL)
  	{
		temp.push_back(pch);
		pch = strtok (NULL, " ");
	}
	//for loop pushes values from the vector to the stack
	//checks for operators and evaluates top 2 numbers from stack using operator found
	//assigns top 2 numbers from stack to number1 and number2, pushes result onto stack
	for (int index = 0; index < temp.size(); index++)
  	{	
		if (temp[index] == "+")
		{
			number2 = holdForEval.top();
			holdForEval.pop();
			number1 = holdForEval.top();
			holdForEval.pop();
			holdForEval.push(number1+number2);
		}
		else if (temp[index] == "-")
		{
			number2 = holdForEval.top();
			holdForEval.pop();
			number1 = holdForEval.top();
			holdForEval.pop();
			holdForEval.push(number1-number2);
		}
		else if (temp[index] == "*")
		{
			number2 = holdForEval.top();
			holdForEval.pop();
			number1 = holdForEval.top();
			holdForEval.pop();
			holdForEval.push(number1*number2);
		}
		else if (temp[index] == "/")
		{
			number2 = holdForEval.top();
			holdForEval.pop();
			number1 = holdForEval.top();
			holdForEval.pop();
			holdForEval.push(number1/number2);
		}
		else 
		{
			holdForEval.push(atof(temp[index].c_str()));
		}
	}
	//pulls final number from the stack and returns it	
	total = holdForEval.top();
	return total;
}

/*
int main()
{

	char postfix1[12] = "4 5 +";
	char postfix2[20] = "25 12 7 - 2 * /";

	cout<<postfixEval(postfix1)<<endl;
	cout<<postfixEval(postfix2)<<endl;

	return 0;
}
*/
