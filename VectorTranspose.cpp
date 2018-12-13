//         Course: CS3420 Data Structures
//           Name: Ulikowski, David
//     Assignment: Programming 5.2
//  Date assigned: 2/24/18
//	  Date due:3/6/18
// Date handed in: 3//18
//         Remark: Program 5.1 using vectors

#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;


int main()
{
	vector <vector<int>> vobj;
	int numRows, numCols;

	cout << "Enter the size of the matrix." << endl << endl;
	cout << "How many rows? ";
	cin >> numRows;
	cout << "How many columns? ";
	cin >> numCols;


	cout << "\n*** numRows = " << numRows << ", " << "numCols = " << numCols << endl;
	cout << "*** rowSize = 3, colSize = 3" << endl << endl;

	vobj.resize(numRows);

	for (int r = 0; r < numRows; r++)
		vobj[r].resize(numCols);

	cout << "*** Resize cell successful!" << endl << endl;
	for (int r = 0; r < numRows; r++)
	{
		cout << "Enter " << numCols << " values for row #" << r << endl; 
		for (int c = 0; c < numCols; c++)
		{
			cin >> vobj[r][c];
		}
		cout << endl;
	}

	cout << "\nContents of the " << numRows << " x " << numCols << " array" << endl;
	for (int r = 0; r < numRows; r++)
	{
		for (int c = 0; c < numCols; c++)
		{
			cout << setw(4) << vobj[r][c] << " ";
		}
		cout << endl;
	}

	cout << "\nAfter transpose:" << endl;
	for (int r = 0; r < numCols; r++)
	{
		for (int c = 0; c < numRows; c++)
		{
			cout << setw(4) << vobj[c][r] << " ";
		}
		cout << endl;
	}

	return 0;
}



