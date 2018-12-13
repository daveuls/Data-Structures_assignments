//         Course: CS3420 Data Structures
//           Name: Ulikowski, David
//     Assignment: Programming 4
//  Date assigned: 2/16/18
//	  Date due:2/22/18
// Date handed in: 2/6/18
//         Remark: Template container class with dynamic array 

// Container with dynamic storage
#include <iostream>
#include <iomanip>
using namespace std;

template <class T>
class container
{
	template <class T>

	friend ostream& operator<<(ostream& out, const container<T> &);
	// Postcondition: displays # of values stored in the container, storage capacity of the contianer, and stored values in the container 
	//                in the following format: Array size = 3, capacity = 4, contents = 11, 22, 33 (see below sample program output

public:
	container();
	// Postcondition: set dynamic storage capacity to 1 and count to -1 where (count + 1) represents the actual values stored 
	//                 in the container. Notice that data member count is used as the subscript to access elements (actual values) stored 
	//                 in the dynamic array; thus (count + 1) represents the total # of values that are currently stored in the array

	container(int n);
	// Postcondition: set dynamic storage (data array) capacity to n and count to -1

	container(container &);
	// Programmer-supplied copy constructor is necessary to avoid memory leak and other side effect
	// Postcondition: a new container class object is created which is the same as the one passed to the function

	~container();
	// Programmer-supplied destructor is necessary to avoid memory leak
	// Postcondition: all dynamic memory locations have been returned back to the heap whenever a container object goes out of scope

	container& operator=(const container<T> &rhs);
	// Programmer-supplied overloaded assignment is necessary to avoid memory leak and other side effect
	// Postconditoin: the container object rhs is assigned to the calling object

	void insert(int);
	// Postcondition: if the container is not full, the value passed to the function is stored in  
	//			the first available element of the dynamic array. Otherwise the function calls the private 
	//         	       "allocate" member function requesting a new set of dynamic memory with twice the previous storage capacity 
	//			the insert function then increments count by 1 and insert the value into the new and larger array.

	void remove();
	//  Precondition: the data array must not be empty; i.e., count must be greater than or equal to 0.
	// Postcondition: if the container is not empty, then remove the most recently stored value ifrom the container and 
	//			decrement count by 1; otherwise, display the message "The container is empty; no action is taken!"

	int operator[](int sub);
	//  Precondition: value passed to the function must be a positive integer including 0
	// Postcondition: the value of stored in data[sub] is returned; if sub is out of range, display a message and terminate the program .

	bool isFull();
	// Postcondition: return true if the container is full; return false otherwise 

	bool isEmpty();
	// Postcondition: return true if the container is empty; return false otherwise

	int Capacity();
	// Notice uppercase 'C' to avoid conflict with data member named "capacity"
	// Postcondition: returns the current storage capacity of the container

	int size();
	// Postcondition: returns the # of elements (# of objects) currently stored in the container

	void resize(int n);
	// Postcondition: container (i.e., the dynamic array) is resized to n; contents of existing container have been copied to the new array; 
	// 			      old array is deleted to avoid memory leak.

private:
	T allocate();
	// Postcondition: 1) the capacity of the container has been doubled, 2) existing values in the existing array have been copied to 
	//				   the new and larger dynamic array, 3) memory of the old array has been deleted (returned to "heap").

	T *data;
	T capacity;		// indicates the storage capcity of the container, i.e., the size of the dynamic array		
	T count;		// used as a subscript to index into the array; size = count + 1
};
template <class T>
ostream& operator<<(ostream& out, const container<T> &c)
{
	out << "Container capacity = " << c.Capacity();
	out << "\tSize or actual # of values stored in container = " << c.size() << endl;
	out << "Contents of the container = ";
	if (c.size() == 0)
		cout << "container is empty";
	else
	{
		for (int i = 0; i < c.size(); i++)
		{
			out << c[i] << " ";
		}
	}
	out << endl << endl;

	return out;
}

container::container()
{
	capacity = 1;
	count = -1;
	data = new int[capacity];
}

container::container(int n)
{
	capacity = n;
	count = -1;
	data = new int[capacity];
}

container::container(container &ctainer)
{
	capacity = ctainer.capacity;
	count = ctainer.count;
	data = new int[capacity];
	for (int i = 0; i < capacity; i++)
	{
		data[i] = ctainer.data[i];
	}
}

container::~container()
{
	delete[] data;
}

container& container::operator=(const container<T> &rhs)
{
	capacity = rhs.capacity;
	count = rhs.count;
	data = new int[capacity];

	return *this;
}
template <class T>
void container<T>::insert(int value)
{
	bool fullArray = false;

	while (!fullArray)
	{
		if (!isFull())
		{
			data[++count] = value;
			fullArray = true;
		}
		else
			allocate();
	}
}
template <class T>
void container<T>::remove()
{
	if (!isEmpty())
	{
		count--;
	}
	else
		cout << "The container is empty; no action is taken!" << endl;
}
template <class T>
int container<T>::operator[](int sub)
{
	if (sub > capacity)
	{
		cout << "Invalid. [sub] is out of range. Program will now terminate..." << endl;
		exit(1);
	}

	return data[sub];
}
template <class T>
bool container<T>::isFull()
{
	return (count == capacity - 1);
}
template <class T>
bool container<T>::isEmpty()
{
	return (count == -1);
}
template <class T>
int container<T>::Capacity()
{
	return capacity;
}
template <class T>
int container<T>::size()
{
	return (count + 1);
}
template <class T>
void container<T>::resize(int n)
{
	count = -1;
	int prevCapacity = capacity;
	capacity = n;
	int *ptr = new int[capacity];

	if (prevCapacity > capacity)
	{
		for (int i = 0; i < capacity; i++)
		{
			ptr[i] = data[i];
			count++;
		}
	}
	else
	{
		for (int i = 0; i < prevCapacity; i++)
		{
			ptr[i] = data[i];
		}
	}
	delete[] data;
	data = new int[capacity];

	for (int i = 0; i < capacity; i++)
	{
		data[i] = ptr[i];
	}
	delete[] ptr;
}
template <class T>
T container<T>::allocate()
{
	count = -1;
	int *newptr = new int[capacity];

	for (int i = 0; i < capacity; i++)
	{
		newptr[i] = data[i];
		count++;
	}
	delete[] data;

	data = new int[capacity * 2];

	for (int i = 0; i < capacity; i++)
	{
		data[i] = newptr[i];
	}
	delete[] newptr;

	capacity *= 2;
}

int main()
{
	cout << "*************** integer container *************" << endl;

	cout << "************** character container ************" << endl;

	cout << "*************** date container *************" << endl;

	return 0;
}