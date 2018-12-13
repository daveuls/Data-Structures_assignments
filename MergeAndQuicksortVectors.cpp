//         Course: CS3420 Data Structures
//           Name: Ulikowski, David
//     Assignment: Programming 6.1
//  Date assigned: 3/7/18
//	  Date due:	3/20/18
// Date handed in: 3/20/18
//         Remark: Merge sort/Quick sort using vectors

#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int MAX_SIZE = 50;

template<class T>
void merge(vector<T>& vobj, T first, T mid, T last);
// Merges two sorted array segments theArray[first..mid] and theArray[mid+1..last] into one sorted array.
//  precondition:  first = mid = last. The subarrays theArray[first..mid] and theArray[mid+1..last] 
//		are each sorted in increasing order.
//  postcondition:  theArray[first..last] is sorted in ascending order.
//  first:  The index of the beginning of the first segment in theArray.
//  mid:  The index of the end of the first segment in theArray; mid + 1 marks the beginning of the second segment.
// last:  The index of the last element in the second segment in theArray.
// Note that this function merges the two subarrays into a temporary array and copies the result into the original array theArray.

template<class T>
void mergeSort(vector<T>& vobj, T first, T last);
// Sorts the items in an array into ascending order.
// postcondition:  theArray[first..last] is sorted in ascending order.
// first: the index of the first element to consider in theArray;  last:  The index of the last element to consider in theArray. 

template<class T>
void merge(vector<T>& vobj, T first, T mid, T last)
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
{
	if (first < last)
	{
		// Sort each half
		int mid = first + (last - first) / 2; // Index of midpoint
		//int mid = vobj.begin() + (vobj.end() - vobj.begin()) / 2;

		// Sort left half theArray[first..mid]
		mergeSort(vobj, first, mid);
		//mergeSort(vobj, vobj.begin(), mid);

		// Sort right half theArray[mid+1..last]
		mergeSort(vobj, mid + 1, last);
		//mergeSort(vobj, mid + 1, vobj.end());

		// Merge the two halves
		merge(vobj, first, mid, last);
		//merge(vobj, vobj.begin(), mid, vobj.end())
	}
}

static const int MIN_SIZE = 10; // Size of an array that quicksort will sort

template<class T>
void insertionSort(vector<T>& vobj, T first, T last);
// Sorts the items in an array into ascending order.
// postcondition:  theArray is sorted into ascending order.

template<class T>
void insertionSort(vector<T>& vobj, T first, T last)
{
	// unsorted: first index of the unsorted region,
	// loc: index of insertion in the sorted region,
	// nextItem: next item in the unsorted region.
	// Initially, sorted region is theArray[0], unsorted region is theArray[1..n-1].
	// In general, sorted region is theArray[0..unsorted-1], unsorted region theArray[unsorted..n-1]

	for (int unsorted = first + 1; unsorted <= last; unsorted++)
	{
		// At this point, theArray[first..unsorted-1] is sorted.
		// Find the right position (loc) in theArray[first..unsorted] for theArray[unsorted], which is the first entry in the
		// 	unsorted region; shift, if necessary, to make room
		T nextItem = vobj[unsorted];
		int loc = unsorted;
		while ((loc > first) && (vobj[loc - 1] > nextItem))
		{
			// Shift theArray[loc - 1] to the right
			vobj[loc] = vobj[loc - 1];
			loc--;
		}

		// At this point, theArray[loc] is where nextItem belongs
		vobj[loc] = nextItem; // Insert nextItem into sorted region
	}
}

// Arranges two specified array entries into sorted order by exchanging them, if necessary.
//  i: The index of the first entry to consider in theArray. j:  The index of the second entry to consider in theArray. 
template<class T>
void order(vector<T>& vobj, T i, T j)
{
	if (vobj[i] > vobj[j])
		swap(vobj[i], vobj[j]);
}

// Arranges the first, middle, and last entry in an array in sorted order.
//  Precondition:  theArray[first..last] is an array; first <= last.
// Postcondition:  theArray[first..last] is arranged so that its first, middle, and last entries are in sorted order.
//			       returnS  The index of the middle entry.
// first  The first entry to consider in theArray.
// last:  The last entry to consider in theArray.

template<class T>
int sortFirstMiddleLast(vector<T>& vobj, T first, T last)
{
	int mid = first + (last - first) / 2;
	order(vobj, first, mid); // Make theArray[first] <= theArray[mid]
	order(vobj, mid, last);  // Make theArray[mid] <= theArray[last]
	order(vobj, first, mid); // Make theArray[first] <= theArray[mid]

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
void fillVector(vector<T> &vobj)
{
	for (int i = 0; i < 10; i++)
	{
		vobj.push_back(i);
		cin >> vobj[i];
	}
	cout << endl << endl;
}

template<class T>
void displayVector(vector<T> &vobj)
{
	for (int i = 0; i < 10; i++)
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

	fillVector(vobj);

	cout << "Before sort, the first 10 values in the vector are:" << endl;
	displayVector(vobj);

	cout << "After the sort, the first 10 values in the vector are:" << endl;
	//mergeSort(vobj, 0, elements - 1);
	quickSort(vobj, 0, elements - 1);
	displayVector(vobj);


	return 0;
}
