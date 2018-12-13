//         Course: CS3420 Data Structures
//           Name: Ulikowski, David
//     Assignment: Programming 7
//  Date assigned: 3/7/18
//		 Date due: 3/20/18
// Date handed in: 3/27/18
//         Remark: Program showing execution time of sort algorithms

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

const int MIN_SIZE = 10; // Size of an array that quicksort will sort
const int MAX_SIZE = 500000;

template<class T>
void bubbleSort(vector<T>& vobj, T n)
// Sorts the n elements stored in an array into ascending order.
// Postcondition: n elements in vobj is sorted into ascending order
{
	bool sorted = false; // False when swaps occur
	int pass = 1;

	while (!sorted && (pass < n))
	{
		sorted = true; // Assume sorted
		for (int index = 0; index < n - pass; index++)
		{
			int nextIndex = index + 1;
			if (vobj[index] > vobj[nextIndex])
			{
				swap(vobj[index], vobj[nextIndex]);
				sorted = false; // Signal exchange, implying the array is not yet sorted
			}
		}
		pass++;
	}
}

template<class T>
void merge(vector<T>& vobj, T first, T mid, T last)
// Merges two sorted array segments vobj[first..mid] and vobj[mid+1..last] into one sorted array.
//  precondition:  first = mid = last. The subarrays vobj[first..mid] and vobj[mid+1..last] 
//		are each sorted in increasing order.
//  postcondition:  vobj[first..last] is sorted in ascending order.
//  first:  The index of the beginning of the first segment in vobj.
//  mid:  The index of the end of the first segment in vobj; mid + 1 marks the beginning of the second segment.
// last:  The index of the last element in the second segment in vobj.
// Note that this function merges the two subarrays into a temporary array and copies the result into the original array vobj.
{
	T tempVec[MAX_SIZE];  // Temporary array

	// Initialize the local indices to indicate the subarrays
	int first1 = first;            // Beginning of first subarray
	int last1 = mid;               // End of first subarray
	int first2 = mid + 1;          // Beginning of second subarray
	int last2 = last;              // End of second subarray

	// While both subarrays are not empty, copy the smaller item into the temporary array
	int index = first1;            // Next available location in tempArray
	while ((first1 <= last1) && (first2 <= last2))
	{
		// At this point, tempArray[first..index-1] is in order
		if (vobj[first1] <= vobj[first2])
		{
			tempVec[index] = vobj[first1];
			first1++;
		}
		else
		{
			tempVec[index] = vobj[first2];
			first2++;
		}
		index++;
	}

	// Finish off the first subarray, if necessary
	while (first1 <= last1)
	{
		// At this point, tempArray[first..index-1] is in order
		tempVec[index] = vobj[first1];
		first1++;
		index++;
	}
	// Finish off the second subarray, if necessary
	while (first2 <= last2)
	{
		// At this point, tempArray[first..index-1] is in order
		tempVec[index] = vobj[first2];
		first2++;
		index++;
	}

	// Copy the result back into the original array
	for (index = first; index <= last; index++)
		vobj[index] = tempVec[index];
}

template<class T>
void mergeSort(vector<T>& vobj, T first, T last)
// Sorts the items in an array into ascending order.
// postcondition:  vobj[first..last] is sorted in ascending order.
// first: the index of the first element to consider in vobj;  last:  The index of the last element to consider in vobj. 
{
	if (first < last)
	{
		// Sort each half
		int mid = first + (last - first) / 2; // Index of midpoint
		//int mid = vobj.begin() + (vobj.end() - vobj.begin()) / 2;

		// Sort left half vobj[first..mid]
		mergeSort(vobj, first, mid);
		//mergeSort(vobj, vobj.begin(), mid);

		// Sort right half vobj[mid+1..last]
		mergeSort(vobj, mid + 1, last);
		//mergeSort(vobj, mid + 1, vobj.end());

		// Merge the two halves
		merge(vobj, first, mid, last);
		//merge(vobj, vobj.begin(), mid, vobj.end())
	}
}

template<class T>
void insertionSort(vector<T>& vobj, T first, T last)
// Sorts the items in an array into ascending order.
// postcondition:  vobj is sorted into ascending order.
{
	// unsorted: first index of the unsorted region,
	// loc: index of insertion in the sorted region,
	// nextItem: next item in the unsorted region.
	// Initially, sorted region is vobj[0], unsorted region is vobj[1..n-1].
	// In general, sorted region is vobj[0..unsorted-1], unsorted region vobj[unsorted..n-1]

	for (int unsorted = first + 1; unsorted <= last; unsorted++)
	{
		// At this point, vobj[first..unsorted-1] is sorted.
		// Find the right position (loc) in vobj[first..unsorted] for vobj[unsorted], which is the first entry in the
		// 	unsorted region; shift, if necessary, to make room
		T nextItem = vobj[unsorted];
		int loc = unsorted;
		while ((loc > first) && (vobj[loc - 1] > nextItem))
		{
			// Shift vobj[loc - 1] to the right
			vobj[loc] = vobj[loc - 1];
			loc--;
		}

		// At this point, vobj[loc] is where nextItem belongs
		vobj[loc] = nextItem; // Insert nextItem into sorted region
	}
}

// Arranges two specified array entries into sorted order by exchanging them, if necessary.
//  i: The index of the first entry to consider in vobj. j:  The index of the second entry to consider in vobj. 
template<class T>
void order(vector<T>& vobj, T i, T j)
{
	if (vobj[i] > vobj[j])
		swap(vobj[i], vobj[j]);
}

// Arranges the first, middle, and last entry in an array in sorted order.
//  Precondition:  vobj[first..last] is an array; first <= last.
// Postcondition:  vobj[first..last] is arranged so that its first, middle, and last entries are in sorted order.
//			       returnS  The index of the middle entry.
// first  The first entry to consider in vobj.
// last:  The last entry to consider in vobj.

template<class T>
int sortFirstMiddleLast(vector<T>& vobj, T first, T last)
{
	int mid = first + (last - first) / 2;
	order(vobj, first, mid); // Make vobj[first] <= vobj[mid]
	order(vobj, mid, last);  // Make vobj[mid] <= vobj[last]
	order(vobj, first, mid); // Make vobj[first] <= vobj[mid]

	return mid;
}

// Partitions the entries in a vector about a pivot entry for quicksort.
//  precondition:  vobj[first..last] is a vector; first <= last.
// postcondition:  vobj[first..last] is partitioned such that:
//S1 = vobj[first..pivotIndex - 1] <= pivot
//vobj[pivotIndex] == pivot
//S2 = vobj[pivotIndex + 1..last] >= pivot
//			The function returns  the index of the pivot. 
template<class T>
int partition(vector<T>& vobj, T first, T last)
{
	// Choose pivot using median-of-three selection
	int pivotIndex = sortFirstMiddleLast(vobj, first, last);

	// Reposition pivot so it is last in the array
	swap(vobj[pivotIndex], vobj[last - 1]);
	pivotIndex = last - 1;
	T pivot = vobj[pivotIndex];

	// Determine the regions S1 and S2
	int indexFromLeft = first + 1;
	int indexFromRight = last - 2;

	bool done = false;
	while (!done)
	{
		// Locate first entry on left that is >= pivot
		while (vobj[indexFromLeft] < pivot)
			indexFromLeft = indexFromLeft + 1;

		// Locate first entry on right that is <= pivot
		while (vobj[indexFromRight] > pivot)
			indexFromRight = indexFromRight - 1;

		if (indexFromLeft < indexFromRight)
		{
			swap(vobj[indexFromLeft], vobj[indexFromRight]);
			indexFromLeft = indexFromLeft + 1;
			indexFromRight = indexFromRight - 1;
		}
		else
			done = true;
	}

	// Place pivot in proper position between S1 and S2, and mark its new location
	swap(vobj[pivotIndex], vobj[indexFromLeft]);
	pivotIndex = indexFromLeft;

	return pivotIndex;
}

// Sorts a vector into ascending order. Uses the quick sort with median-of-three pivot selection 
//	for vectors of at least MIN_SIZE entries, and uses the insertion sort for other vectors.
//  Precondition:  vobj[first..last] is loaded from first to last.
// Postcondition:  vobj[first..last] is sorted.
template<class T>
void quickSort(vector<T>& vobj, T first, T last)
{
	if (last - first + 1 < MIN_SIZE)
	{
		insertionSort(vobj, first, last);
	}
	else
	{
		// Create the partition: S1 | Pivot | S2
		int pivotIndex = partition(vobj, first, last);

		// Sort subarrays S1 and S2
		quickSort(vobj, first, pivotIndex - 1);
		quickSort(vobj, pivotIndex + 1, last);
	}
}

template<class T>
void selectionSort(vector<T>& vobj, T n)
// ** Finds the largest item in an array.
// Precondition:  The size of the array is >= 1 and the array is loaded with size (number of elements) values
// Postcondition:  returns the subscript (or index) value of the largest element stored in the array.
{
	// last: index of the last item in the subarray of items yet to be sorted;
	// largest: index of the largest item found
	for (int last = n - 1; last >= 1; last--)
	{
		// Select the largest entry in vobj[0..last]
		int largest = findIndexOfLargest(vobj, last + 1);

		// Swap the largest entry, vobj[largest], with vobj[last]
		swap(vobj[largest], vobj[last]);
	}
}

template<class T>
int findIndexOfLargest(const vector<T>& vobj, T size)
{
	int indexSoFar = 0;
	for (int currentIndex = 1; currentIndex < size; currentIndex++)
	{
		if (vobj[currentIndex] > vobj[indexSoFar])
			indexSoFar = currentIndex;
	}
	return indexSoFar;
}

template<class T>
void fillVector(vector<T> &vobj, T numOfElements)
{
	for (int i = 0; i < numOfElements; i++)
	{
		int num = rand() % 100;
		vobj.push_back(i);
		vobj[i] = num;
	}
	cout << endl << endl;
}

template<class T>
void displayVector(vector<T> &vobj, T numOfElements)
{
	for (int i = 0; i < numOfElements; i++)
	{
		cout << vobj[i] << " ";
	}
	cout << endl << endl;
}

int main()
{
	vector<int> vobj;
	int elements;

	cout << "Enter number of random positive integers to be stored then sorted in the vector: ";
	cin >> elements;
	vobj.resize(elements);

	fillVector(vobj, elements);

	if (elements <= 10)
	{
		cout << "Before sorting, the first " << elements << " values in the vector are:" << endl;
		displayVector(vobj, elements);


		/*cout << "Amount of time taken to Bubble Sort " << elements << " elements in vector:" << endl;
		clock_t startb = clock();
		bubbleSort(vobj, elements);
		clock_t endb = clock();
		cout << "time: " << ((endb - startb) / 1000) << " seconds" << endl;
		cout << "Sorted vector elements" << endl;
		displayVector(vobj, elements);

		cout << "Amount of time taken to Insertion Sort " << elements << " elements in vector:" << endl;
		clock_t starti = clock();
		insertionSort(vobj, 0, elements - 1);
		clock_t endi = clock();
		cout << "time: " << ((endi - starti) / 1000) << " seconds" << endl;
		cout << "Sorted vector elements" << endl;
		displayVector(vobj, elements);*/

		cout << "Amount of time taken to Merge Sort " << elements << " elements in vector:" << endl;
		clock_t startm = clock();
		mergeSort(vobj, 0, elements - 1);
		clock_t endm = clock();
		cout << "time: " << ((endm - startm) / 1000) << " seconds" << endl;
		cout << "Sorted vector elements" << endl;
		displayVector(vobj, elements);

		/*cout << "Amount of time taken to Quick Sort " << elements << " elements in vector:" << endl;
		clock_t startq = clock();
		quickSort(vobj, 0, elements - 1);
		clock_t endq = clock();
		cout << "time: " << ((endq - startq) / 1000) << " seconds" << endl;
		cout << "Sorted vector elements" << endl;
		displayVector(vobj, elements);*/
	}

	else
	{
		/*cout << "Amount of time taken to Bubble Sort " << elements << " elements in vector:" << endl;
		clock_t startb = clock();
		bubbleSort(vobj, elements);
		clock_t endb = clock();
		cout << "time: " << ((endb - startb) / 1000) << " seconds" << endl << endl;

		cout << "Amount of time taken to Insertion Sort " << elements << " elements in vector:" << endl;
		clock_t starti = clock();
		insertionSort(vobj, 0, elements - 1);
		clock_t endi = clock();
		cout << "time: " << ((endi - starti) / 1000) << " seconds" << endl;

		cout << "Amount of time taken to Merge Sort " << elements << " elements in vector:" << endl;
		clock_t startm = clock();
		mergeSort(vobj, 0, elements - 1);
		clock_t endm = clock();
		cout << "time: " << ((endm - startm) / 1000) << " seconds" << endl;

		cout << "Amount of time taken to Quick Sort " << elements << " elements in vector:" << endl;
		clock_t startq = clock();
		quickSort(vobj, 0, elements - 1);
		clock_t endq = clock();
		cout << "time: " << ((endq - startq) / 1000) << " seconds" << endl;*/
	}



	return 0;
}

