// ----------------------------- bintree.cpp ----------------------------------
// Ahmad Yousif - CSS 343A
// Created:       10/12/2020
// Last Modified: 10/25/2020
// ----------------------------------------------------------------------------
// Implementation file for the BinTree class. This program implements the internal
// representation of a binary search tree. Constructors, accessors, and other
// operators and functions have been defined and overloaded for BST manipulation
// in this program.
// ----------------------------------------------------------------------------
// Assumptions: 
// - Array to Binary Search Tree assumes that the array passed in is sorted.
// ----------------------------------------------------------------------------

#include <iostream>
#include "bintree.h"

using namespace std;

////////////////// Default Constructor ////////////////////
// <summary>
// Default constructor for class BinTree. Creates an empty tree.
// </summary>
BinTree::BinTree()
{
	root = nullptr;
}

//////////////////// Copy Constructor /////////////////////
// <summary>
// Copy constructor for class BinTree. Performs a deep copy.
// </summary>
// <parameter = "obj">
// BinTree object to be copied.
// </parameter>
BinTree::BinTree(const BinTree& obj)
{
	assign(root, obj.root);
}

////////////////////// Destructor /////////////////////////
// <summary>
// Destructor for class BinTree. Calls makeEmpty.
// </summary>
BinTree::~BinTree()
{
	makeEmpty();
}

//////////////////////// Is Empty /////////////////////////
// <summary>
// Function that checks whether the current BinTree is empty. BinTree is empty
// if the root node is empty.
// </summary>
// <returns>
// Returns true if the BinTree root node is null. Returns false otherwise.
// </returns>
bool BinTree::isEmpty() const
{
	if (root == nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/////////////////////// Make Empty ////////////////////////
// <summary>
// Function that empties BinTree. Calls the makeEmpty helper function to
// individually empty each node in BinTree. isEmpty returns true when called
// on a BinTree directly after this function.
// </summary>
void BinTree::makeEmpty()
{
	makeEmpty(root);
}

/////////////////// Make Empty Helper /////////////////////
// <summary>
// Helper function for makeEmpty function. Individually empties each node in
// BinTree if not already empty.
// </summary>
// <parameter = "node">
// Root node to start emptying BinTree.
// </parameter>
void BinTree::makeEmpty(Node* &node)
{
	if (node != nullptr)
	{
		makeEmpty(node->left);
		makeEmpty(node->right);

		if (node->data != nullptr) {
			delete node->data;
			node->data = nullptr;
		}

		delete node;
		node = nullptr;
	}
}

//////////////////////// = Operator ///////////////////////
// <summary>
// Overloaded BinTree implementation for the = assignment operator.
// </summary>
// <parameter = "obj">
// Right side operant; a BinTree object whose nodes are to be assigned to the
// left side BinTree object.
// </parameter>
// <returns>
// Returns the preceding BinTree that has been modified to contain the same
// nodes as the right side Bintree object.
// </returns>
BinTree& BinTree::operator=(const BinTree &obj)
{
	if (*this != obj)
	{
		makeEmpty();				// Delete contents of left tree
		assign(root, obj.root);		// Assign left tree with contents of right tree
	}

	return *this;				// Return modified left tree
}

//////////////////////// = Helper /////////////////////////
// <summary>
// Helper function for the = assignment operator.
// </summary>
void BinTree::assign(Node* &leftNode, Node* rightNode)
{
	if (rightNode != nullptr)
	{
		leftNode = new Node();
		leftNode->data = new NodeData(*rightNode->data);

		assign(leftNode->left, rightNode->left);
		assign(leftNode->right, rightNode->right);
	}
	else
	{
		leftNode = nullptr;
	}
}

/////////////////////// == Operator ///////////////////////
// <summary>
// Function for the overloaded == comparison operator.
// </summary>
// <returns>
// Returns true if the two BinTrees are identical, returns false otherwise.
// </returns>
bool BinTree::operator==(const BinTree &obj) const
{
	return equal(root, obj.root);
}

//////////////////////// == Helper ////////////////////////
// <summary>
// Helper function for the overloaded == comparison operator.
// </summary>
// <returns>
// Returns true if the two BinTrees are identical, returns false otherwise.
// </returns>
bool BinTree::equal(Node* leftNode, Node* rightNode) const
{
	if (leftNode == nullptr && rightNode == nullptr)
	{
		return true;
	}
	else if (leftNode == nullptr || rightNode == nullptr)
	{
		return false;
	}
	else if (*(leftNode->data) == *(rightNode->data)
			&& leftNode->left == nullptr
			&& leftNode->right == nullptr
			&& rightNode->left == nullptr
			&& rightNode->right == nullptr)
	{
		return true;
	}

	bool status = *(leftNode->data) == *(rightNode->data);
	status &= equal(leftNode->left, rightNode->left);
	status &= equal(leftNode->right, rightNode->right);;

	return status;
}

/////////////////////// != Operator ///////////////////////
// <summary>
// Function for the overloaded != comparison operator. Opposite of the
// overloaded == implementation.
// </summary>
// <returns>
// Returns true if the two BinTrees are not identical, returns false otherwise.
// </returns>
bool BinTree::operator!=(const BinTree &obj) const
{
	return !equal(root, obj.root);
}

/////////////////////// << Operator ///////////////////////
// <summary>
// Function for the overloaded << operator. Prints the BinTree horizontally
// using inOrder traversal.
// </summary>
// <returns>
// Returns the output stream for the correctly formatted BinTree output to be
// printed in the console.
// </returns>
ostream& operator<<(ostream& out, const BinTree& obj)
{
	obj.inOrderOut(obj.root);
	out << endl;
	return out;
}

//////////////////////// << Helper ////////////////////////
// <summary>
// Helper function for the overloaded << operator. Prints the BinTree horizontally
// using inOrder traversal.
// </summary>
void BinTree::inOrderOut(Node* obj) const
{
	if (obj != nullptr)
	{
		inOrderOut(obj->left);
		cout << *obj->data << " ";
		inOrderOut(obj->right);
	}
}

//////////////////////// Retrieve /////////////////////////
// <summary>
// Function to search for the passed data in the BinTree, sets it to
// retrieveData if found.
// </summary>
// <returns>
// Returns true if the data is found and set, false otherwise.
// </returns>
bool BinTree::retrieve(const NodeData &data, NodeData* &retrieveData) const
{
	bool status = false;
	Node* foundPtr = findNode(data, root);

	if (foundPtr != nullptr) {
		retrieveData = foundPtr->data;
		status = true;
	}

	return status;
}

/////////////////////// Get Height ////////////////////////
// <summary>
// Function to get the height of BinTree at the node containing the data
// parameter.
// </summary>
// <returns>
// Returns the integer height of BinTree at the data. Returns 0 if
// data is not found in BinTree.
// </returns>
int BinTree::getHeight(const NodeData &data) const
{
	Node* foundPtr = findNode(data, root);
	return (foundPtr != nullptr) ? getHeight(foundPtr) : 0;
}

//////////////////// Get Height Helper ////////////////////
// <summary>
// Helper function to get the height of BinTree at the node containing the data
// parameter. Increases the return value by 1 for every level after finding the
// data node.
// </summary>
// <returns>
// Returns the integer height of BinTree at the data until reaching the bottom.
// </returns>
int BinTree::getHeight(Node* node) const
{
	if (node == nullptr)
	{
		return 0;
	}

	int left = getHeight(node->left);		// search left
	int right = getHeight(node->right);     // search right

	if (right > left)
	{
		return right + 1;
	}
	else
	{
		return left + 1;
	}
}

//////////////////// Find Node Helper ////////////////////
// <summary>
// Helper function to find the node in BinTree containing the passed data.
// Called by retrieve and getHeight.
// </summary>
// <returns>
// Returns the found node in BinTree.
// </returns>
BinTree::Node* BinTree::findNode(const NodeData &data, Node* node) const
{
	if (node == nullptr)
	{
		return nullptr;
	}
	else if (data == *(node->data))
	{
		return node;
	}

	Node* leftPtr = findNode(data, node->left);		 // search left
	Node* rightPtr = findNode(data, node->right);    // search right

	return (leftPtr != nullptr) ? leftPtr : rightPtr;
}

/////////////// Binary Search Tree to Array ///////////////
// <summary>
// Converts BinTree to array.
// </summary>
void BinTree::bstreeToArray(NodeData* arr[])
{
	int index = 0;
	inOrderBstArr(arr, root, index);
	makeEmpty();
}

/////////// Binary Search Tree to Array Helper ////////////
// <summary>
// Helper function for bstreeToArray.
// </summary>
void BinTree::inOrderBstArr(NodeData* arr[], Node* obj, int& index)
{
	if (obj != nullptr)
	{
		inOrderBstArr(arr, obj->left, index);
		NodeData* newData = obj->data;
		obj->data = nullptr;
		arr[index++] = newData;
		newData = nullptr;
		inOrderBstArr(arr, obj->right, index);
	}
}

/////////////// Array to Binary Search Tree ///////////////
// <summary>
// Converts array to BinTree.
// </summary>
void BinTree::arrayToBSTree(NodeData* arr[])
{
	makeEmpty();

	int arrSize = 0;
	for (arrSize = 0; arrSize < 100; arrSize++) {
		if (arr[arrSize] == nullptr)
			break;
	}

	inOrderArrBst(arr, 0, arrSize - 1);
}

/////////// Array to Binary Search Tree Helper ////////////
// <summary>
// Helper function for arrayToBSTree.
// </summary>
void BinTree::inOrderArrBst(NodeData* arr[], int min, int max)
{
	if (min > max)
	{
		return;
	}

	int mid = (min + max) / 2;
	insert(arr[mid]);
	arr[mid] = nullptr;

	inOrderArrBst(arr, min, mid - 1);
	inOrderArrBst(arr, mid + 1, max);
}

//////////////////////// Insert ///////////////////////////
// <summary>
// Inserts a node to BinTree in the appropriate location based on its NodeData.
// Duplicate nodes are not inserted.
// </summary>
// <returns>
// Returns the true if the insert was successful, false if unsuccessful.
// </returns>
bool BinTree::insert(NodeData* obj)
{
	bool status = false;

	if (root == nullptr)
	{
		Node* newRoot = new Node();
		newRoot->data = obj;
		root = newRoot;
		status = true;
	}
	else
	{
		status = insert(root, obj);
	}

	return status;
}

///////////////////// Insert Helper ///////////////////////
// <summary>
// Helper function for insert.
// </summary>
// <returns>
// Returns the true if the insert was successful, false if unsuccessful.
// </returns>
bool BinTree::insert(Node* node, NodeData* obj)
{
	if (*obj <= *(node->data))
	{
		if (*obj == *(node->data))
		{
			return false;
		}
		else if (node->left == nullptr)
		{
			Node* newNode = new Node();
			newNode->data = obj;
			node->left = newNode;

			return true;
		}
		else
		{
			return insert(node->left, obj);
		}
	}
	else
	{
		if (node->right == nullptr)
		{
			Node* newNode = new Node();
			newNode->data = obj;
			node->right = newNode;

			return true;
		}
		else
		{
			return insert(node->right, obj);
		}
	}
}

//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::displaySideways() const {
	sideways(root, 0);
}

//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::sideways(Node* current, int level) const {
	if (current != nullptr) {
		level++;
		sideways(current->right, level);

		// indent for readability, 4 spaces per depth level 
		for (int i = level; i >= 0; i--) {
			cout << "    ";
		}

		cout << *current->data << endl;        // display information of object
		sideways(current->left, level);
	}
};