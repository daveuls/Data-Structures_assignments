// --------------- Adjacent list implementation of a digraph -----------------
// --------------- based on Nyhoff's 2005 Data Structure book ----------------
#include <iostream>
#include <list>
#include <vector>
#include <queue>		// fro breadth-first search or BFS
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

template <typename T>
class Digraph
{
public:
	/***** Member Functions *****/
	T data(int k) const;
	/*-----------------------------------------------------------------------
	Retrieve data value in a given vertex.
	Precondition:  k is the number of a vertex.
	Postcondition: Data value stored in vertex k is returned.
	-----------------------------------------------------------------------*/

	void read(ifstream &inStream);
	/*-----------------------------------------------------------------------
	Input operation: read data from a disk file
	Precondition:  ifstream inStream is open.  The lines in the file to
	which it is connected are organized so that the data item in a
	vertex is on one line and on the next line is the number of
	vertices adjacent to it followed by a list of these vertices.
	Postcondition: The adjacency list representation of this digraph
	has been stored in myAdjacencyLists.
	-----------------------------------------------------------------------*/

	void display(ostream &out);
	/*-----------------------------------------------------------------------
	Output operation.
	Precondition:  ostream out is open.
	Postcondition: Each vertex and its adjacency list have been output to out.
	-----------------------------------------------------------------------*/

	void depthFirstSearch(int start);
	/*-----------------------------------------------------------------------
	Depth first search of digraph via depthFirstSearchAux(), starting at vertex start.
	Precondition:  start (an integer value) is a vertex.
	Postcondition: All elements of unvisited are initialized to true.
	-----------------------------------------------------------------------*/

	void depthFirstSearchAux(int start, vector<bool> &unvisited);
	/*-----------------------------------------------------------------------
	Recursive depth first search of digraph, starting at vertex start.
	Precondition:  start is a vertex;  unvisited[i] is true if vertex i has
	not yet been visited, and is false otherwise.
	Postcondition: Vector unvisited has been updated.
	-----------------------------------------------------------------------*/

	vector<int> shortestPath(int start, int destination);
	/*-----------------------------------------------------------------------
	Find a shortest path in the digraph from vertex start to vertex destination.
	Precondition:  start and destination are vertices.
	Postcondition: A vector of vertices along the shortest path from start to destination
	is returned.
	-----------------------------------------------------------------------*/

private:
	/***** "Head nodes" of adjacency lists *****/
	class VertexInfo
	{
	public:
		T data;
		list<int> adjacencyList;
	};

	/***** Data member *****/
	vector<VertexInfo> myAdjacencyLists;
}; // end of Digraph class template declaration

// ***** data() *****
template <typename T>
inline T Digraph<T>::data(int k) const
{
	return myAdjacencyLists[k].data;
}



// ***** read() member function *****
template <typename T>
void Digraph<T>::read(ifstream & inStream)
{
	Digraph<T>::VertexInfo vi;
	int n,           // number of vertices adjacent to some vertex
		vertex;      // the number of a vertex

	// Put a garbage 0-th value so indices start with 1, as is customary
	myAdjacencyLists.push_back(vi); 	// vector<VertexInfo> myAdjacencyLists; is the data member Digraph<T> type

	// Construct adjacency list representation
	for (;;)	// infinite loop until “break” out
	{
		inStream >> vi.data;		// read T type of vertex data
		if (inStream.eof()) break;	// terminate loop when end of file is reached

		inStream >> n;		// read an integer value: the # of adjacent nodes of a vertex
		list<int> adjList;      // construct empty list of n adjacent nodes of the vertex

		for (int i = 1; i <= n; i++)
		{
			inStream >> vertex;
			adjList.push_back(vertex);
		}
		vi.adjacencyList = adjList;		// vi: a vertex object; has 2 data members: “data” &  “adjacencyList”
		myAdjacencyLists.push_back(vi);		// Note: again “myAdjacencyLists” is the data member of Digraph class 
	}
}

// ***** display() member function *****
template <typename T>
void Digraph<T>::display(ostream & out)
{
	out << "Adjacency-List Representation: \n";
	for (unsigned i = 1; i < myAdjacencyLists.size(); i++)	// Note: subscript i begins with 1, not 0!
	{
		out << "     " << i << ": " << setw(14) << myAdjacencyLists[i].data << " --> ";
		for (list<int>::iterator it = myAdjacencyLists[i].adjacencyList.begin();
			it != myAdjacencyLists[i].adjacencyList.end(); it++)
			out << *it << "  ";
		out << endl;
	}
}

// ***** depthFirstSearch() and depthFirstSearchAux() member functions *****
template <typename T>
void Digraph<T>::depthFirstSearch(int start)
{
	vector<bool> unvisited(myAdjacencyLists.size(), true);	// myAdjacencyLists.size() returns # of total  of vertices 	depthFirstSearchAux(start, unvisited);
}


template <typename T>
void Digraph<T>::depthFirstSearchAux(int start, vector<bool> &unvisited)
{
	// Add statements here to process myAdjacencyLists[start].data
	cout << myAdjacencyLists[start].data << endl;

	unvisited[start] = false;
	// Traverse its adjacency list, performing depth-first searches from each unvisited vertex in it.
	for (list<int>::iterator it = myAdjacencyLists[start].adjacencyList.begin();
		it != myAdjacencyLists[start].adjacencyList.end(); it++)
		if (unvisited[*it]) 	// check if current vertex has been visited
			depthFirstSearchAux(*it, unvisited);  // start DFS from new node
}

// ***** shortestPath() member function *****
template<typename T>
vector<int> Digraph<T>::shortestPath(int start, int destination)
{
	int n = myAdjacencyLists.size();	// n: total number of vertices 
	vector<int> distLabel(n, -1),	// “distance” labels for vertices, all marked as unvisited (-1)
		predLabel(n);		// predecessor labels for vertices
	// Perform breadth first search from start to find destination, labeling vertices with distances from start as we go.
	distLabel[start] = 0;	// 1 <= start <= n; starting vertex has subscript value 0
	int distance = 0,		// distance from start vertex to another node (i.e., the # of hops to reach another node)
		vertex;			// a vertex identified by a positive integer from 1 to n
	queue<int> vertexQueue;    	// queue of vertices; needed for BFS
	vertexQueue.push(start);
	while (distLabel[destination] < 0 && !vertexQueue.empty()) // all distLabel[ ] elements are initialized to (-1)
	{									         // as unvisited				
		vertex = vertexQueue.front();
		vertexQueue.pop();
		if (distLabel[vertex] > distance)
			distance++;
		for (list<int>::iterator it = myAdjacencyLists[vertex].adjacencyList.begin();
			it != myAdjacencyLists[vertex].adjacencyList.end(); it++)
			if (distLabel[*it] < 0)
			{
				distLabel[*it] = distance + 1;
				predLabel[*it] = vertex;
				vertexQueue.push(*it);
			}
	}
	distance++;

	// ***** reconstruct the shortest path if there is one *****
	vector<int> path(distance + 1);	// path vector has a size of (distance+1)
	if (distLabel[destination] < 0)	// all vertices are initialized to -1 as unvisited 
		cout << "Destination not reachable from start vertex\n";
	else
	{
		path[distance] = destination;
		for (int k = distance - 1; k >= 0; k--)
			path[k] = predLabel[path[k + 1]];
	}

	return path;
}

/*-------------------------------------------------------------------------
Program to find the most direct route in an airline network from a given
start city to a given destination city.  A digraph represented by its
adjacency-list implementation is used for the network, and the
information needed to construct it is read from “flyNetwork” file on disk.
-------------------------------------------------------------------------*/

int main()
{
	cout << "Enter name of network file: ";
	string networkFile;
	cin >> networkFile;
	ifstream inFile(networkFile.data());
	if (!inFile.is_open())
	{
		cerr << "*** Cannot open " << networkFile << " ***\n";
		exit(-1);
	}
	Digraph<string> d;
	d.read(inFile);
	cout << "\nThe Digraph's ";
	d.display(cout);
	cout << endl;

	int start, destination;
	char response;
	do
	{
		cout << " Number of start city? ";
		cin >> start;
		cout << "Number of destination? ";
		cin >> destination;

		vector<int> path = d.shortestPath(start, destination);
		cout << "Shortest path is:\n";

		for (unsigned k = 0; k < path.size() - 1; k++)
		{
			cout << setw(3) << path[k] << ' ' << d.data(path[k]) << endl;
			cout << "      |\n"
				"      v\n";
		}
		cout << setw(3) << destination << ' ' << d.data(destination) << endl;
		cout << "\nMore (Y or N)?";
		cin >> response;
	} while (response == 'y' || response == 'Y');
}
