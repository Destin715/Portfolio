#pragma once

//Header guards so QueueNode isn't defined twice between LinkedQueue.h and CircularLinkedQueue.h
#ifndef STRUCTNODE
#define STRUCTNODE

//The struct interface each node in the Linked List uses
struct QueueNode {

	int NodeValue;
	QueueNode* Next;

};

#endif

//LinkedQueue - Class Interface 
class LinkedQueue {

public:

	//Constructor/Destructor
	LinkedQueue(bool DeveloperSetting = true); //Default parameter, so this is default constructor.
	~LinkedQueue();

	//Functions

	//Functions that will directly alter the list
	//Add an element (Enqueue) or remove an element (Dequeue). 
	void Enqueue(int Value);
	void Dequeue();

	//Checks if the list is Full/Empty respectively.
	bool IsFull() const;
	bool IsEmpty() const;

	//Visualization for the user.
	void Visualize() const;

private:


	//Points to Head of linked list
	QueueNode* Head;
	//Determines whether to run DeveloperVisualize() or not
	bool DeveloperMode;

	//Helper Functions

	//Special diagram for DeveloperMode.
	void DeveloperVisualize() const;
	//Makes the list empty upon deconstruction.
	void MakeEmpty();

};

