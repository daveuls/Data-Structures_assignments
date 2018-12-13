//         Course: CS3420 Data Structures
//           Name: Ulikowski, David
//     Assignment: Programming 14
//  Date assigned: 
//	     Date due: 
// Date handed in: 
//         Remark: Binary Search Tree basics

#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <strstream>

using namespace std;

struct node
{
	int  item;
	node *left;
	node *right;
};

// class to display binary tree
class tnodeShadow
{
public:
	string nodeValueStr;	// formatted node value
	int level, column;
	tnodeShadow *left, *right;

	tnodeShadow(){}
};

// A function to create a new BST node
node* newNode(int newItem);
// Postcondition: a new node is returned and members initialized to newItem, nullptr, and nullptr, respectively. 
//		The address of the new node is returned

void inorderDisplay(node *root);
//  Precondition: address of the root is passed to the function
// Postcondition: the contents of nodes are displayed in LNR or inorder manner (see sample display)


void preorderDisplay(node *root);
//  Precondition: address of the root is passed to the function
// Postcondition: the contents of the nodes are displayed in NLR or preorder manner (see sample display)

void postorderDisplay(node *root);
//  Precondition: address of the root is passed to the function
// Postcondition: the contents of the nodes are displayed in LRN or postorder manner (see sample display)

int countLeaf(node* root);
//  Precondition: address of the root is passed to the function
// Postcondition: the # of leaf nodes is returned

node* insert(node* root, int newItem);
//  Make use of the newNode function above
//  Precondition: root node pointer & the value  for a new node to be created are passed to the function
// Postcondition: the new node is properly inserted such that the tree remains a binary search tree or BST

int height(node* root);
//  Precondition: root pointer is passed to teh function
// Postcondition: height or depth of the tree is returned

void levelorderOutput(node* root);
//  Precondition: root pointer is passed to the function
// Postcondition: the contents of the nodes are displayed in level order

node* find(node* root, int target, bool &found);
// Search for a node with a value equal to "target"
// Postcondition: If found, assigns "true" to found and the and return the address of the node; else assigns false to found and return nullptr

void displayTree(node* t, int maxCharacters);
// display BST
// Postcondition: Diplays content of binary search tree

node* newNode(int newItem)
{
	node *temp = new node;
	temp->item = newItem;
	temp->left = temp->right = nullptr;
	return temp;
}

void inorderDisplay(node *root) // LNR
{
	if (root != NULL)
	{
		inorderDisplay(root->left);
		cout << root->item << " ";
		inorderDisplay(root->right);
	}
}

void preorderDisplay(node *root) // NLR
{
	if (root != NULL)
	{
		cout << root->item << " ";
		preorderDisplay(root->left);
		preorderDisplay(root->right);
	}
}

void postorderDisplay(node *root) // LRN
{
	if (root != NULL)
	{
		postorderDisplay(root->left);
		postorderDisplay(root->right);
		cout << root->item << " ";
	}
}

int countLeaf(node* root)
{
	int count = 0;

	if (root != NULL)
	{
		if (root->left == NULL && root->right == NULL)
			count++;
		countLeaf(root->left);
		countLeaf(root->right);
	}
	return count;
}

node* insert(node* root, int newItem)
{
	// if tree is empty return a new node
	if (root == nullptr)
	{
		return newNode(newItem);
	}
	// otherwise recur down the tree
	if (newItem < root->item)
	{
		root->left = insert(root->left, newItem);
	}
	else if (newItem > root->item)
	{
		root->right = insert(root->right, newItem);
	}
	return root;
}

int height(node* root)
{
	int rtHt, lftHt, htValue;

	if (root == nullptr)
	{
		htValue = 0;
	}
	else
	{
		rtHt = height(root->right);
		lftHt = height(root->left);
		htValue = 1 + (lftHt > rtHt ? lftHt : rtHt);
	}
	return htValue;
}

void levelorderOutput(node* root)
{
	// base case
	if (root == nullptr)
	{
		return;
	}

	// create an empty queue for level order tansversal
	queue<node *> q;

	// enqueue root and initialize height
	q.push(root);

	while (q.empty() == false)
	{
		// print front of queue and remove it from queue
		node *node = q.front();
		cout << node->item << " ";
		q.pop();

		// enqueue the left child
		if (node->left != nullptr)
			q.push(node->left);

		// enqueue the right child
		if (node->right != nullptr)
			q.push(node->right);
	}
}

node* find(node* root, int target, bool &found)
{
	// uses binary search
	if (root == nullptr)
		return nullptr;		// not found
	else if (root->item == target)
		return root;		// found
	else if (root->item > target)
		// search left subtree
		return find(root->left, target, found);
	else
		// search right subtree
		return find(root->right, target, found);
}

// functions to display binary search tree
tnodeShadow *buildShadowTree(node *t, int level, int &column)
{
	// pointer to new shadow tree node
	tnodeShadow *newNode = NULL;
	// text and ostr used to perform format conversion
	char text[80];
	ostrstream ostr(text, 80);

	if (t != NULL)
	{
		// create the new shadow tree node
		newNode = new tnodeShadow;

		// allocate node for left child at next level in tree; attach node
		tnodeShadow *newLeft = buildShadowTree(t->left, level + 1, column);
		newNode->left = newLeft;

		// initialize data members of the new node
		ostr << t->item << ends;	// format conversion
		newNode->nodeValueStr = text;
		newNode->level = level;
		newNode->column = column;

		// update column to next cell in the table
		column++;

		// allocate new node for right child at the next level in tree; attach node
		tnodeShadow *newRight = buildShadowTree(t->right, level + 1, column);
		newNode->right = newRight;
	}
	return newNode;
}

void deleteShadowTree(tnodeShadow *t)
{
	// if current root node is not NULL, delete its left subtree,
	// its right subtree and then the node itself
	if (t != NULL)
	{
		deleteShadowTree(t->left);
		deleteShadowTree(t->right);
		delete t;
	}
}

void displayTree(node* t, int maxCharacters)
{
	string label;
	int level = 0, column = 0;
	int colWidth = maxCharacters + 1;
	int currLevel = 0, currCol = 0;

	if (t != NULL)
		return;

	// build shadow tree
	tnodeShadow *shadowRoot = buildShadowTree(t, level, column);

	// use during the level order scan of the shadow tree
	tnodeShadow *currNode;

	// store sibilings of each tnodeShadow object in a queue so that
	// they are visited in order at the next level of the tree
	queue<tnodeShadow *> q;

	// insert the root in the queue and set the current level to 0
	q.push(shadowRoot);

	// continue the iterative process until the queue is empty
	while (!q.empty())
	{
		// delete front node from the queue and make it the current node
		currNode = q.front();
		q.pop();

		// if level changes, output a newline
		if (currNode->level > currLevel)
		{
			currLevel = currNode->level;
			currCol = 0;
			cout << endl;
		}

		// if a left child exists, insert the child in the queue
		if (currNode->left != NULL)
			q.push(currNode->left);

		// if a right child exists, insert it in the queue
		if (currNode->right != NULL)
			q.push(currNode->right);

		// output formatted node label
		if (currNode->column > currCol)
		{
			cout << setw((currNode->column - currCol) * colWidth) << " ";
			currCol = currNode->column;
		}
		cout << setw(colWidth) << currNode->nodeValueStr;
		currCol++;
	}
	cout << endl;

	// delete shadow tree
	deleteShadowTree(shadowRoot);
}

int main()
{
	bool found = false;
	int target;
	node *root = nullptr;
	root = insert(root, 50);
	insert(root, 30);
	insert(root, 20);
	insert(root, 40);
	insert(root, 70);
	insert(root, 60);
	insert(root, 80);
	insert(root, 10);

	cout << "Built a BST with 7 nodes as shown below: " << endl << endl;
	displayTree(root, 1);
	cout << endl;

	// count leaves
	int count = countLeaf(root);
	cout << "Number of leaf nodes: " << count << endl;

	int heightVal = height(root);
	cout << "Height of the tree: " << heightVal << endl << endl;

	target = 40;
	cout << "Try to find node with value of " << target << endl;
	find(root, target, found);
	if (found)
		cout << "Node with value " << target << " is found!" << endl << endl;
	else
		cout << "Node with value " << target << " is NOT found!" << endl << endl;
	// print inoder traversal of the BST
	cout << "Preorder traversal/display of nodes in a BST:\n" << "==> ";
	preorderDisplay(root);

	cout << "\n\nInorder traversal/display of nodes in a BST:\n" << "==> ";
	inorderDisplay(root);

	cout << "\n\nPostorder traversal/display of nodes in a BST:\n" << "==> ";
	postorderDisplay(root);

	cout << "\n\nLevelorder traversal/display of nodes in a BST:\n" << "==> ";
	levelorderOutput(root);
	cout << endl << endl;
	system("pause");
	return 0;
}



