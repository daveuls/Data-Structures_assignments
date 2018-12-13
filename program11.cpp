//         Course: CS3420 Data Structures
//           Name: Ulikowski, David
//     Assignment: Programming 11.1
//  Date assigned: 4/11/18
//		 Date due: 4/25/18
// Date handed in: 
//         Remark: 

#include <iostream>
#include <iterator>

using namespace std;

class linked
{
private:

	struct node	// can use class if members are public.
	{
		node();
		// default constructor
		// Postcondition: item and next are initialized to nullptr (or NULL) and 0.
		int item;
		node* next;
	};

	node *head;
	node *tail;
	int length;

public:

	class Iterator
	{
	public:
		Iterator();
		// Postcondition: data member nptr is initialized to nullptr or NULL

		Iterator(node* ptr);
		// Postcondition: value in ptr is assigned to data member nptr

		Iterator operator++();
		// Prefix version unary increment operator
		// Postcondition: iterator points to the next object in the list

		T& operator*();	// dereference operator
		// dereference operator
		// Postcondition: returns the node object pointed to by the iterator

		bool operator!=(Iterator& itr2);


	private:
		node* nptr;	// data member of the Iterator class
	};

	// *** linked class member functions ***
	linked();
	// Postcondition: creates an empty list; i.e., head = nullptr; length = 0

	int getSize() const;
	// Postcondition: returns length or size of the list

	Iterator begin();
	// Postcondition: returns an iterator pointing to the first node of the list

	Iterator end();
	// Postcondition: returns an iterator pointing to the object just passed the last 

	node* getHdptr();
	// Postcondition: returns the head pointer

	void push_front(const T&newItem);
	// Postcondition: a new node is pushed to the front with its item set to newItem

	void displayListV1();
	// Version 1: Use pointers and iterator
	// Postcondition: contents of the list (all nodes) are displayed

	void displayListV2();
	// Version 1: Use iterator, the begin() and end() member functions
	// Postcondition: contents of the list (all nodes) are displayed

	void displayListv3();
	// Version 3: Use a counter
	// Postcondition: contents of the list (all nodes) are displayed
};

void displayListv1()
{
	node* curr = head;
	cout << "\nUsing node* nptr to loop:" << endl;
	while (curr != tail)
	{
		cout << "  " << curr->item;
		curr = curr->next;
	}
	cout << endl;
}

void displayListv2()
{
	cout << "\nUsing Iterator to loop:" << endl;
	linked<int>::Iterator itr = this->begin(), sentinel = this->end();

	while (itr != sentinel)
	{
		cout << "  " << *itr;
		++itr;
	}
	cout << endl;
}


void displayListv3()
{
	cout << "\nUsing counter to loop:" << endl;
	linked<int>::Iterator itr = this->begin();
	int count = 0;
	while (count < length)
	{
		cout << "  " << *itr;
		++itr;
		++count;
	}
}
};
