#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

template <typename T>
class LinkedList
{


public:

	//Nested Node class
	struct Node
	{
		T data;
		Node* next; //pointer to the next node
		Node* prev; //pointer to the prev node
	};

	//prototypes here

	/*==== Behaviors ====*/
	void PrintForward() const; //Iterate through all the nodes and print
	void PrintReverse() const; //Iterate through all the nodes and print backwards
	void PrintForwardRecursive(const Node* node) const; //takes in a pointer node (Starting node), and then from there recursively visit each node that follows and print their values
	void PrintReverseRecursive(const Node* node) const; //takes in a pointer node, and then from the recursively visit each node before it and print their values. 

	/*==== Accessors ====*/
	unsigned int NodeCount() const; //How many things are stored in this list?
	Node* Head(); //Return the head pointer
	const Node* Head() const; //Return the head pointer in const version
	Node* Tail(); //Return the tail pointer
	const Node* Tail() const; //Return the tail pointer in const version
	Node* GetNode(unsigned int index); //Given an index, return a pointer at that index. Throw exception out_of_range if it is. 
	const Node* GetNode(unsigned int index) const; //Given an index, return a pointer at that index in const. Throw exception out_of_range if so.
	Node* Find(const T& data); //Find the first node with a data value matching the passed in parameter, returning the pointer. Return nullptr if none found
	const Node* Find(const T& data) const; //Const version of //Find the first node with a data value matching the passed in parameter, returning the pointer. Return nullptr if none found
	void FindAll(vector<Node*>& outData, const T& value) const; //Find all nodes who match the parameter value, store a pointer to that node in the passed in vector

	/*==== Insertion ====*/
	void AddHead(const T& data); //Create a new Node at the front of the list to store the passed parameter
	void AddTail(const T& data); //Create a new Node at the end of the list to store the passed parameter
	void AddNodesHead(const T* data, unsigned int count);
	void AddNodesTail(const T* data, unsigned int count);
	void InsertAt(const T& data, unsigned int index); //Inserts a new node to store the first parameter at the index-th location. 
	void InsertAfter(Node* node, const T& data); //Given a pointer to a node, create a new node to store passed value after indicated node
	void InsertBefore(Node* node, const T& data);//Given a pointer to a node, create a new node to store passed value before indicated node

	/*==== Removal ====*/
	bool RemoveHead(); //Delete the first node in the list, returns whether or not the node was removed
	bool RemoveTail(); //Deletes the last node in the list, returns whether or not the node was removed
	unsigned int Remove(const T& data); //Remove ALL nodes contained values matching that of the passed in parameter. Returns how many instances where removed
	bool RemoveAt(unsigned int index); //Deletes the index-th node from the list, returning whether or not operation was successful
	void Clear(); //Deletes all Nodes

	/*==== Operators ====*/
	LinkedList<T>& operator=(const LinkedList<T>& rhs); //copy assignment operator
	const T& operator[](unsigned int index) const; //Const Overloaded subscript operator, takes an index and returns data from index'th node 
	T& operator[](unsigned int index); //Overloaded subscript operator, takes an index and returns data from index'th node
	bool operator==(const LinkedList<T>& rhs) const; //overloaded equality operator. Does listA = listB?

	/*==== Construction / Destruction ====*/
	LinkedList(); //Default constructor
	LinkedList(const LinkedList<T>& list); //Constructor 
	~LinkedList(); //Destructor


private:
	//Variables here 
	Node* head;
	Node* tail;
	unsigned int nodeCount = 0;
};



/*==== Construction / Destruction ====*/

template <typename T>
LinkedList<T>::LinkedList() //Default constructor
{
	nodeCount = 0;
	head = nullptr;
	tail = nullptr;
}

template <typename T>
LinkedList<T>::~LinkedList() //Destructor
{
	Node* deleteNode = head;
	while (deleteNode != nullptr)
	{
		Node* deleteNodeNext = deleteNode->next;
		delete deleteNode;
		deleteNode = deleteNodeNext;
	}

}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) //Copy constructor 
{
	// May need nodeCount = 0? 
	//May need 
	this->nodeCount = list.nodeCount;
	nodeCount = 0; // The AddHead function adds 1 to nodeCount every node, the nodeCount should start at 0. 
	int counterCon = list.nodeCount - 1; // May be list.nodeCount? 
	while (counterCon >= 0) //May not be >= 0? how do I get it to execute at 0 and nothing less
	{
		AddHead(list.GetNode(counterCon)->data);
		counterCon = counterCon - 1;
	}
}

/*==== Insertion ====*/

template <typename T>
void LinkedList<T>::AddHead(const T& data) //Create a new Node at the front of the list to store the passed parameter
{

	Node* newNode = new Node(); // Create a new node
	newNode->data = data;

	if (nodeCount == 0) //If there is no nodes, this newnode will be the first one.
	{
		head = newNode; //assign the head to this single node
		tail = newNode; //assign the tail to this single node
		head->prev = nullptr; //there is nothing behind the head
		head->next = nullptr; //there is nothing in front of the head

		tail->prev = nullptr; //there is nothing behind the tail
		tail->next = nullptr; //there is nothing in front of the tail
		nodeCount = nodeCount + 1; // update the node count to be 1.
	}

	else
	{
		head->prev = newNode; //Assign the newnode to the old head's left
		newNode->next = head; //Assign newNode's next pointer to be the old head
		head = newNode; //Reassign the head to be newNode

		if (nodeCount == 1) //If there is only 1 node, update the tail's prev pointer too
		{
			tail->prev = newNode;
		}
		nodeCount = nodeCount + 1; //update the node count by 1
	}


	/*Node* newNode = new Node(); //Make a new node
	newNode->data = data; // This new node's data is what was passed in

	if (nodeCount > 1)
		//If theres two (or more) nodes, and I just made a third node (newNode), the count will only be 2. So it'll take this and do its normal
		// thing of just adding a new head to an occupied linked list.
	{
		newNode->next = head; // Say this new node's next points to the current head
		head->prev = newNode; //Say the current head's prev pointer points to the new node.
		head = newNode; // Then say the current head points to the new node
		newNode->prev = nullptr; // Since it's at the front, the prev is nullptr.
		nodeCount = nodeCount + 1; // Update the count of nodes
	}
	if (nodeCount == 0) //If there are no nodes in it just yet, it'll just be the single head.
	{
		head = newNode; // The head points to this newNode
		tail = newNode; // The tail points to this newNode (cause theres only one node)
		newNode->prev = nullptr; // There is nothing behind newNode
		newNode->next = nullptr; // There is nothing in front of newNode
		nodeCount = nodeCount + 1; // Node count will be incremented by 1.
	}
	if (nodeCount == 1) //If there is just a single node already, and you want to add in a new node and make it head
	{
		newNode->next = head; // point the newNode's next pointer to the current head
		head->prev = newNode; //point the current head's prev pointer to the newNode
		head = newNode; //point the head pointer to the newNode
		newNode->prev = nullptr; //since newNode is the new head, there is nothing prev to it. // This one isnt in the other!!!
		tail->prev = newNode; //the prev node from the last one is the newNode.
		nodeCount = nodeCount + 1; //update the node count
	} */
}

template <typename T>
void LinkedList<T>::AddTail(const T& data) // Create a new node at the end of the list to store the passed parameter 
{
	Node* newNode = new Node(); // Make a new node
	newNode->data = data; // Pass in the value 

	if (nodeCount > 1) //If there is more than 1 node already in existence, I won't have to alter the head 
	{
		newNode->prev = tail; //Since its going last, it's prev will point towards the former tail
		newNode->next = nullptr; //Since it's last, it's next pointer will point towards null
		tail->next = newNode; // Assigns the former tail's next pointer to point towards newNode
		tail = newNode; // Assign the newNode to be the new tail
		nodeCount = nodeCount + 1;
		//maybe tail->next = nullptr? once the tail changes to update its next?
	}
	if (nodeCount == 1) //If there is only one node, I need to change the head AND the tail
	{
		newNode->prev = tail; //Since its going last, it's prev will point towards the former tail
		newNode->next = nullptr; //Since it's last, it's next pointer will point towards null
		tail->next = newNode; // Assigns the former tail's next pointer to point towards newNode
		tail = newNode; // Assign the newNode to be the new tail
		head->next = newNode; // Assign the head's next pointer to be newNode
		nodeCount = nodeCount + 1;
		//maybe tail->next = nullptr? once the tail changes to update its next?
	}
	if (nodeCount == 0) //If there is nothing and this tail is the first thing, assign the tail and head to it, and set pointers to null
	{
		tail = newNode; // Assign the single node to be the tail
		head = newNode; // Also assign the single node to be the head 
		head->next = nullptr; //There is nothing on the right side 
		tail->prev = nullptr; //There is nothing on the left side
		nodeCount = nodeCount + 1;
	}
}

template <typename T>
void LinkedList<T>::AddNodesTail(const T* data, unsigned int count) //Given an array of values, insert a node for each single value at the end of the list
{
	//Use a for loop that is counting up, and pass each index value of data to AddTail();
	for (unsigned int i = 0; i < count; i++)
	{
		AddTail(data[i]);
	}
}

template <typename T>
void LinkedList<T>::AddNodesHead(const T* data, unsigned int count) //Given an array of values, insert a node for each single value at the front of the list
{
	// Use a for loop that is counting down, and each iteration call AddHead() passed with each array index value
	for (int i = count - 1; i >= 0; i--)
	{
		AddHead(data[i]);
	}
}

template <typename T>
void LinkedList<T>::InsertAt(const T& data, unsigned int index) //Inserts a new node to store the first parameter at the index-th location. 
{
	unsigned int maximum = index; //The maximum index the for loop is suppose to go to
	Node* rightPointer = head; //Make a pointer to point at the head //MAY NEED TO BE INSIDE ELSE LOOP


	if (index > nodeCount) // May be >= 
	{
		throw out_of_range("Bruh!");

	}

	if (index != nodeCount) //Means its an index thats not tail
	{
		Node* newNode = new Node(); //The actual node being squeezed in
		newNode->data = data; //copy over the data passed in
		for (unsigned int i = 0; i < maximum; i++) //MAY NEED TO BE I <= MAXIMUM. IF INDEX IS 3 FORLOOP MIGHT ONLY GO TO INDEX 2 //for loop to iterate to the required index
		{
			rightPointer = rightPointer->next;
		}
		//Squeeze the newNode in before nodePointer, whos index should be at + 1 the given node
		newNode->next = rightPointer;
		newNode->prev = rightPointer->prev;
		if (index == 0) //If the user said they wanted their node inputted at index 0, it would become the new head
		{
			head = newNode;
		}
		else
		{
			Node* leftPointer = rightPointer->prev;
			leftPointer->next = newNode;
		}
		rightPointer->prev = newNode;
		nodeCount = nodeCount + 1;
	}
	else // If the index and nodecount are the same, this will become the new tail
	{
		Node* newNode = new Node();
		tail->next = newNode;
		newNode->prev = tail;
		newNode->next = nullptr;
		newNode->data = data;
		tail = newNode;
		nodeCount = nodeCount + 1;
	}

}

template <typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& data) //Given a pointer to a node, create a new node to store passed value after indicated node
{
	nodeCount = nodeCount + 1;
	Node* newNode = new Node();
	Node* nodeAfter = node->next;
	newNode->next = node->next;
	newNode->data = data;
	nodeAfter->prev = newNode->next;
	node->next = newNode;
	newNode->prev = node;




}

template <typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& data) //Given a pointer to a node, create a new node to store passed value before indicated node
{
	nodeCount = nodeCount + 1;
	Node* newNode = new Node();
	Node* nodePrev = node->prev;
	newNode->prev = node->prev;
	newNode->data = data;
	nodePrev->next = newNode;
	node->prev = newNode;
	newNode->next = node;


}

/*==== Removal ====*/

template <typename T>
bool LinkedList<T>::RemoveHead() //Delete the first node in the list, returns whether or not the node was removed
{
	bool deleted = false;
	if (nodeCount == 1) //If theres only one node, set everything to nullptr and delete the single node. Return true
	{
		nodeCount = nodeCount - 1;
		Node* newNode = head;
		tail = nullptr;
		head = nullptr;
		delete newNode;
		deleted = true;
		return deleted;
	}
	if (nodeCount == 0) // If theres zero, theres nothing to delete. Return false
	{
		return deleted;
	}
	else //If there is more than 1 node, it will set the current head->next to be head. Return true
	{
		nodeCount = nodeCount - 1;
		Node* newNode = head;
		head = newNode->next;
		head->prev = nullptr;
		delete newNode;
		deleted = true;
		return deleted;

	}
}

template <typename T>
bool LinkedList<T>::RemoveTail() //Deletes the last node in the list, returns whether or not the node was removed
{
	bool deleted = false;
	if (nodeCount == 1)  //If theres only one node, set everything to nullptr and delete the single node. Return true
	{
		nodeCount = nodeCount - 1;
		Node* newNode = tail;
		tail = nullptr;
		head = nullptr;
		delete newNode;
		deleted = true;
		return deleted;
	}
	if (nodeCount == 0) // If theres zero, theres nothing to delete. Return false
	{
		return deleted;
	}
	else //If there is more than 1 node, it will set the current tail->prev to equal head. Return true
	{
		nodeCount = nodeCount - 1;
		Node* newNode = tail;
		tail = newNode->prev;
		tail->next = nullptr;
		delete newNode;
		deleted = true;
		return deleted;
	}
}

template <typename T>
unsigned int LinkedList<T>::Remove(const T& data) //Remove ALL nodes contained values matching that of the passed in parameter. Returns how many instances where removed
{
	Node* newNode = head;
	Node* buffer = nullptr;
	unsigned int instancesRemoved = 0;
	unsigned int i = 0;
	unsigned int tempNodeCount = nodeCount; // I need a constant copy of nodecount because nodeCount is constantly changing in the while loop. Cant do while i < nodeCount.


	for (i = 0; i < tempNodeCount; i++)
	{
		buffer = newNode->next; // Need to use the buffer variable because I cant use next-> when the newNode variable is deleted. I need a place holder

		if (newNode->data == data)
		{
			if (i == tempNodeCount) //if it's the tail
			{
				tail = newNode->prev;
				tail->next = nullptr;
				delete newNode;
				nodeCount = nodeCount - 1;
				instancesRemoved++;
			}
			if (i == 0) //if it's the head
			{
				head = newNode->next;
				head->prev = nullptr;
				delete newNode;
				nodeCount = nodeCount - 1;
				instancesRemoved++;
			}
			else if (i != 0 && i != tempNodeCount) //If it's not at index 0 or nodecount, then it is in the middle
			{
				newNode->prev->next = newNode->next;
				newNode->next->prev = newNode->prev;
				nodeCount = nodeCount - 1;
				delete newNode;
				instancesRemoved++;
			}

		}
		//i++;
		newNode = buffer;
		//newNode = newNode->next;
	}
	return instancesRemoved;
}

template <typename T>
bool LinkedList<T>::RemoveAt(unsigned int index) //Deletes the index-th node from the list, returning whether or not operation was successful
{
	// MAY NEED TO INCORPORATE IF THERE IS A NODE LIST OF SIZE 1. MAYBE CALL REMOVETAIL AND REMOVE HEAD INSTEAD? 
	bool deleted = false;

	if (nodeCount == 0 || index > nodeCount) //If there is no nodes to delete, just return false. 
	{
		return deleted;
	}
	unsigned int maximum = index;
	Node* newNode = head;
	unsigned int tempNodeCount = nodeCount;

	for (unsigned int i = 0; i < maximum; i++) //Iterates the newNode to point at the passed in index-th node
	{
		newNode = newNode->next;
	}
	if (index == tempNodeCount) //If the index to delete is the tail
	{
		tail = newNode->prev;
		tail->next = nullptr;
		nodeCount = nodeCount - 1;
		delete newNode;
		deleted = true;
		return deleted;
	}
	if (index == 0) // If the index to delete is the head
	{
		head = newNode->next;
		head->prev = nullptr;
		nodeCount = nodeCount - 1;
		delete newNode;
		deleted = true;
		return deleted;
	}
	else if (index > 0 && index < tempNodeCount) //If the index doesn't head or tail, its in the middle
	{
		newNode->prev->next = newNode->next;
		newNode->next->prev = newNode->prev;
		nodeCount = nodeCount - 1;
		delete newNode;
		return deleted;
	}
	else
	{
		cout << "Bruh!" << endl;
		return deleted;
	}
}

template <typename T>
void LinkedList<T>::Clear() //Deletes all Nodes
{
	Node* deleteNode = head;
	while (deleteNode != nullptr)
	{
		Node* deleteNodeNext = deleteNode->next;
		delete deleteNode;
		deleteNode = deleteNodeNext;
	}
	nodeCount = 0;
	head = nullptr;
	tail = nullptr;

}

/*==== Operators ====*/
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs) //copy assignment operator
{
	// May need nodeCount = 0? 
	this->~LinkedList();
	this->nodeCount = rhs.nodeCount;
	nodeCount = 0; // The AddHead function adds 1 to nodeCount every node, the nodeCount should start at 0. 
	int counterCon = rhs.nodeCount - 1; // May be list.nodeCount? 
	while (counterCon >= 0) //May not be >= 0? how do I get it to execute at 0 and nothing less
	{
		AddHead(rhs.GetNode(counterCon)->data);
		counterCon = counterCon - 1;
	}
	return *this;
}

template <typename T>
T& LinkedList<T>::operator[](unsigned int index) //Takes an index, and returns data from the index-th node. Throw outofrange
{
	if (index > nodeCount)
	{
		throw out_of_range("Out of range");
	}
	else
	{
		unsigned int maximum = index;
		Node* indexNode = head;
		for (unsigned int i = 0; i < maximum; i++)
		{
			indexNode = indexNode->next;
		}
		return indexNode->data;
	}
}

template <typename T>
const T& LinkedList<T>::operator[](unsigned int index) const
{

	if (index > nodeCount)
	{
		throw out_of_range("Out of range");
	}
	else
	{
		unsigned int maximum = index;
		Node* indexNode = head;
		for (unsigned int i = 0; i < maximum; i++)
		{
			indexNode = indexNode->next;
		}
		return indexNode->data;
	}
}

template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const //overloaded equality operator. Does listA = listB?
{
	Node* findNode = head;
	unsigned int matchCount = 0;
	if (nodeCount != rhs.nodeCount)
	{
		return false;
	}
	else
	{
		for (unsigned int i = 0; i < nodeCount; i++)
		{
			if (findNode->data == rhs.GetNode(i)->data)
			{
				matchCount = matchCount + 1;
			}
			findNode = findNode->next;
		}
		if (matchCount == nodeCount)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

/*==== Accessors ====*/

template <typename T>
unsigned int LinkedList<T>::NodeCount() const //How many things are stored in this list?
{
	return nodeCount;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head() //Return the head pointer
{
	return head;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const //Return the head pointer in const version
{
	return head;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail() //Return the tail pointer
{
	return tail;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const //Return the tail pointer in const version
{
	return tail;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) //Given an index, return a pointer at that index. Throw exception out_of_range if it is. 
{
	if (index >= nodeCount)
	{
		throw out_of_range("Index out of range!");
	}
	unsigned int maximum = index;
	Node* indexNode = head;

	for (int i = 0; i < maximum; i++) //MAY HAVE TO BE MAXIMUM - 1!? I STILL DONT UNDERSTAND THE -1 STUFF SMFH
	{
		indexNode = indexNode->next;
	}
	return indexNode;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const //Given an index, return a pointer at that index in const. Throw exception out_of_range if so.
{
	if (index >= nodeCount)
	{
		throw std::out_of_range("Index Out Of Range!");
	}
	unsigned int maximum = index;
	Node* indexNode = head;

	for (unsigned int i = 0; i < maximum; i++) //MAY HAVE TO BE MAXIMUM - 1!? I STILL DONT UNDERSTAND THE -1 STUFF SMFH
	{
		indexNode = indexNode->next;
	}
	return indexNode;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) //Find the first node with a data value matching the passed in parameter, returning the pointer. Return nullptr if none found
{
	Node* findNode = head;
	unsigned int whileCount = 0;
	bool match = false; //Only turns true if there is a match in the for loop
	while (match != true && whileCount != nodeCount) //ONCE AGAIN, MAY NEED TO BE NODECOUNT - 1? Iterates through the linked list
	{
		if (findNode->data == data) //If there is a match, return the pointer that it matches, and set the boolean to be true.
		{
			match = true;

		}
		whileCount = whileCount + 1;
		findNode = findNode->next; //Move findNode onto the next node
	}

	if (match == false) //If there is never a match, the boolean stays false. If there is no match, this will return nullptr.
	{
		return nullptr;
	}
	else
	{
		findNode = findNode->prev;
		return findNode;
	}
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) const //Const version of //Find the first node with a data value matching the passed in parameter, returning the pointer. Return nullptr if none found
{
	Node* findNode = head;
	unsigned int whileCount = 0;
	bool match = false; //Only turns true if there is a match in the for loop
	while (match != true && whileCount != nodeCount) //ONCE AGAIN, MAY NEED TO BE NODECOUNT - 1? Iterates through the linked list
	{
		if (findNode->data == data) //If there is a match, return the pointer that it matches, and set the boolean to be true.
		{
			match = true;

		}
		whileCount = whileCount + 1;
		findNode = findNode->next; //Move findNode onto the next node
	}

	if (match == false) //If there is never a match, the boolean stays false. If there is no match, this will return nullptr.
	{
		return nullptr;
	}
	else
	{
		findNode = findNode->prev;
		return findNode;
	}


}

template <typename T>
void LinkedList<T>::FindAll(vector<Node*>& outData, const T& value) const //Find all nodes who match the parameter value, store a pointer to that node in the passed in vector
{
	Node* findAllNode = head;
	for (unsigned int i = 0; i < nodeCount; i++)
	{
		if (findAllNode->data == value)
		{
			outData.push_back(findAllNode);
		}
		findAllNode = findAllNode->next;
	}
}


/*==== Behaviors ====*/

template <typename T>
void LinkedList<T>::PrintForward() const //Iterate through all the nodes and print
{
	Node* printNode = head; // Make a new node pointer and set it equal to the head
	while (printNode != nullptr) //While the following node's next pointer does not equal nullptr
	{
		cout << printNode->data << endl; // Print out the data of that node
		printNode = printNode->next; //Reassign the new Node pointer to the following node

	}

}

template <typename T>
void LinkedList<T>::PrintReverse() const //Iterate trough all the nodes in reverse
{
	Node* printNode = tail; // Make a new node pointer and set it equal to the tail
	while (printNode != nullptr) //While the following node's prev pointer does not equal nullptr
	{
		cout << printNode->data << endl; // Print out the data of that node
		printNode = printNode->prev; //Reassign the new Node pointe rto the prev node a
	}
}

template <typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* node) const //takes in a pointer node (Starting node), and then from there recursively visit each node that follows and print their values
{
	//Node* newNode = head;

	if (node != nullptr)
	{
		cout << node->data << endl;
		PrintForwardRecursive(node->next);
	}
	else
	{
		return;
	}
}

template <typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* node) const //takes in a pointer node, and then from the recursively visit each node before it and print their values. 
{
	if (node != nullptr)
	{
		cout << node->data << endl;
		PrintReverseRecursive(node->prev);
	}
	else
	{
		return;
	}
}