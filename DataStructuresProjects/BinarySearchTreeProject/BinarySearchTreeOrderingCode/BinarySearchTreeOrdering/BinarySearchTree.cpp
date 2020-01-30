#include <iostream>
#include "BinarySearchTree.h"


//Precondition: New BinrySearchTree object created in main.
//Postcondition: BinarySearchTree object initialized.
BinarySearchTree::BinarySearchTree() {

	//Initialize root to null.
	Root = 0;

	NumberOfElements = 0;

}

//Precondition:: BinarySearchTree object goes out of scope, object was previously initialized.
//Postcondition: All dynamically allocated memory is deallocated safely.
BinarySearchTree::~BinarySearchTree() {

	MakeEmpty(Root);

}

//Precondition: Tree object is initialized.
//Postcondition: Node with value is returned (for use in calling the delete function) or null if not found. Tree is unchanged.
BinaryNode*& BinarySearchTree::FindNodeByValue(int SearchingValue) {

	return FindNode(SearchingValue, Root);

}

//Precondition: SearchingNode is an ancestor of the node we're looking for (or would be, if the node does not currently exist). 
//Postcondition: If found, node the value is in is returned. If not found, returns null. Tree is unchanged.
BinaryNode*& BinarySearchTree::FindNode(int SearchingValue, BinaryNode*& SearchingNode) {

	if (SearchingNode == 0 || SearchingNode->Value == SearchingValue) {

		//If found or not found where expected, we return what we have.
		//Returns where number should be if not found.
		return SearchingNode;

	}

	//If we can not determine a final answer yet, keep recursivly looking.

	if (SearchingValue < SearchingNode->Value) {

		//If value we're looking for is greater than what we have, go right.
		return FindNode(SearchingValue, SearchingNode->Left);

	} else if (SearchingValue > SearchingNode->Value) {

		//If value we're looking for is less than what we have, go left.
		return FindNode(SearchingValue, SearchingNode->Right);

	}

}

//Precondition: Value does not already exist in binary search tree and tree object is initialized.
//Postcondition: Value added correctly to binary search tree.
void BinarySearchTree::AddNode(int ValueToAdd, BinaryNode*& NodeToAdd) {

	//Create new node at location, load it with values.

	NodeToAdd = new BinaryNode;

	NodeToAdd->Value = ValueToAdd;

	NodeToAdd->Left = 0;

	NodeToAdd->Right = 0;

	//Update the NumberOfElements
	NumberOfElements++;

}

//Precondition: Value already exists in binary search tree and tree object is initialized.
//Postcondition: Value deleted. If two children, right-most node of left branch where value was is deallocated after that value is overwritten over the deleted value's.
//If one children, node is deleted and pointer points to child. If no children, node is simply deleted. 
void BinarySearchTree::DeleteNode(BinaryNode*& NodeToDelete) {

	if (NodeToDelete->Left == 0 && NodeToDelete->Right == 0) {

		//If node is a leaf node.

		delete NodeToDelete;

		//Make NodeToDelete null.
		NodeToDelete = 0;

		//Update NumberOfElements to reflect changes.
		NumberOfElements--;

	} else if (NodeToDelete->Left == 0) {

		//If only the left node has no descendent.

		//Create temp node so we can safely delete 
		BinaryNode* TempNode = NodeToDelete;

		NodeToDelete = NodeToDelete->Right;

		delete TempNode;

		//Update NumberOfElements to reflect changes.
		NumberOfElements--;

	} else if (NodeToDelete->Right == 0) {

		//If only the right node has no descendent.

		//Create temp node so we can safely delete 
		BinaryNode* TempNode = NodeToDelete;

		NodeToDelete = NodeToDelete->Left;

		delete TempNode;

		//Update NumberOfElements to reflect changes.
		NumberOfElements--;

	} else {

		//If Two childs

		//Use TempNode to remain at the location of the value to delete.
		BinaryNode* TempNode = NodeToDelete;

		//Find Right-most child of the left branch.

		TempNode = TempNode->Left;

		while (TempNode->Right != 0) {

			TempNode = TempNode->Right;

		}

		int TempInt = TempNode->Value; //Copy value over to temp int.

		//Can not copy over to NodeToDelete yet to avoid duplicate values
		//(We are calling DeleteValue again)

		//Since the right-most node of the elft branch will
		//Either have one child or no children, we can call function
		//and the above case will handle and restructure. 

		DeleteNode(FindNodeByValue(TempNode->Value));

		NodeToDelete->Value = TempInt;

		//Do not decrement because the function handling deletion of right-most descendent of left branch will already decrement.

	}

}

//Precondition: Tree object is initialized.
//Postcondition: Tree object's values are printed in "pre"order.
void BinarySearchTree::Preorder() const {

	PrintPreorder(Root);

}

//Precondition: "Current" is a node in tree.
//Postcondition: "Current" is printed, left branch of "Current" is printed, and right branch of "Current" is printed.
void BinarySearchTree::PrintPreorder(BinaryNode* Current) const {

	//Preorder: Print "Current" first.

	//If "Current" exists.
	if (Current != 0) {

		std::cout << Current->Value << " | ";
		PrintPreorder(Current->Left);
		PrintPreorder(Current->Right);

	}

}

//Precondition: Tree object initialized.
//Postcondition: Tree object's values printed in "in"order.
void BinarySearchTree::Inorder() const {

	PrintInorder(Root);

}

//Precondition: "Current" is a node in tree.
//Postcondition: Left branch of "Current" is printed, "Current" is printed, and right branch of "Current" is printed.
void BinarySearchTree::PrintInorder(BinaryNode* Current) const {

	//Inorder: Print "Current" in between two branches.

	//If "Current" exists.
	if (Current != 0) {

		PrintInorder(Current->Left);
		std::cout << Current->Value << " | ";
		PrintInorder(Current->Right);

	}

}

//Precondition: Tree object initialized.
//Postcondition: Tree object's values printed in "post"order.
void BinarySearchTree::Postorder() const {

	PrintPostorder(Root);

}

//Precondition: "Current" is a node in tree.
//Postcondition: Left branch of "Current" is printed, right branch of "Current" is printed, and "Current" is printed.
void BinarySearchTree::PrintPostorder(BinaryNode* Current) const {

	//Postorder: Print "Current" last.

	//If "Current" exists.
	if (Current != 0) {

		PrintPostorder(Current->Left);
		PrintPostorder(Current->Right);
		std::cout << Current->Value << " | ";

	}

}

//Precondition: Tree object is initialized.
//Postcondition: Determiend whether to be full or not.
bool BinarySearchTree::IsFull() const {

	BinaryNode* TempNode;

	try {

		//Create a temproary node to see if tis possible.
		//Delete after if no problems.

		TempNode = new BinaryNode;
		delete TempNode;
		return false;

	} catch (std::bad_alloc exception) {

		//If an error, tree is full.
		return true;

	}

}

//Precondition: Tree object is initialized.
//Postcondition: Determiend whether to be empty or not.
bool BinarySearchTree::IsEmpty() const {

	return (Root == 0);

}

//Precondition: Tree object is initialized. Current is an existing node in the tree. First "Current" is root.
//Postcondition: Both branches of "Current" are first deleted, then "Current" is deleted.
//Everything under and including "Current" is deleted.
void BinarySearchTree::MakeEmpty(BinaryNode*& Current) {

	//Delete in postorder. Most efficient.

	if (Current != 0) {

		MakeEmpty(Current->Left);
		MakeEmpty(Current->Right);
		delete Current;

	}


}

//Precondition: Tree object is initialized.
//Postcondition: Returns the data member "NumberOfElements".
int BinarySearchTree::GetNumberOfElements() const {

	return NumberOfElements;

}
