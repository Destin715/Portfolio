#pragma once

struct BinaryNode {

	int Value;

	BinaryNode* Left;
	BinaryNode* Right;

};

class BinarySearchTree {
public:

	//Constructor/Destructor

	BinarySearchTree();
	~BinarySearchTree();

	//Functions

	BinaryNode*& FindNodeByValue(int SearchingValue);

	void AddNode(int ValueToAdd, BinaryNode*& NodeToAdd);
	void DeleteNode(BinaryNode*& NodeToDelete);

	void Preorder() const;
	void Inorder() const;
	void Postorder() const;

	bool IsFull() const;
	bool IsEmpty() const;

	int GetNumberOfElements() const;

private:

	//Data Members

	BinaryNode* Root;
	int NumberOfElements;

	//Helper functions

	BinaryNode*& FindNode(int SearchingValue, BinaryNode*& SearchingNode);

	void PrintPreorder(BinaryNode* Current) const;
	void PrintInorder(BinaryNode* Current) const;
	void PrintPostorder(BinaryNode* Current) const;

	void MakeEmpty(BinaryNode*& Current);

};
