//         Course: CS3420 Data Structures
//           Name: Ulikowski, David
//     Assignment: Programming 5.1
//  Date assigned: 2/24/18
//	  Date due:3/6/18
// Date handed in: 3//18
//         Remark: Matrix class with transpose operation

#include <iostream>
#include <iomanip>
using namespace std;

class Matrix
{
public:
	Matrix();
	// default constructor
	// Postcondition: all elements are initialized to 0

	double& operator()(const int rn, const int cn);
	// rn: row subscript; cn: column subscript
	// Postcondition: returns the value of data[rn][cn]

	void operator()();
	// An overloaded function that sets all array elements to zero 
	// Postcondition: clears or reset all elements of 2D data array

	void transpose(int &numRows, int &numCols);
	// numRows and numCols: the actual # rows & columns that are to be operated on
	// Postcondition: entire rows and columns are interchanged

	void fill2dArray(int &numRows, int &numCols);
	//  Precondition: numRows <= ROW_SIZE and numCols <= COL_SIZE
	// Postcondition: data array filled with numRows x numCols values


	void display2dArray(int &numRows, int &numCols);
	// Postcondition: displays the contents of numRows x numCols 2D array

private:
	static const int ROW_SIZE = 4, COL_SIZE = 4;
	double data[ROW_SIZE][COL_SIZE];
};

Matrix::Matrix()
{
	for (int i = 0; i < ROW_SIZE; i++)
	{
		for (int j = 0; j < COL_SIZE; j++)
			data[i][j] = 0;
	}
}

double& Matrix::operator()(const int rn, const int cn)
{
	return (data[rn][cn]);
}

void Matrix::operator()()
{
	for (int i = 0; i < ROW_SIZE; i++)
	{
		for (int j = 0; j < COL_SIZE; j++)
			data[i][j] = 0;
	}
}

void Matrix::transpose(int &numRows, int &numCols)
{
	cout << "After transpose:" << endl;
	for (int i = 0; i < numCols; i++)
	{
		for (int j = 0; j < numRows; j++)
		{
			cout << data[j][i] << " ";
		}
		cout << endl;
	}
}

void Matrix::fill2dArray(int &numRows, int &numCols)
{
	for (int i = 0; i < numRows; i++)
	{
		cout << "\nEnter " << numCols << " values for row #" << i << endl;
		for (int j = 0; j < numCols; j++)
		{
			cin >> data[i][j];
		}
	}
}

void Matrix::display2dArray(int &numRows, int &numCols)
{
	cout << "\nContents of the " << numRows << " x " << numCols << " array:" << endl;
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			cout << data[i][j] << " ";
		}
		cout << endl;
	}
}

int main()
{
	Matrix m;
	int rows, cols;

	cout << "You may enter up to 10 rows and 10 columns of numbers." << endl << endl;
	cout << "How many rows? ";
	cin >> rows;
	cout << "How many columns? ";
	cin >> cols;

	m.fill2dArray(rows, cols);
	m.display2dArray(rows, cols);
	m.transpose(rows, cols);

	return 0;
}



