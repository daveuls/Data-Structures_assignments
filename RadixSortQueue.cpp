//         Course: CS3420 Data Structures
//           Name: Ulikowski, David
//     Assignment: Programming 12.1
//  Date assigned: 4/11/18
//	     Date due: 4/19/18
// Date handed in: 
//         Remark: Program that performs radix sort on a queue of strings

#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

template <typename T>
void distributeLetters(vector<T> &vect, queue<T> q[], int power)
{
	for (unsigned int i = 0; i < vect.size(); i++)
	{
		//q[(vect[i] / power) % 10].push(vect[i]);
	}
}

template <typename T>
void collect(queue<T> q[], vector<T> &vect)
{
	int i = 0;

	for (int digit = 0; digit < 10; digit++)
	{
		while (!q[digit].empty())
		{
			vect[i] = q[digit].front();
			q[digit].pop();
			i++;
		}
	}
}

template <typename T>
void radixSort(vector<T> &vect, int n)
{
	int power = 5;
	queue<T> q[26];

	for (int i = 0; i < n; i++)
	{
		distributeLetters(vect, q, power);
		collect(q, vect);
		power--;
	}
}

int main()
{
	//queue<int> myQueue;
	//vector<int> myVec;
	queue<string> stringQ;
	vector<string> stringVec;
	string queueArray[10] = { "radix", "bubble", "insert", "select", "quick",
		"bucket", "shell", "heap", "merge", "count" };

	for (int i = 0; i < 10; i++)
	{
		/*int randomNum = rand() % 9999 + 1; // randomly select numbers from 1 to 9,999
		myQueue.push(randomNum);
		myVec.push_back(randomNum);*/
		stringQ.push(queueArray[i]);
		stringVec.push_back(queueArray[i]);
	}

	cout << "Before sorting, list contains:" << endl;
	/*while (!myQueue.empty())
	{
	cout << myQueue.front() << "  ";
	myQueue.pop();
	}*/
	while (!stringQ.empty())
	{
		cout << stringQ.front() << endl;
		stringQ.pop();
	}

	cout << endl << "After sorting, list contains:" << endl;
	/*for (int i = 0; i < 10; i++)
	{
	radixSort(myVec, 10);
	cout << myVec[i] << " ";
	}*/
	for (int i = 0; i < 10; i++)
	{
		radixSort(stringVec, 10);
		cout << stringVec[i] << endl;
	}
	cout << endl;

	return 0;
}


