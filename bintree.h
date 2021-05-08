// ------------------------------ bintree.h -----------------------------------
// Ahmad Yousif - CSS 343A
// Created:       10/12/2020
// Last Modified: 10/25/2020
// ----------------------------------------------------------------------------
// Header file for the BinTree class. This program implements the internal
// representation of a binary search tree. Constructors, accessors, and other
// operators and functions have been defined and overloaded for BST manipulation
// in this program.
// ----------------------------------------------------------------------------
// Assumptions: 
// - Array to Binary Search Tree assumes that the array passed in is sorted.
// ----------------------------------------------------------------------------

#include <iostream>
#include "nodedata.h"

using namespace std;

class BinTree
{
public:
	////////////////// Default Constructor ////////////////////
	// <summary>
	// Default constructor for class BinTree. Creates an empty tree.
	// </summary>
	BinTree();

	//////////////////// Copy Constructor /////////////////////
	// <summary>
	// Copy constructor for class BinTree. Performs a deep copy.
	// </summary>
	// <parameter = "obj">
	// BinTree object to be copied.
	// </parameter>
	BinTree(const BinTree &obj);

	////////////////////// Destructor /////////////////////////
	// <summary>
	// Destructor for class BinTree. Calls makeEmpty.
	// </summary>
	~BinTree();

	//////////////////////// Is Empty /////////////////////////
	// <summary>
	// Function that checks whether the current BinTree is empty. BinTree is empty
	// if the root node is empty.
	// </summary>
	// <returns>
	// Returns true if the BinTree root node is null. Returns false otherwise.
	// </returns>
	bool isEmpty() const;

	/////////////////////// Make Empty ////////////////////////
	// <summary>
	// Function that empties BinTree. Calls the makeEmpty helper function to
	// individually empty each node in BinTree. isEmpty returns true when called
	// on a BinTree directly after this function.
	// </summary>
	void makeEmpty();

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
	BinTree& operator=(const BinTree &obj);

	/////////////////////// == Operator ///////////////////////
	// <summary>
	// Function for the overloaded == comparison operator.
	// </summary>
	// <returns>
	// Returns true if the two BinTrees are identical, returns false otherwise.
	// </returns>
	bool operator==(const BinTree &obj) const;

	/////////////////////// != Operator ///////////////////////
	// <summary>
	// Function for the overloaded != comparison operator. Opposite of the
	// overloaded == implementation.
	// </summary>
	// <returns>
	// Returns true if the two BinTrees are not identical, returns false otherwise.
	// </returns>
	bool operator!=(const BinTree &obj) const;

	/////////////////////// << Operator ///////////////////////
	// <summary>
	// Function for the overloaded << operator. Prints the BinTree horizontally
	// using inOrder traversal.
	// </summary>
	// <returns>
	// Returns the output stream for the correctly formatted BinTree output to be
	// printed in the console.
	// </returns>
	friend ostream& operator<<(ostream& out, const BinTree& obj);

	//////////////////////// Retrieve /////////////////////////
	// <summary>
	// Function to search for the passed data in the BinTree, sets it to
	// retrieveData if found.
	// </summary>
	// <returns>
	// Returns true if the data is found and set, false otherwise.
	// </returns>
	bool retrieve(const NodeData &data, NodeData* &retrieveData) const;

	/////////////////////// Get Height ////////////////////////
	// <summary>
	// Function to get the height of BinTree at the node containing the data
	// parameter.
	// </summary>
	// <returns>
	// Returns the integer height of BinTree at the data. Returns 0 if
	// data is not found in BinTree.
	// </returns>
	int getHeight(const NodeData &data) const;

	/////////////// Binary Search Tree to Array ///////////////
	// <summary>
	// Converts BinTree to array.
	// </summary>
	void bstreeToArray(NodeData* arr[]);

	/////////////// Array to Binary Search Tree ///////////////
	// <summary>
	// Converts array to BinTree.
	// </summary>
	void arrayToBSTree(NodeData* arr[]);

	//////////////////////// Insert ///////////////////////////
	// <summary>
	// Inserts a node to BinTree in the appropriate location based on its NodeData.
	// Duplicate nodes are not inserted.
	// </summary>
	// <returns>
	// Returns the true if the insert was successful, false if unsuccessful.
	// </returns>
	bool insert(NodeData* obj);

	//------------------------- displaySideways ---------------------------------
	// Displays a binary tree as though you are viewing it from the side;
	// hard coded displaying to standard output.
	// Preconditions: NONE
	// Postconditions: BinTree remains unchanged.
	void displaySideways() const;

private:
	struct Node {
		NodeData* data;						// pointer to data object
		Node* left;							// left subtree pointer
		Node* right;						// right subtree pointer
	};
	Node* root;								// root of the tree

	/////////////////// Make Empty Helper /////////////////////
	// <summary>
	// Helper function for makeEmpty function. Individually empties each node in
	// BinTree if not already empty.
	// </summary>
	// <parameter = "node">
	// Root node to start emptying BinTree.
	// </parameter>
	void makeEmpty(Node* &node);

	//////////////////////// = Helper /////////////////////////
	// <summary>
	// Helper function for the = assignment operator.
	// </summary>
	void assign(Node* &leftNode, Node* rightNode);

	//////////////////////// == Helper ////////////////////////
	// <summary>
	// Helper function for the overloaded == comparison operator.
	// </summary>
	// <returns>
	// Returns true if the two BinTrees are identical, returns false otherwise.
	// </returns>
	bool equal(Node* leftNode, Node* rightNode) const;

	//////////////////////// << Helper ////////////////////////
	// <summary>
	// Helper function for the overloaded << operator. Prints the BinTree horizontally
	// using inOrder traversal.
	// </summary>
	void inOrderOut(Node* node) const;

	//////////////////// Get Height Helper ////////////////////
	// <summary>
	// Helper function to get the height of BinTree at the node containing the data
	// parameter. Increases the return value by 1 for every level after finding the
	// data node.
	// </summary>
	// <returns>
	// Returns the integer height of BinTree at the data until reaching the bottom.
	// </returns>
	int getHeight(Node* node) const;

	//////////////////// Find Node Helper ////////////////////
	// <summary>
	// Helper function to find the node in BinTree containing the passed data.
	// Called by retrieve and getHeight.
	// </summary>
	// <returns>
	// Returns the found node in BinTree.
	// </returns>
	Node* findNode(const NodeData &data, Node* node) const;

	/////////// Binary Search Tree to Array Helper ////////////
	// <summary>
	// Helper function for bstreeToArray.
	// </summary>
	void inOrderBstArr(NodeData* arr[], Node* obj, int& index);

	/////////// Array to Binary Search Tree Helper ////////////
	// <summary>
	// Helper function for arrayToBSTree.
	// </summary>
	void inOrderArrBst(NodeData* arr[], int low, int high);

	///////////////////// Insert Helper ///////////////////////
	// <summary>
	// Helper function for insert.
	// </summary>
	// <returns>
	// Returns the true if the insert was successful, false if unsuccessful.
	// </returns>
	bool insert(Node* node, NodeData* obj);

	//---------------------------- Sideways -------------------------------------
	// Helper method for displaySideways
	// Preconditions: NONE
	// Postconditions: BinTree remains unchanged.
	void sideways(Node*, int) const;			// provided below, helper for displaySideways()
};