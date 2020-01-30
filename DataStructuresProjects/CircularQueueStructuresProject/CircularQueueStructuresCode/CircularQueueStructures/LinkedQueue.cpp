
#include "LinkedQueue.h"
#include <iostream>

//Precondition: List is not initialized, object created in "main".
//Postcondition: List object initialized with correct settings.
LinkedQueue::LinkedQueue(bool DeveloperSetting) {

	//Head starts as NULL (no elements).
	Head = 0;

	//Determines whether to display DeveloperMode visualization or not.
	DeveloperMode = DeveloperSetting;

}

//Precondition: List is initialized, goes out of scope.
//Postcondition: All list memory is deallocated, list is freed up.
LinkedQueue::~LinkedQueue() {

	MakeEmpty();

}

//Precondition: List is initialized and not full.
//Post condition: New node will become the head of the list.
void LinkedQueue::Enqueue(int Value) {

	//Put at front - easier for visualize function

	QueueNode* NewNode = new QueueNode;

	NewNode->NodeValue = Value;
	NewNode->Next = 0;

	if (IsEmpty()) {

		//If Head is null, the NewNode is the head.
		Head = NewNode;

	} else {

		//If there is already an element in the linked list.

		QueueNode* TraversingNode = Head; //Used for looping through while loop.

		while (TraversingNode->Next != 0) {

			//Cycle until we reach last node.
			TraversingNode = TraversingNode->Next;

		}

		TraversingNode->Next = NewNode; //Connect NewNode so that NewNode is the end of the queue.

	}

}

//Precondition: List is initilaized and is not empty.
//Postcondition: Oldest element in linked list is dequeued, deallocated, and removed.
void LinkedQueue::Dequeue() {

	QueueNode* ToDelete = Head; //Will be deleting head (oldest element).

	Head = Head->Next; //Reallign the head to be the next node.

	delete ToDelete; //Delete old head.

}

//Precondition: Linked List is initialized.
//Postcondition: List unchanged, checked whether maximum capacity has been reached.
bool LinkedQueue::IsFull() const {

	QueueNode* TempNode;

	try {

		//Try to create new node. If no error, we still have storage space.
		TempNode = new QueueNode;
		delete TempNode;

		return false;

	}

	catch (std::bad_alloc exception) {

		//If error, catch error and record that the list has reached maximum capacity.
		return true;

	}

}

//Precondition: List is initialized.
//Postcondition: List is determined to be empty or not empty. List unchanged.
bool LinkedQueue::IsEmpty() const {

	//If the "Head" pointer isn't pointing to anything (pointing to NULL), the list is empty.
	return (Head == 0);

}

//Precondition: List is initialized.
//Postcondition: List is displayed in a queue form to the user. List is unchanged.
void LinkedQueue::Visualize() const {

	if (IsEmpty()) {

		//If empty, tell the user.
		std::cout << "The queue is currently empty.\n\n";

	} else {

		//If not empty, we visualize.
		std::cout << "This is the current queue: \n\n";

		std::cout << "\t| ";

		QueueNode* Location;

		Location = Head;

		while (Location != 0) {

			std::cout << Location->NodeValue << " | ";

			Location = Location->Next;

		}

		std::cout << "\t\n\n";

		if (DeveloperMode) {

			//Wont display if empty or DeveloperMode is off.
			DeveloperVisualize();

		}

	}

}

//Precondition: List is initialized.
//Postcondition: List displayed in a more clearly "Linked List" structure. List unchanged.
void LinkedQueue::DeveloperVisualize() const {

	std::cout << "\t";

	QueueNode* Location;

	Location = Head;

	while (Location != 0) {

		//Cycle through each node, starting with head, to display values.
		std::cout << "| " << Location->NodeValue << " |";

		Location = Location->Next;

		if (Location != 0) {

			std::cout << " --> ";

		} else {

			//End of list has "x" to mark pointer as NULL.
			std::cout << " x |";

		}

	}

	std::cout << "\n\n";

	std::cout << "\n\nHead Node's Value = " << Head->NodeValue << "\n\n";

}

//Precondition: Linked List is initialized and not empty.
//Postcondition: All memory deallocated, list is empty.
void LinkedQueue::MakeEmpty() {

	QueueNode* TempPointer;

	while (Head != 0) {

		//Delete Head each time until we're done
		//And move head one step further until it hits NULL

		TempPointer = Head;

		Head = Head->Next;

		delete TempPointer;

	}

}