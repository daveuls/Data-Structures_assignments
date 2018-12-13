//         Course: CS3420 Data Structures
//           Name: Ulikowski, David
//     Assignment: Programming 12.1
//  Date assigned: 4/23/18
//	     Date due: 5/3/18
// Date handed in: 
//         Remark: implementation of a binary tree

#include <iostream>
#include <iomanip>
#include <queue>
#include <string>

using namespace std;

struct node
{
	int	item;
	node*	left;
	node*	right;
};


node* newNode(int newItem);
// parameter newItem is used to initialize a new object
// Postcondition: returns the pointer of a new dynamic node initialized with node value newItem

int height(node* root);
// Postcondition: get height of the tree

int countLeaves(node *root, int &count);
// Postcondition: output total number of leaf nodes

void inOrderDisplay(node *root, const string &separator = " ");
// inorder recursive output of the nodes in a binary tree.
// Postcondition: output node values separate by a separator which defaults to "  "

void preOrderDisplay(node *root, const string &separator = " ");
// preorder recursive output of the nodes in a binary tree.
// Postcondition: output node values seperate by a separator which defaults to " "

void postOrderDisplay(node *root, const string &separator = " ");
// postorder recursive output of the nodes in a binary tree.
// Postcondition: output node values separate by a separator which defaults to " "

void levelOrderDisplay(node *root, const string &separator = " ");
// traverse the tree level by level and output each node in level order
// Postcondition: output node values separate by a separator which defaults to "  "

node* newNode(int newItem)
{
	node *temp = new node;
	temp->item = newItem;
	temp->left = temp->right = nullptr;
	return temp;
}

int height(node *root)
{
	int rightHt, leftHt, htValue;

	if (root == nullptr)
	{
		htValue = 0;
	}
	else
	{
		rightHt = height(root->right);
		leftHt = height(root->left);
		htValue = 1 + (leftHt > rightHt ? leftHt : rightHt);
	}
	return htValue;
}

int countLeaves(node *root, int &count)
{
	if (root != NULL)
	{
		if (root->left == nullptr && root->right == nullptr)
			count++;
		countLeaves(root->left, count); // descend left
		countLeaves(root->right, count); // descend right
	}
	return count;
}

void inorderDisplay(node *root)		// LNR
{
	if (root != NULL)
	{
		inorderDisplay(root->left);
		cout << root->item << " ";
		inorderDisplay(root->right);
	}
}

void preorderDisplay(node *root)	// NLR
{
	if (root != NULL)
	{
		cout << root->item << " ";
		preorderDisplay(root->left);
		preorderDisplay(root->right);
	}
}

void postorderDisplay(node *root)	// LRN
{
	if (root != NULL)
	{
		postorderDisplay(root->left);
		postorderDisplay(root->right);
		cout << root->item << " ";
	}
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
		node *node = q.front();		// pointer that points to the front node in queue
		cout << node->item << " ";	// output item from front node in queue
		q.pop();	// remove front node from the queue

		// enqueue the left child
		if (node->left != nullptr)
			q.push(node->left);

		// enqueue the right child
		if (node->right != nullptr)
			q.push(node->right);
	}
}

// Test all functions
int main()
{
	node *root, *b, *c, *d, *e, *f, *g;		// declare pointers to point to nodes in tree
	
	// place instructions here to build a 7 node instructions, node by node such that after
	// scanning in various orders, the output of the scans would be identical to the sample ouput
	root = newNode(30);
	b = newNode(40);
	root->left = b;		// left pointer of root node points to node b
	c = newNode(50);
	root->right = c;	// right pointer of root node points to node c
	d = newNode(60);
	b->left = d;
	e = newNode(70);
	b->right = e;
	f = newNode(80);
	c->left = f;
	g = newNode(90);
	c->right = g;

	cout << "Built a BST with 7 nodes: " << endl << endl;
	// count leaves
	int count = 0;
	count = countLeaves(root, count);
	cout << "Number of leaf nodes: " << count << endl;

	int heightVal = height(root);
	cout << "Height of the tree: " << heightVal << endl << endl;

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
	return 0;
}
