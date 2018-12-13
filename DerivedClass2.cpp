//         Course: CS3420 Data Structures
//           Name: Ulikowski, David
//     Assignment: Programming 2.2
//  Date assigned: 1/19/18
//	  Date due:1/31/18
// Date handed in: 1/31/18
//         Remark: Program 2.1 with derived class of three functions 




#include <iostream>
#include <iomanip>
#include <cstdlib>	// for exit function.
#include <ctime>	// for generating random test data values
using namespace std;

// container class interface
class container
{
public:
	container();
	// Postcondition: all data array elements of the container are initialized to 0 and data member count is set to -1

	void insert(int);
	//  Precondition: container  must not be full
	// Postcondition: if the container is not full, insert the value passed to the function into the first available data array element 
	//		    	      and increment count by 1; otherwise , display "The container is full: no insertion made and program terminated!" 

	bool isEmpty();
	// Postcondition: return true if container is empty; return false otherwise

	bool isFull();
	// Postcondition: return true if container is full; return false otherwise

	void remove();
	//  Precondition: the container  must not be empty
	// Postcondition: if the container is not empty, remove the last element (most recently) stored into the data array of the container;                    //                           otherwise display "Container is empty; program terminated!"
	void undelete();
	// Postcondition: the most recently removed value is restored or undeleted

	void sort();
	//  Precondition: container contains at least two values 
	// Postcondition: all values stored in the container have been sorted in ascending order

	void display();
	// Postcondition: displays all values currently stored the container

protected:
	const static int CAPACITY = 10;		// specifies storage capacity of a container object, i.e., the size of the container
	int data[CAPACITY];			// stores inserted integer values  
	int count;					// (count + 1) represents how many values are currently stored in the container!
};								// this is because data member “count” will be used as subscript for the data array.

// Implementation of member functions
container::container()
{
	count = -1;
	for (int i = 0; i < CAPACITY; i++)
		data[i] = 0;
}

void container::insert(int value)
{
	if (!isFull())
	{
		count++;
		data[count] = value;	// count is used as subscript for “data” array elements
		cout << setw(4) << value << " has been inserted in data[" << count << "]." << endl;
	}
	else {
		cout << "Attempts to insert a value into a full container; program is terminated!";
		exit(1);
	}
}

bool container::isFull()
{
	return (count == 9);
}

bool container::isEmpty()
{
	return (count == -1);
}


void container::remove()	// logical removal!
{
	if (!isEmpty())
	{
		cout << "  data[" << count-- << "] is 'logically' removed from the container!" << endl;
	}
	else
	{
		cout << "Attempts to remove a value from an empty container; program is terminated!";
		exit(1);
	}
}

void container::undelete()
{
	if (!isFull())
	{
		count++;
	}
	else
	{
		cout << "attempted to restore a value to a full container; program is terminated!";
		exit(1);
	}
}

void container::sort()
{
	int i, j, flag = 1, temp;
	for (i = 0; (i <= CAPACITY) && flag; i++)
	{
		flag = 0;
		for (j = 0; j < (CAPACITY - 1); j++)
		{
			if (data[j + 1] < data[j])
			{
				temp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = temp;
				flag = 1;
			}
		}
	}
}

void container::display()
{
	cout << "The container contains the following " << count + 1 << " value(s):\n";
	if (count == -1)
		cout << "*** data array is empty!" << endl;
	else
	{
		for (int i = 0; i <= count; i++)
			cout << data[i] << '\t';
		cout << endl;
	}
}



class Container :public container
{
public:
	Container();
	// Postcondition: all data array elements of the container are initialized to 0 and data member count is set to -1



	int locateLargest();
	// Postcondition: returns the largest value stored in the container object

	bool linearSearch(int);
	// Value for the search key  is passed to the function. The function determines if the value exists in the container
	// Postcondition: return true if key value exists in the container; returns false otherwise.

	bool binarySearch(int);
	// Value for the search key is passed to the function. The function determines if the value exists in the container
	// Precondition: the data array has been sorted
	// Postcondition: return true if key value exists in the container; returns false otherwise.
};

Container::Container() :container()
{
}

int Container::locateLargest()
{
	int largest = data[0];

	for (int i = 0; i < CAPACITY; i++)
	{
		if (data[i] > largest)
			largest = data[i];
	}

	return (largest);
}

bool Container::linearSearch(int key)
{
	for (int i = 0; i < count; i++)
	{
		if (key == data[i])
			return true;
	}

	return false;
}

bool Container::binarySearch(int key)
{
	int lower = 0, upper = count, mid = 0;
	bool find = false;

	while (lower <= upper && !find)
	{
		mid = (lower + upper) / 2;

		if (key > data[mid])
		{
			lower = mid + 1;
		}
		else if (key < data[mid])
		{
			upper = mid - 1;
		}
		else
		{
			find = true;
		}
		return true;
	}
	return false;
}

int main()
{
	Container C;
	int keyNum;

	srand(static_cast<unsigned int>(time(0)));
	cout << "We now insert 10 random integer values into the container:\n";
	for (int i = 0; i < 10; i++)
		C.insert(rand() % 99 + 1);

	cout << "\nAfter the insertion operation:" << endl;
	C.display();

	cout << "\nWe search for the largest value stored in the container..." << endl;
	cout << "After the search operation, we found that the largest value is ";
	cout << C.locateLargest() << endl;

	cout << "\nEnter a value to be linear-searched to see if it is in the container: ";
	cin >> keyNum;
	if (C.linearSearch(keyNum))
	{
		cout << keyNum << " is in the container!" << endl;
	}
	else
		cout << keyNum << " is not in the container!" << endl;

	cout << "\nIn order to perform a binary search, the data array must be sorted!" << endl;
	cout << "We perform sort operation ... After sort operation:" << endl;
	C.sort();
	C.display();

	cout << "We are ready to perform a binary search." << endl;
	cout << "Enter a value to be binary-searched to see if it is in the container: ";
	cin >> keyNum;
	if (C.binarySearch(keyNum))
	{
		cout << keyNum << " is in the container!" << endl;
	}
	else
		cout << keyNum << " is not in the container!" << endl;

	return 0;
}


