// This program will have multiple sorting algorithms
// Each will show how different types of sorting are performed
// Each algorithm can be modified to use vectors

#include <iostream>
#include <string>
//#include <vector>

using namespace std;

// selection sort

typedef string ItemType;	// more flexible to change data type without using template

int findIndexOfLargest(const ItemType theArray[], int size);
// ** finds the largest item in the array
// Precondition: The size of the array is >= 1 and is loaded with size(number of elements) values
// Postcondition: returns the subscript (or index) value of the largest element stored in the array

void selectionSort(ItemType theArray[], int n);
// sorts the items in an array in ascending order
//Precondition: none
//Postcondition: The n elements stored in the array is sorted in ascending order

void selectionSort(ItemType theArray[], int n)
{
	// last: index of the last item in the subarray of items yet to be sorted
	// largest: index of the largest item found
	for (int last = n - 1; last >= 1; last--)
	{
		//select the largest entry in theArray[0...last]
		int largest = findIndexOfLargest(theArray, last + 1);

		// swap the largest entry, theArray[largest] with theArray[last]
		swap(theArray[largest], theArray[last]);
	}
}

int findIndexOfLargest(const ItemType theArray[], int size)
{
	int indexSoFar = 0;
	for (int currentIndex = 1; currentIndex < size; currentIndex++)
	{
		if (theArray[currentIndex] > theArray[indexSoFar])
			indexSoFar = currentIndex;
	}
	return indexSoFar;
}

int main()
{
	string a[6] = { "Z", "F", "R", "K", "X", "B" };

	selectionSort(a, 6);
	
	for (int i = 0; i < 6; i++)
	{
		cout << a[i] << " ";
	}

	cout << endl;

	return 0;
}