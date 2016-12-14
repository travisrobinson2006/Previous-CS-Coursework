/************************************************************************
 *Author: Travis Robinson
 *05/28/2015
 *Assignment 9 Part 1
 *StringList Class Function Implementation File
 ************************************************************************/

#include "StringList.hpp"

/*********************************************************************
**Aceepts a string as parameter, adds it as a new node
*********************************************************************/
void StringList::add(std::string stringToAdd)
{
	if (head == NULL)
	{
		head = new ListNode(stringToAdd);
	}
	else
	{
		ListNode *nodePtr = head;
		while (nodePtr->nextNode != NULL)
		{
			nodePtr = nodePtr->nextNode;
		}
		nodePtr->nextNode = new ListNode(stringToAdd);
	}	
}
/*********************************************************************
**Searches nodes for the parameter, returns the node number or -1 if not found
*********************************************************************/
int StringList::positionOf(std::string stringSearch)
{
	int counter = 0;
	int position = -1;
	ListNode *nodePtr = head;
	while (nodePtr)
	{
		if (nodePtr->nodeString == stringSearch)
		{
			position = counter;
			break;
		}
		counter++;
		nodePtr = nodePtr->nextNode;
	}
	return position;
}
/*********************************************************************
**Accepts a string parameter, sets the nodeNumber to that string
*********************************************************************/
bool StringList::setNodeVal(int nodeNumber, std::string stringSet)
{
	bool inRange = false;
	int counter = 0;
	ListNode *nodePtr = head;
	while (nodePtr != NULL)
	{
		if (counter == nodeNumber)
		{
			nodePtr->nodeString = stringSet;
			inRange = true;
		}
		counter = counter+1;
		nodePtr = nodePtr->nextNode;
	}
	return inRange;
}
/*********************************************************************
**Returns a vector with the same size, order and values as StringList
*********************************************************************/
std::vector<std::string> StringList::getAsVector()
{
	std::vector<std::string> vectorStringOut;
	ListNode *nodePtr = head;
	while (nodePtr != NULL)
		{
			vectorStringOut.push_back(nodePtr->nodeString);
			nodePtr = nodePtr->nextNode;
		}
	return vectorStringOut;
}
/*********************************************************************
**Default constructor, creates empty node list
*********************************************************************/
StringList::StringList()
{
	head = NULL;
}
/*********************************************************************
**Returns a vector with the same size, order and values as StringList
**Includes const for use with copy constructor
*********************************************************************/
std::vector<std::string> StringList::getAsVector() const
{
	std::vector<std::string> vectorStringOut;
	ListNode *nodePtr = head;
	while (nodePtr != NULL)
		{
			vectorStringOut.push_back(nodePtr->nodeString);
			nodePtr = nodePtr->nextNode;
		}
	return vectorStringOut;
}
/*********************************************************************
**Copy constructor, creates a copy of the parameter list
*********************************************************************/
StringList::StringList(const StringList& listToCopy)
{
	head = NULL;	
	std::vector<std::string> tempVector = listToCopy.getAsVector();
	for (int index = 0; index<tempVector.size(); index++)
	{
		add(tempVector[index]);
	}
}
/*********************************************************************
**Destructor, destroys all dynamically created nodes
*********************************************************************/
StringList::~StringList()
{
	ListNode *nodePtr = head;
	while (nodePtr != NULL)
	{
		ListNode *garbage = nodePtr;
		nodePtr = nodePtr->nextNode;
		delete garbage;
	}
}

