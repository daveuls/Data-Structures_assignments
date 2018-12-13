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

void countSort(string a[], int size, int n)
{
	string *b = NULL; int *c = NULL;
	b = new string[size];
	c = new int[257];

	for (int i = 0; i < 257; i++)
	{
		c[i] = 0;
	}

	for (int j = 0; j < size; j++)
	{
		c[n < a[j].size() ? (int)(unsigned char)a[j][n] + 1 : 0]++; 
	}

	for (int f = 1; f < 257; f++)
	{
		c[f] += c[f - 1];
	}

	for (int r = size - 1; r >= 0; r--)
	{
	b[c[n < a[r].size() ? (int)(unsigned char)a[r][n] + 1 : 0] - 1] = a[r];
	c[n < a[r].size() ? (int)(unsigned char)a[r][n] + 1 : 0]--;
	}

	for (int l = 0; l < size; l++)
	{
	a[l] = b[l];
	}
	// avold memory leak
	delete[] b;
	delete[] c;
}

int collect(string arr[], int n)
{
	int max = arr[0].size();
	for (int i = 1; i < n; i++)
	{
	if (arr[i].size()>max)
	max = arr[i].size();
	}
return max;
}



void radixSort(string b[], int r)
{
	int max = collect(b, r);
	for (int i = max; i > 0; i--)
	{ 
		countSort(b, r, i - 1);
	}
}

int main()
{
	queue<string> stringQ;
	vector<string> stringVec;
	string queueArray[] = { "radix", "bubble", "insert", "select", "quick",
		"bucket", "shell", "heap", "merge", "count" };

	for (int i = 0; i < 10; i++)
	{
		stringQ.push(queueArray[i]);
		stringVec.push_back(queueArray[i]);
	}

	cout << "Before sorting, list contains:" << endl;
	while (!stringQ.empty())
	{
		cout << stringQ.front() << endl;
		stringQ.pop();
	}

	cout << endl << "After sorting, list contains:" << endl;
	for (int i = 0; i < 10; i++)
	{
		radixSort(queueArray, (int)(sizeof(queueArray) / sizeof(queueArray[0])));
		cout << queueArray[i] << endl;
	}
	cout << endl;

	return 0;
}


