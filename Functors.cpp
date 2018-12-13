//         Course: CS3420 Data Structures
//           Name: Ulikowski, David
//     Assignment: Programming 8
//  Date assigned: 3/20/18
//		 Date due: 3/27/18
// Date handed in: 3/27/18
//         Remark: Program using functors to fill and sort vectors

#include<iostream>
#include<vector>

using namespace std;

template <class T>
void writeVector(const vector<T>& v);
// forward declaration of a template class function
// Postcondition: contents of vector v are displayed

template<class T>
class greaterThan;
// forward declaration of the greaterThan class
// the class allows functional objects to be declared. The Object calls a greater-than function defined in the class

template<class T>
class lessThan;
// forward declaration of teh lessThan class
// the class allows functional objects to be declared. The Object calls a less-than function defined in the class
template <class T, class Compare>
void insertionSort(vector<T>& v, Compare comp);
// use the insertion sort to order v using function object comp depending on the functional object
// Postcondition: of the functional object comp is an object of lessThan type, the vector v is sorted 
//				    in ascending order; if greaterThan type, the vector v is sorted in descending order

// ***** Implementation of the functors *****
template <class T>
void writeVector(const vector<T>& v)
{
	int i, n = v.size();

	for (i = 0; i < n; i++)
		cout << v[i] << "  ";
	cout << endl;
}

// objects of type greaterThan<T> evaluate x > y
template<class T>
class greaterThan
{
public:
	bool operator() (const T& x, const T& y) const
	{
		return x > y;
	}
};

// objects of type lessThan<T> evaluate x < y
template<class T>
class lessThan
{
public:
	bool operator() (const T& x, const T& y) const
	{
		return x < y;
	}
};

template <class T, class Compare>
void insertionSort(vector<T>& v, Compare comp)
{
	int i, j, n = v.size();
	T temp;

	// place v[i] into the sublist v[0] ... v[i-1], 1 <= i <= n-1, so it is in the correct position
	for (i = 1; i < n; i++)
	{
		// index j scans down list from v[i] looking for correct position to locate target. assigns it to v[j]
		j = i;
		temp = v[i];
		// locate insertion point by scanning downward as long as comp(temp, v[j-1]) is true and we have not 
		//     encountered the beginning of the list
		while (j > 0 && comp(temp, v[j - 1]))
		{
			// shift elements up list to make room for insertion
			v[j] = v[j - 1];
			j--;
		}
		// the location is found; insert temp
		v[j] = temp;
	}
}

int main()
{
	vector<int> v = { 2, 1, 7, 8, 12, 15, 3, 5 }; 

	cout << "Before sorting, vector contains:" << endl;
	writeVector(v);

	cout << "\nAfter sorting the vector in ascending order, the vector contains:" << endl;
	insertionSort(v, lessThan<int>());
	writeVector(v);

	cout << "\nAfter sorting the vector in descending order, the vector contains:" << endl;
	insertionSort(v, greaterThan<int>());
	writeVector(v);
	cout << endl;

	return 0;
}