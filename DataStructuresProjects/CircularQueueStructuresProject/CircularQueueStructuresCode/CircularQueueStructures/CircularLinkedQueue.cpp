
#include "CircularLinkedQueue.h"
#include <iostream>

//Precondition: List is not initialized, object created in "main".
//Postcondition: List object initialized with correct settings.
CircularLinkedQueue::CircularLinkedQueue(bool DeveloperSetting) {

	//Head starts as NULL (no elements).
	Head = 0;

	//Determines whether to display DeveloperMode visualization or not.
	DeveloperMode = DeveloperSetting;

}

//Precondition: List is initialized, goes out of scope.
//Postcondition: All list memory is deallocated, list is freed up.
CircularLinkedQueue::~CircularLinkedQueue() {

	MakeEmpty();

}

//Precondition: List is initialized and not full.
//Post condition: New node will become the head of the list.
void CircularLinkedQueue::Enqueue(int Value) {

	//"Main" ensures list is not full before calling.

	QueueNode* NewNode;

	NewNode = new QueueNode;

	//Load the new node with the user's value.
	NewNode->NodeValue = Value;

	if (IsEmpty()) {

		//If empty, create node pointing to self.
		NewNode->Next = NewNode;

		Head = NewNode;

	} else {

		//Since NewNode will be at the end, NewNode circles back to head.
		NewNode->Next = Head;

		QueueNode* TempLocater;

		TempLocater = Head;

		//Loop won't run if one element, but that means we've already found our last node.
		while (TempLocater->Next != Head) {

			//Go until we find the node that circles back to head, or the "last" node in the linked list
			TempLocater = TempLocater->Next;

		}

		//Circle back to new head.
		TempLocater->Next = NewNode;

	}

}

//Precondition: List is initilaized and is not empty.
//Postcondition: Oldest element in linked list is dequeued, deallocated, and removed.
void CircularLinkedQueue::Dequeue() {

	QueueNode* ToDelete = Head; //We will be deleting the head.

	//We need to find rear to make it circle to the node after head.
	QueueNode* RearLocater = Head;

	while (RearLocater->Next != Head) {

		//Cycle until we find the node before head (the linked list rear).
		RearLocater = RearLocater->Next;

	}

	if (Head->Next == Head) {

		//If circles back to itself (only one element)

		delete ToDelete; //Delete the head.

		Head = 0; //Set Head to null.

	} else {

		Head = Head->Next; //Update new Head

		RearLocater->Next = Head; //Circle back to new Head.

		delete ToDelete; //Delete old Head.

	}

}

//Precondition: List is initialized.
//Postcondition: List is determined to be full or not full. List unchanged.
bool CircularLinkedQueue::IsFull() const {

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
bool CircularLinkedQueue::IsEmpty() const {

	//If head is NULL, we know there are no elements.
	return (Head == 0);

}

//Precondition: List is initialized.
//Postcondition: List is displayed in a queue form to the user. List is unchanged.
void CircularLinkedQueue::Visualize() const {

	//If empty, tell the user.
	if (IsEmpty()) {

		std::cout << "The queue is currently empty.\n\n";

	} else {

		//If not empty, we visualize.
		std::cout << "This is the current queue: \n\n";

		std::cout << "\t| ";

		QueueNode* Location;

		Location = Head;

		do {

			//Run once and go until We encoutner the Head again.
			std::cout << Location->NodeValue << " | ";

			Location = Location->Next;

		} while (Location != Head);

		std::cout << "\t\n\n";

		if (DeveloperMode) {

			//Wont display if empty or DeveloperMode is off.
			DeveloperVisualize();

		}

	}

}

//Precondition: List is initialized.
//Postcondition: List displayed in a more clearly "Linked List" structure. List unchanged.
void CircularLinkedQueue::DeveloperVisualize() const {

	std::cout << "\t";

	QueueNode * Location;

	Location = Head;

	std::cout << " --> ";

	if (Location->Next == Head) {

		//If there is only one element (head points to itself), the loop will not run,
		//So we make sure to still print the singular node value.
		std::cout << "| " << Location->NodeValue << " |";

	}

	while (Location->Next != Head) {

		//Print value at node
		std::cout << "| " << Location->NodeValue << " |";

		//Cycle through to next node
		Location = Location->Next;

		if (Location->Next != Head) {

			//If we
			std::cout << " --> ";

		} else {

			//Loop will exit after this, so make sure to print last result.
			//(This is the node that circles back to Head).
			std::cout << " --> | " << Location->NodeValue << " |";

		}

	}


	std::cout << " --> \n\n";

	//Extra data to prove linked list is circular.
	std::cout << "\n\nHead Node's Value = " << Head->NodeValue << "\n";
	std::cout << "Head Node Location = " << Head << "\nNode Before Head Location = " << Location << "\nNode Before Head's ->Next Location = " << Location->Next << "\n\n";


}

//Precondition: Linked List is initialized and not empty.
//Postcondition: All memory deallocated, list is empty.
void CircularLinkedQueue::MakeEmpty() {

	if (IsEmpty()) {

		//Check to make sure it isn't already empty.
		return;

	} else {

		//Temp pointer will cycle through, move head forward, and delete whats at spot.
		//Will also be used to make the last element point to NULL instead of head, so
		//we know where to stop when it's time to delete (instead of readjusting the 
		//end pointer, which is suppsed to point to head, of the linked list each time).
		QueueNode* TempPointer;

		TempPointer = Head;

		while (TempPointer->Next != Head) {

			TempPointer = TempPointer->Next;

		}

		TempPointer->Next = 0; //Seal up the last node so we know when to stop.

		while (Head != 0) {

			//Delete Head each time until we're done
			//And move head one step further until it hits NULL
			TempPointer = Head;

			Head = Head->Next;

			delete TempPointer;

		}

	}

}