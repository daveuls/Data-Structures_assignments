//         Course: CS3420 Data Structures
//           Name: Ulikowski, David
//     Assignment: Programming 10.1
//  Date assigned: 3/28/18
//		 Date due: 4/5/18
// Date handed in: 4/12/18
//         Remark: Program that builds a linked list

#include <iostream>

using namespace std;

// external display() function
//template <class T>
//void display(Node<T> *hdptr);

// Node<T> class interface
template<class T>
class Node
{
private:
	T        item; // A data item
	Node<T>* next; // Pointer to next node
public:
	Node();
	Node(const T& anItem);
	Node(const T& anItem, Node<T>* nextNodePtr);
	void setItem(const T& anItem);
	void setNext(Node<T>* nextNodePtr);
	T getItem() const;
	Node<T>* getNext() const;
};

// Node<T> class implementation 
// default constructor
template<class T>
Node<T>::Node() : next(nullptr)
{}

// 2nd constructor
template<class T>
Node<T>::Node(const T& anItem) : item(anItem), next(nullptr)
{}

// 3rd constructor
template<class T>
Node<T>::Node(const T& anItem, Node<T>* nextNodePtr) : item(anItem), next(nextNodePtr)
{}

// setItem() function
template<class T>
void Node<T>::setItem(const T& anItem)
{
	item = anItem;
}

// setNext() funciton
template<class T>
void Node<T>::setNext(Node<T>* nextNodePtr)
{
	next = nextNodePtr;
}

// getItem() function
template<class T>
T Node<T>::getItem() const
{
	return item;
}

// getNext() function
template<class T>
Node<T>* Node<T>::getNext() const
{
	return next;
}

// insertFront() function
template<class T>
bool insertFront(T& hdptr)
{
	// Precondition: 
	// Postcondition: Node is inserted at front of linked list
	Node<int> *newNodePtr = new Node<int>(10, hdptr);
	hdptr = newNodePtr;

	return hdptr;
}

// insertBack() function
template<class T>
bool insertBack(T& hdptr)
{
	// Precondition:
	// Postcondition: node is inserted at end of the list
	Node<int> *curr;

	Node<int> *newNodePtr = new Node<int>(60, nullptr);
	curr = hdptr;
	while (curr->getNext() != nullptr)
	{
	curr = curr->getNext();
	}
	curr->setNext(newNodePtr);

	return hdptr;
}

// insertInterior() function
template<class T>
bool insertInterior(T& hdptr, T& tmptr)
{
	// Precondition:
	// Postcondition: Node is inserted at a given point in the list
	Node<int> *curr;

	Node<int> *newNodePtr = new Node<int>(25, tmptr);
	curr = hdptr;
	while (curr->getItem() != 20)
	{
		curr = curr->getNext();
	}
	curr->setNext(newNodePtr);

	return hdptr;
}


// removeFront() function
template<class T>
bool removeFront(T& hdptr, T& tmptr)
{
	tmptr = hdptr->getNext();
	delete hdptr;
	hdptr = tmptr;

	return hdptr;
}

// removeBack() function
template<class T>
bool removeBack(T& hdptr)
{
	Node<int> *curr = hdptr, *prev;
	prev = curr;
	while (curr->getNext() != nullptr)
	{
		prev = curr;
		curr = curr->getNext();
	}
	prev->setNext(nullptr);
	delete curr;

	return hdptr;
}

// removeInterior() function
template<class T>
bool removeInterior(T& hdptr, T& tmptr)
{
	Node<int> *curr = hdptr;
	while (curr->getItem() != 25)
	{
		tmptr = curr;
		curr = curr->getNext();
	}
	tmptr->setNext(curr->getNext());
	delete curr;

	return hdptr;
}

// clear() function
template<class T>
bool clear(T& hdptr)
{
	Node<int>* deletePtr = hdptr;
	while (hdptr != nullptr)
	{
		hdptr = hdptr->getNext();

		// return node to system
		deletePtr->setNext(nullptr);
		delete deletePtr;
	}
	// hdptr and deletePtr are nullptr
	return hdptr;
}

// external display() function
template<class T>
void display(Node<T> *hdptr)
{ 
	int i = 1;

	Node<T>* curr = hdptr;
	while (curr != nullptr)
	{
		cout << "Node #" << i << ": Item = " << curr->getItem() << ": Next = " << curr->getNext() << endl;
		curr = curr->getNext();
		i++;
	}
}

int main()
{
	Node<int> *hdptr, *tmptr, *curr, *prev;
	tmptr = new Node<int>(50, nullptr);
	tmptr = new Node<int>(40, tmptr);
	tmptr = new Node<int>(30, tmptr);
	hdptr = new Node<int>(20, tmptr);
	
	cout << "The initial 4-node list contains:" << endl;
	cout << "\nHead pointer = " << int(hdptr) << endl << endl;
	display(hdptr);

	cout << "\nAfter sending a node to the front end, the list contains:" << endl;
	/*Node<int> *newNodePtr = new Node<int>(10, hdptr);
	hdptr = newNodePtr;
	display(hdptr); */
	insertFront(hdptr);
	display(hdptr);

	cout << "\nAfter inserting 25 before 30, the list contains:" << endl;
	//newNodePtr = new Node<int>(25, tmptr);
	/*curr = hdptr;
	while (curr->getItem() != 20)
	{
		curr = curr->getNext();
	}
	curr->setNext(newNodePtr);
	display(hdptr);*/	
	insertInterior(hdptr, tmptr);
	display(hdptr);

	cout << "\nAfter attaching new node 60 to the end, the list contains:" << endl;
	//newNodePtr = new Node<int>(60, nullptr);
	//curr = hdptr;
	/*while (curr->getNext() != nullptr)
	{
		curr = curr->getNext();
	}
	curr->setNext(newNodePtr);
	display(hdptr);*/
	insertBack(hdptr);
	display(hdptr);

	cout << "\nAfter removing the front node, the list contains:" << endl;
	/* tmptr = hdptr->getNext();
	delete hdptr;
	hdptr = tmptr;*/
	removeFront(hdptr, tmptr);
	display(hdptr); 

	cout << "\nAfter removing the last node, the list contains:" << endl;
	/* curr = hdptr;
	prev = curr;
	while (curr->getNext() != nullptr)
	{
		prev = curr;
		curr = curr->getNext();
	}
	prev->setNext(nullptr);
	delete curr;*/
	removeBack(hdptr);
	display(hdptr);


	cout << "\nAfter deleting node with value of 25, the list contains:" << endl;
	/*curr = hdptr;
	while (curr->getItem() != 25)
	{
		tmptr = curr;
		curr = curr->getNext();
	}
	tmptr->setNext(curr->getNext());
	delete curr;*/
	removeInterior(hdptr, tmptr);
	display(hdptr);

	cout << "\nAfter clearing list:" << endl;
	clear(hdptr);
	display(hdptr);

	return 0;
}