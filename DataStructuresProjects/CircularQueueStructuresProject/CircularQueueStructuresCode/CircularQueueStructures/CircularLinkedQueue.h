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

//CircularLinkedQueue - Class Interface 
class CircularLinkedQueue {
public:

	//Constructor/Destructor
	CircularLinkedQueue(bool DeveloperSetting = true); //Default parameter, so this is default constructor.
	~CircularLinkedQueue();

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

	//Data Members

	//Points to Head of linked list
	QueueNode* Head;
	//Determines whether to run DeveloperVisualize() or not
	bool DeveloperMode;

	//Helper Functions
	void DeveloperVisualize() const; //Special diagram for DeveloperMode
	//Makes the list empty upon deconstruction.
	void MakeEmpty();

};



