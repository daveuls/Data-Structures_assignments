//         Course: CS3420 Data Structures
//           Name: Ulikowski, David
//     Assignment: Programming 2.2
//  Date assigned: 1/30/18
//	  Date due:2/6/18
// Date handed in: 2/6/18
//         Remark: container class with dynamic array 

// Container with dynamic storage
#include <iostream>
#include <iomanip>
using namespace std;

class container
{
	friend ostream& operator<<(ostream& out, container &);
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

	container& operator=(const container &rhs);
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
	void allocate();
	// Postcondition: 1) the capacity of the container has been doubled, 2) existing values in the existing array have been copied to 
	//				   the new and larger dynamic array, 3) memory of the old array has been deleted (returned to "heap").

	int *data;
	int capacity;		// indicates the storage capcity of the container, i.e., the size of the dynamic array		
	int count;		// used as a subscript to index into the array; size = count + 1
};

ostream& operator<<(ostream& out, container &c)
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

container& container::operator=(const container &rhs)
{
	capacity = rhs.capacity;
	count = rhs.count;
	data = new int[capacity];

	return *this;
}

void container::insert(int value)
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

void container::remove()
{
	if (!isEmpty())
	{
		count--;
	}
	else
		cout << "The container is empty; no action is taken!" << endl;
}

int container::operator[](int sub)
{
	if (sub > capacity)
	{
		cout << "Invalid. [sub] is out of range. Program will now terminate..." << endl;
		exit(1);
	}

	return data[sub];
}

bool container::isFull()
{
	return (count == capacity - 1);
}

bool container::isEmpty()
{
	return (count == -1);
}

int container::Capacity()
{
	return capacity;
}

int container::size()
{
	return (count + 1);
}

void container::resize(int n)
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

void container::allocate()
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
	container c1;

	cout << "Before inserting any value into the c1 container" << endl;
	cout << c1;
	cout << endl;

	cout << "We now insert 11 to 99 with incremental value of 11 into the c1 container." << endl;
	for (int i = 11; i <= 99; i += 11)
		c1.insert(i);
	cout << "Container c1:" << endl;
	cout << c1;
	cout << endl;

	container c2(c1);

	cout << "Declared c2 as a copy of c1 using the copy contructor." << endl;
	cout << "Container c2:" << endl;
	cout << c2;
	cout << endl;

	container c3 = c2;

	cout << "Declared c3 as a copy of c2 with overloaded assignment operator." << endl;
	cout << "Container c3:" << endl;
	cout << c3;
	cout << endl;

	c3.resize(4);
	cout << "Resized c3 to size = 4";// << c3.Capacity();
	cout << "\nContainer c3:" << endl;
	cout << c3;
	cout << endl;

	c3.resize(7);
	cout << "Resized c3 to size = 7";// << c3.Capacity();
	cout << "\nContainer c3:" << endl;
	cout << c3;
	cout << endl;

	cout << "finally, we display the address of the three containers:" << endl;
	cout << "\tAddress of c1 = " << &c1 << endl;
	cout << "\tAddress of c2 = " << &c2 << endl;
	cout << "\tAddress of c3 = " << &c3 << endl;

	return 0;
}
