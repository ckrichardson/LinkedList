//Author:  Clifford Richardson
//Course:  CS 302
//Instructor:  Dr. Harris
//Functionality:  This file implements a linked list for the ListLinked.h file

#include "ListLinked.h"


//Function:  Parameterized constructor
//Accepts the "ignored" paramter, which is ignored and creates
//a new ListNode of values NULL
template <typename DataType>
List<DataType>::List(int ignored)
{

	head = NULL;
}

//Function:  Parameterized ListNode constructor
//Accepts value ofr dataItem and point for next node, then sets both values
//of the changing ListNode object to the passed values.
template <typename DataType>
List<DataType>::ListNode::ListNode(const DataType& nodeData, ListNode* nextPtr)
{
	dataItem = nodeData;
	next = nextPtr;
}

//Function:  Copy constructor
//Accepts another List object, and sets values equal to eachother
template <typename DataType>
List<DataType>::List(const List& other)
{
	(*this) = other;
}


//Function:  =operator
//takes two List objects and makes a deep copy for the calling object.
template <typename DataType>
List<DataType>& List<DataType>::operator=(const List& other)
{
	ListNode* temp = new ListNode();
	ListNode* nextNode = new ListNode();
	ListNode* otherNode = &other.head;
	head = &nextNode;
	cursor = head;

	while(otherNode.next != NULL)
	{
		temp->dataItem = otherNode->dataItem;
		temp->next = &nextNode;

		temp = &nextNode;

		nextNode = new ListNode();


	}


	return head;


}

//Function:  Destructor
//Releases memories to the computer overlords once the program ends
template <typename DataType>
List<DataType>::~List()
{
	clear();
}

//Function:  insert
//Inserts node after cursor, and moves cursor to new node
template <typename DataType>
void List<DataType>::insert(const DataType& newDataItem) throw (logic_error)
{

	if(isFull() == true)
		throw logic_error("insert() full list");

	if(head != NULL)
	{
		ListNode* current = cursor;
		//cout << "CURSOR: " << cursor->dataItem;
		ListNode* temp = new ListNode(newDataItem, cursor->next);

		current->next = temp;
		cursor = temp;
		//cout << temp->dataItem;



			return;

	}



	head = new ListNode(newDataItem, NULL);
	cursor = head;





}


//Function:  remove
// Removes a node from the list, returns an error if list is empty
template <typename DataType>
void List<DataType>::remove() throw (logic_error)
{
ListNode* temp;

	if(cursor == head)
	{
		if(cursor->next == NULL)
		{
			cursor = NULL;
			head = NULL;
			return;
		}

		temp = cursor;
		cursor = cursor->next;
		delete[] temp;

	}

else if(cursor->next == NULL)
{
	temp = cursor;

	gotoPrior();
	cursor->next = NULL;

	delete[] temp;
}
else
{
	ListNode* before;
	ListNode* after;

	gotoPrior();
	before = cursor;
	gotoNext();
	temp = cursor;
	gotoNext();
	after = cursor;

	before->next = after;
	delete[] temp;
}

}




//Function:  replace
//Replaces the cursor Node data value with passed value
template <typename DataType>
void List<DataType>::replace(const DataType& newDataItem) throw (logic_error)
{
	if(head == NULL)
		throw logic_error("replace() empty list");

	cursor->dataItem = newDataItem;
	return;
}

//Function:  clear
//clears all nodes
template <typename DataType>
void List<DataType>::clear()
{

	if(isEmpty() == true)
		return;

	ListNode* temp = new ListNode(NULL, NULL);
	while(head->next != NULL)
	{
		temp = head;

		head = head->next;

		delete[] temp;
	}

	head = NULL;
	cursor = NULL;
}

//Function:  isEmpty()
//Returns true if empty (no nodes), false if not empty (nodes exist)
template <typename DataType>
bool List<DataType>::isEmpty() const
{
	if(head == NULL)
		return true;

	if(head != NULL)
		return false;
}

//Function:  isFull()
//Returns true if full (max nodes), false if not full (more nodes available)
template <typename DataType>
bool List<DataType>::isFull() const
{
	return false;
}

//Function:  gotoBeginning
//Positions cursor at the beginning of the List
template <typename DataType>
void List<DataType>::gotoBeginning() throw (logic_error)
{
	if(isEmpty() == true)
		throw logic_error("gotoBeginning() empty list");

	cursor = head;
}

//Function:  gotoEnd
//Positions cursor at the end of the List
template <typename DataType>
void List<DataType>::gotoEnd() throw (logic_error)
{
	if(isEmpty() == true)
		throw logic_error("gotoEnd() empty list");

	gotoBeginning();

	while(cursor->next != NULL)
	{
		cursor = cursor->next;
	}
}


//Function:  gotoNext
//Moves cursor to next node if possible
template <typename DataType>
bool List<DataType>::gotoNext() throw (logic_error)
{
	if(isEmpty() == true)
	{
		throw logic_error("gotoNext empty list");
		return false;
	}



	if(cursor->next == NULL)
		return false;

	cursor = cursor->next;

	return true;
}

//Function:  gotoPrior
//Moves cursor to prior node if possible
template <typename DataType>
bool List<DataType>::gotoPrior() throw (logic_error)
{
	ListNode* temp = head;

	if(isEmpty() == true)
	{
		throw logic_error("gotoPrior empty list");
		return false;
	}


	if(head->next == NULL)
		return false;



	while(temp->next != cursor && temp != cursor)
	{
		temp = temp->next;
	}

	if(temp == cursor)
	{
		return false;
	}
	cursor = temp;

	return true;
}

//Function:  moveToBeginning
//Moves Node to beginning of an existing list
template <typename DataType>
void List<DataType>::moveToBeginning() throw (logic_error)
{
	ListNode* temp;
	ListNode* before;
	ListNode* after;

	if(head == NULL)
		throw logic_error("moveToBeginning() empty list");

	if(cursor->next == NULL)
	{
		temp = cursor;
		gotoPrior();
		before = cursor;

		temp->next = head;
		head = temp;
		cursor = temp;
		before->next = NULL;

	}

	if(cursor == head)
	{
		return;
	}

	gotoPrior();
	before = cursor;
	gotoNext();
	temp = cursor;
	gotoNext();
	after = cursor;

	temp->next = head;
	head = temp;
	cursor = head;
	before->next = after;

	return;


}


//Function:  insertBefore
//Inserts a node before an existing node (if not creates new node)
template <typename DataType>
void List<DataType>::insertBefore(const DataType& newDataItem) throw (logic_error)
{

	ListNode* beforeCursor = new ListNode(NULL, NULL);
	ListNode* temp = new ListNode(NULL, NULL);
	ListNode* afterCursor = new ListNode(NULL, NULL);

	if(isFull() == true)
		throw logic_error("insertBefore() full list");

	if(head == NULL)
	{
		head = new ListNode(newDataItem, NULL);
		return;
	}

	if(head->next == NULL)
	{
		temp = head;
		head = new ListNode(newDataItem, temp);
	}



	gotoPrior();
	beforeCursor = cursor;
	gotoNext();
	gotoNext();
	afterCursor = cursor;

	temp->dataItem = newDataItem;
	temp->next = afterCursor;

	beforeCursor->next = temp;

	return;
}


//Function:  showStructure
//Used for debugging, shows the actual linked list positions and values
template <typename DataType>
void List<DataType>::showStructure() const
{
	if ( isEmpty() )
	{
		 cout << "Empty list" << endl;
	}
	else
	{
	for (ListNode* temp = head; temp != 0; temp = temp->next) {
		if (temp == cursor) {
	cout << "[";
		}

		// Assumes that dataItem can be printed via << because
		// is is either primitive or operator<< is overloaded.
		cout << temp->dataItem;

		if (temp == cursor) {
	cout << "]";
		}
		cout << " ";
	}
	cout << endl;
	}



	return;
}


//Function:  getCursor
//Returns value of ListNode dataItem at the current cursor position
template <typename DataType>
DataType List<DataType>::getCursor() const throw (logic_error)
{
	return cursor->dataItem;
}
