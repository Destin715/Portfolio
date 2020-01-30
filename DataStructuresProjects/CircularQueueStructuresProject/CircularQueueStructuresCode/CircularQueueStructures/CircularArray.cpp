
#include "CircularArray.h"
#include <iostream>

//Precondition: Queue is not initialized, CircularArray object created from "main" without parameters. Default constructor.
//Postcondition: Queue is initialized with generic data values. 
CircularArray::CircularArray() {

	//Initialize data members
	MaxLength = 9;
	QueuedElements = 0;

	//Dynamic array allocated based on user's requested length.
	Queue = new int[MaxLength];

	FirstIndex = 0;
	LastIndex = 0;

	for (int i = 0; i < MaxLength; i++) {

		Queue[i] = 0; //Initialize Queue values to 0 (needed for readability in developer mode).

	}

	DeveloperMode = true;

}

//Precondtion: Queue is not initialized, CircularArray object created from "main" with length of user request.
//Postcondition: Queue is initialized with data values based on user request. 
CircularArray::CircularArray(int InputLength, bool DeveloperSetting) {

	//Initialize data members
	MaxLength = InputLength;
	QueuedElements = 0;

	//Dynamic array allocated based on user's requested length.
	Queue = new int[MaxLength];

	FirstIndex = 0;
	LastIndex = 0;

	for (int i = 0; i < MaxLength; i++) {

		Queue[i] = 0; //Initialize Queue values to 0 (needed for readability in developer mode).

	}

	DeveloperMode = DeveloperSetting;

}

//Precondition: Queue is initialized, goes out of scope.
//Postcondition: Dynamic array is deallocated to avoid memory leaks.
CircularArray::~CircularArray() {

	delete[] Queue;

}

//Precondition: Queue is initialized.
//Postcondition: Queue is displayed in a readable queue form to the user. Queue is unchanged.
void CircularArray::Visualize() const {

	std::cout << "This is the current queue: \n\n";

	std::cout << "Queue:\t| ";

	for (int i = 0; i < MaxLength; i++) {


		//Since we initialize to 0, we need to check if the 0 was entered by the user.
		//(meaning it is a memebr of the queue) or it is representing an empty space.
		if (Queue[i] == 0) {

			if (FirstIndex == LastIndex) {

				//If the indexes are on top of each other, there is either one member or no members.

				if (IsEmpty() || i != LastIndex) {

					//If empty, this is an empty element.
					//Or if the current index is not the FirstIndex/LastIndex, we know it must be empty
					//because if the two indexes are the same only that index could possible hold an element.
					std::cout << '*';

				} else if (i == LastIndex) {

					//If i is the LastIndex/FirstIndex space, only the first element is full.
					std::cout << Queue[i];

				}

			} else if (FirstIndex < LastIndex) {

				//If the array does not wrap around

				//If the 0 is not between the two indexes it is not an intended member of the queue
				if (i < FirstIndex || i > LastIndex) {

					std::cout << '*';

				} else {

					std::cout << Queue[i];

				}

			} else if (LastIndex < FirstIndex) {

				//If the indexes wrap around the queue

				//If i is out of the wrapped range
				if (i > LastIndex&& i < FirstIndex) {

					std::cout << '*';

				} else {

					std::cout << Queue[i];

				}

			}

		} else { //If any other number

			std::cout << Queue[i]; //Print as normal

		}

		std::cout << " | ";

	}

	std::cout << "\n\n";

	if (DeveloperMode) {

		//Wont display if empty or DeveloperMode is off.
		DeveloperVisualize();

	}

	std::cout << "The maximum length of the queue is " << MaxLength << ".\n\n";


}

//Precondition: Queue is initialized.
//Postcondition: Queue displayed as it is. Queue unchanged.
void CircularArray::DeveloperVisualize() const {

	for (int i = 0; i < MaxLength; i++) {

		std::cout << Queue[i] << "[" << i << "] | ";

	}

	std::cout << "\n\nFirstIndex: " << FirstIndex << "\tLastIndex: " << LastIndex << "\n\n";

}


//Precondition: Queue is initialized and is not full.
//Postcondition: Value is enqueued in the "back" of the queue.
void CircularArray::Enqueue(int Value) {

	if (!IsEmpty()) {

		//If the queue is empty, the index's will be on top of each other.
		//If they are, we can just add the new element in that place.
		//If not, we add it to the next spot (we need to alter LastIndex).

		if (LastIndex != MaxLength - 1) {

			//If we dont need the index counter to circle back.

			LastIndex++;

		} else {

			LastIndex = 0;

		}

	}

	//Add the new value tot he proper index plcace, update counter variable.
	Queue[LastIndex] = Value;
	QueuedElements++;


}

//Precondition: Queue is initialized and is not Empty.
//Postcondition: Least recent element is removed from the queue.
void CircularArray::Dequeue() {

	Queue[FirstIndex] = 0; //Set removed element back to 0.

	if (LastIndex != FirstIndex) {

		//If there was more than one element left before dequeing 
		//We need to update FIrstIndex.
		//(If there was only one element, the indexes would be
		//on top of eachother).

		if (FirstIndex != MaxLength - 1) {

			//If we dont need the index counter to circle back.

			FirstIndex++;

		} else {

			//If we need FirstIndex to circle back to the front.
			FirstIndex = 0;

		}

	}

	//Update counter.
	QueuedElements--;

}

//Precondition: Queue is initialized.
//Postcondition: Queue is determined to be empty/not empty. Queue unchanged.
bool CircularArray::IsEmpty() const {

	return (QueuedElements == 0);

}

//Precondition: Queue is initialized.
//Postcondition: Queue is determined to be full/not full. Queue unchanged.
bool CircularArray::IsFull() const {

	if (LastIndex == MaxLength - 1 && FirstIndex == 0) {

		//If the two index trackers are at opposite ends but circularly next to eachother.
		return true;

	} else {

		//Else, if full, Last will be one behind first.
		return (LastIndex == FirstIndex - 1);

	}

}
