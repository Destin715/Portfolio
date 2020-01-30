// CircularStructures.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*

	Destin Piagentini
	Professor Ammari
	Data Structures

	References: https://mathbits.com/MathBits/CompSci/Introduction/clear.htm

	References: https://stackoverflow.com/questions/14669457/initialization-of-element-is-skipped-by-case-label


*/


#include "CircularArray.h"
#include "LinkedQueue.h"
#include "CircularLinkedQueue.h"
#include <iostream>
#include <stdlib.h>

int main() {

	//Initialize DeveloperMode to true.
	bool DeveloperMode = true;

	//Variable which will record the user input in menus.
	char UserChoice;

	//Instructions
	std::cout << "Welcome to the Queue Creator!\n\n";
	std::cout << "A queue is a type of datat implementation in which the first elements put in are the first to be removed.\n\n";
	std::cout << "To better understand a queue, picture a line at the grocery store.\nThe customer who's waited the longest gets served first,\nand the line keeps moving until all customers are finished.\n\n";
	std::cout << "This program will use three different data structures (of your choosing) as implementation of a queue: \n\n";
	std::cout << "\t1) Circular Array - An Array (list) where the list of elements\n\tis treated as a circle,and elements dont need to be rearranged\n\teach time, we can just rewrite the old spaces.\n\n";
	std::cout << "\t2) Linked List - A list of seperate numbers connected to eachother.\n\tThink of numbers taped to a piece of yarn! Each number is\n\tseperate, but they are all on the same line.\n\n";
	std::cout << "\t3) Circular Linked List - Same type of structure, except\n\tthe end of that yarn connects back to the first number!\n\n";
	std::cout << "Additionally, this program offers a 'Developer Mode' to help show\nhow each of the data structures work behind the scenes.\nThis can be turned on from the settings menu.\n\n";

	std::cout << "Press any key to start: ";
	std::cin >> UserChoice;

	system("CLS"); //Clear screen

	do { //Main Menu

		//Instructions.
		std::cout << "Main Menu (Please type a letter based on which queue structure you'd like):\n\n\t[1] Circular Array\n\t[2] Linked List\n\t[3] Circular Linked List\n\t[4] Settings\n\t[5] Quit\n\n";
		std::cout << "Enter here: ";
		std::cin >> UserChoice;


		switch (UserChoice) { //Main menu switch

		default: {

			//If any invalid characters are entered.
			system("CLS"); //Clear Screen
			std::cout << "Invalid option! Please Try Again!\n\n";

			break;

		}

			   //All three main cases follow similar structures (except custom user length).
			   //All notes here (except custom user length) apply to others.

		case '1': { //Case 1 - Circular Array

			system("CLS");

			int LengthInput; //Length for user generated length

			do { //Get queue length.

				std::cout << "Please enter the length of the desired circular array: ";
				std::cin >> LengthInput;
				std::cout << "\n";

				if (LengthInput < 1) { //If invalid length, we must catch it beforehand.

					std::cout << "ERROR! Invalid input! Try again!\n\n";

				}

			} while (LengthInput < 1);

			CircularArray QueueObject(LengthInput, DeveloperMode);

			do { //Each Turn Loop

				//Visualize again each time through. Screen will have been cleared prior each time.
				QueueObject.Visualize();

				std::cout << "Options:\n\n[E/e] Enque\n[D/d] Deque\n[Q/q] Quit to Main menu\n\n";

				std::cout << "Choice: ";
				std::cin >> UserChoice;

				if (UserChoice == 'd' || UserChoice == 'D') {

					//Make sure queue is not empty before dequeing

					if (!QueueObject.IsEmpty()) {

						QueueObject.Dequeue();
						system("CLS"); //Clears screen

					} else {

						//If queue is empty, we can not dequeue.
						system("CLS");
						std::cout << "ERROR: Queue is empty! Can not deque empty queue!\n\n";

					}

				} else if (UserChoice == 'e' || UserChoice == 'E') {

					//Make sure queue is not full before enqueing
					if (!QueueObject.IsFull()) {

						int ValueInput;

						//Get value to enqueue, and then enqueue to the object.
						std::cout << "Value to Queue (Integer): ";
						std::cin >> ValueInput;
						QueueObject.Enqueue(ValueInput);

						system("CLS");

					} else {

						//If queue is full, we can not enqueue.
						system("CLS");
						std::cout << "ERROR: Queue is full! Can not enque a full queue!\n\n";

					}

				} else if (UserChoice != 'q' && UserChoice != 'Q') {

					//If input is invalid.
					system("CLS");
					std::cout << "ERROR: Input not an option! Try again!\n\n";

				}

				if (UserChoice == 'q' || UserChoice == 'Q') {

					//Clear Screen before leaving.
					system("CLS");

				}

			} while (UserChoice != 'q' && UserChoice != 'Q');

			break;

		} //Circular Array - Case '1' - Needed because no redefinition of class object error

		case '2': { //Case 2 - Linked List

			system("CLS");

			LinkedQueue QueueObject(DeveloperMode);

			do {

				QueueObject.Visualize();

				std::cout << "Options:\n\n[E/e] Enque\n[D/d] Deque\n[Q/q] Quit to Main menu\n\n";

				std::cout << "Choice: ";
				std::cin >> UserChoice;

				if (UserChoice == 'd' || UserChoice == 'D') {

					if (!QueueObject.IsEmpty()) {

						QueueObject.Dequeue();
						system("CLS");

					} else {

						system("CLS");
						std::cout << "ERROR: Queue is empty! Can not deque empty queue!\n\n";

					}

				} else if (UserChoice == 'e' || UserChoice == 'E') {

					if (!QueueObject.IsFull()) {

						int ValueInput;

						std::cout << "Value to Queue (Integer): ";
						std::cin >> ValueInput;
						QueueObject.Enqueue(ValueInput);

						system("CLS");

					} else {

						system("CLS");
						std::cout << "ERROR: Queue is full! Can not enque a full queue!\n\n";

					}

				} else if (UserChoice != 'q' && UserChoice != 'Q') {

					system("CLS");
					std::cout << "ERROR: Input not an option! Try again!\n\n";

				}

				if (UserChoice == 'q' || UserChoice == 'Q') {

					//Clear Screen before leaving
					system("CLS");

				}

			} while (UserChoice != 'q' && UserChoice != 'Q');


			break;

		} //Linked List - Case '2'

		case '3': { //Case 3 - Circular Linked List

			system("CLS");

			CircularLinkedQueue QueueObject(DeveloperMode);

			do {

				QueueObject.Visualize();

				std::cout << "Options:\n\n[E/e] Enque\n[D/d] Deque\n[Q/q] Quit to Main menu\n\n";

				std::cout << "Choice: ";
				std::cin >> UserChoice;

				if (UserChoice == 'd' || UserChoice == 'D') {

					if (!QueueObject.IsEmpty()) {

						QueueObject.Dequeue();
						system("CLS");

					} else {

						system("CLS");
						std::cout << "ERROR: Queue is empty! Can not deque empty queue!\n\n";

					}

				} else if (UserChoice == 'e' || UserChoice == 'E') {

					if (!QueueObject.IsFull()) {

						int ValueInput;

						std::cout << "Value to Queue (Integer): ";
						std::cin >> ValueInput;
						QueueObject.Enqueue(ValueInput);

						system("CLS");

					} else {

						system("CLS");
						std::cout << "ERROR: Queue is full! Can not enque a full queue!\n\n";

					}

				} else if (UserChoice != 'q' && UserChoice != 'Q') {

					system("CLS");
					std::cout << "ERROR: Input not an option! Try again!\n\n";

				}

				if (UserChoice == 'q' || UserChoice == 'Q') {

					//Clear Screen before leaving
					system("CLS");

				}

			} while (UserChoice != 'q' && UserChoice != 'Q');


			break;

		} //Linked List - Case '3'

		case '4': { //Case 4 - Settings Menu

			system("CLS");

			do {

				std::cout << "Settings:\n\n";

				if (DeveloperMode) {

					std::cout << "Developer Mode is on. Would you like to turn it off?\n";
					std::cout << "Enter (Y or y) to turn off, or (Q or q) to go back to the main menu: ";

				} else {

					std::cout << "Developer Mode is off. Would you like to turn it on?\n";
					std::cout << "Enter (Y or y) to turn on, or (Q or q) to go back to the main menu: ";

				}

				std::cin >> UserChoice;

				if (UserChoice == 'y' || UserChoice == 'Y') {

					system("CLS");
					DeveloperMode = !DeveloperMode;

				} else if (UserChoice != 'q' && UserChoice != 'Q') {

					system("CLS");
					std::cout << "ERROR: Invalid input! Try again!\n\n";

				}

				if (UserChoice == 'q' || UserChoice == 'Q') {

					//Clear Screen before leaving
					system("CLS");

				}

			} while (UserChoice != 'q' && UserChoice != 'Q');

			break;

		} //Settings - Case '4'

		case '5': { //Case 5 - Exit

			//Needed so error message doesn't output, but nothing needs to be done.
			break;

		} //Exit - Case '5'

		}

	} while (UserChoice != '5');

	return 0;

}