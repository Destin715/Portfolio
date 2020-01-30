#pragma once

//CircularArray - Class Interface 
class CircularArray {
public:

	//Constructors/Destructor
	CircularArray(); //Default Constructor
	CircularArray(int InputLength, bool DeveloperSetting = true);
	~CircularArray();

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

	//Queue is the dynamic array to hold the queue.
	//The index variables used to enforce ciruclar structure,
	//Keeping track of where the queue "starts" and ends based on user action.
	int* Queue;
	int FirstIndex;
	int LastIndex;

	//QueuedElements maintained to determine if list is empty (0 elements).
	//MaxLength used to help determine if full. MaxLength determined by the user.
	int QueuedElements;
	int MaxLength;

	//Determines whether to run DeveloperVisualize() or not
	bool DeveloperMode;

	//Helper Functions

	//Visualizes the array itself (not in queue visual structure) as part of Developer Mode.
	void DeveloperVisualize() const;

};

