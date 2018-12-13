// this program shows how to create nodes and implement singly-linked
// and doubly-linked lists

#include <iostream>

using namespace std;

template<class ItemType>
class List
{
private:
	Node<ItemType>* head;
	int itemCount;
	Node<ItemType>* getPointerTo(const ItemType& target) const;
public:
	List(); // constructor
	List(const List<ItemType>& aList);	// copy constructor
	~List();	// destructor
};

// Default Constructor: declares and empty list object
template<class ItemType>
List<ItemType>::List() : head(nullptr), tail(nullptr), itemCount(0)
{}

// Copy Constructor: declares a list object whose contents are the same as aList
template<class ItemType>
List<ItemType>::list(const list<ItemType>& aList)
{
	itemCount = aList.itemCount();
	Node<ItemType>* origChainPtr = aList.head;	// points to nodes in original chain
	if (origChainPtr == nullPtr)
	{
		head = nullptr;
	}
	else
	{
		// copy first node
		head = new Node<ItemType>();
		head->setItem(origChainPtr->getItem());

		//copy remaining nodes
		Node<ItemType>* newChainPtr = head;	// points to last node in new chain
		origChainPtr = origChainPtr->getNext();	// advance original chain pointer

		while (origChainPtr != nullptr)
		{
			// get item from original chain
			ItemType nextItem = origChainPtr->getItem();

			// create a new node containing the next item
			Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);

			// link new node to the end of the new chain
			newChainPtr->setNext(newNodePtr);

			// advance new pointer to new last node
			newChainPtr = newChainPtr->getNext();

			// advance original chain pointer
			origChainPtr = origChainPtr->getNext();
		} // end while loop

		newChainPtr->setNext(nullptr);	// end flag of chain
	}	// end if
}


