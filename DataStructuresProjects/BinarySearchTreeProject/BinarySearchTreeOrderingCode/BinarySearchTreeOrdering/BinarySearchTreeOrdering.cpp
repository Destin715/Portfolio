// BinarySearchTreeOrdering.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "BinarySearchTree.h"


int main()
{

	char Input;

	//Intro

	std::cout << "Welcome to Binary Search Tree Creator!\n\n";

	std::cout << "In this program, you will be able to create and edit a binary search tree, and print its contents in three different 'orders': preorder, inorder, and postorder.\n\n";

	std::cout << "A binary search tree is a data structure in which each element can point\nto every element lower than it, and every element higher than it.\n\n";
	std::cout << "As we search for an element down the tree, we can reduce our search area by half each time by comparing what we arelooking for to a certain point on the tree.\n\n";
	std::cout << "If we are looking for an item of lesser value, we explore that point's left branch. If we are looking for an element of a higher value, we explore that trees right branch.\n\n";

	std::cout << "We can also display the cotents of the tree in different types of orders:\n\n";
	std::cout << "\tPreorder: As we move along points on the tree, the element being looked\n\tat is printed first, then we look at the element to its left,then\n\tto its right. We repeat this process until all elements are printed.\n\n";
	std::cout << "\tInorder: As we move along points on the tree, the element to the left\n\tof the element in question is looked at first, then the element\n\titself, then the element to the right. Repeat this process\n\tfor all elements, and the result will be printed in a sorted order.\n\n";
	std::cout << "\tPostorder: As we move along points on the tree, the element to the\n\tleft of the element in question is looked at first, then the element\n\tto the right is looked at, and finally the element itself is printed.\n\tWe repeat this process until all elements are printed.\n\n";

	std::cout << "Press any key to continue to the main menu: ";
	std::cin >> Input;

	do {

		BinarySearchTree Tree;

		system("CLS");

		do {

			std::cout << "Main Menu (Please type a letter based on which queue structure you'd like):\n\n\t[1] Edit Tree\n\t[2] Print Preorder\n\t[3] Print Inorder\n\t[4] Print Postorder\n\t[5] Quit\n\n";
			std::cout << "Enter here: ";
			std::cin >> Input;

			switch (Input) {

			default: {

				system("CLS");
				std::cout << "Invalid Input! Try again!\n\n";
				break;

			}

			case '1': {

				system("CLS");

				do {

					std::cout << "There are " << Tree.GetNumberOfElements() << " element(s) in the binary search tree.\n\n";

					std::cout << "Options:\n\n[A/a] Add Number\n[D/d] Delete Number\n[Q/q] Quit to Main menu\n\n";
					std::cin >> Input;

					if (Input == 'A' || Input == 'a') {

						if (Tree.IsFull()) {

							system("CLS");
							std::cout << "Error! Tree is full! Try deleting a value first!\n\n";

						} else {

							//To check if the value is already in the tree.
							BinaryNode* TempNode;

							do {

								int InputValue;

								std::cout << "Please enter a number to add: ";
								std::cin >> InputValue;

								//Create temp object so only have to run FindNodeByValue() once.
								TempNode = Tree.FindNodeByValue(InputValue);

								if (TempNode != 0) {

									//If value already exists in tree.

									system("CLS");
									std::cout << "Error! Value already in tree! Try again!\n\n";
									std::cout << "These are the values in the tree: ";
									Tree.Inorder();
									std::cout << "\n\n";


								} else {

									//If value does not already exist in tree.
									Tree.AddNode(InputValue, Tree.FindNodeByValue(InputValue));

								}

							} while (TempNode != 0);

							system("CLS");

						}

					} else if (Input == 'D' || Input == 'd') {

						if (Tree.IsEmpty()) {

							system("CLS");
							std::cout << "Error! Tree is empty! Try adding a value!\n\n";

						} else {

							//To check if the value is not in tree.
							BinaryNode* TempNode;

							bool Error;

							do {

								Error = false;

								int InputValue;

								std::cout << "Please enter a number to delete from the tree: ";
								std::cin >> InputValue;

								TempNode = Tree.FindNodeByValue(InputValue);

								if (TempNode == 0) {

									system("CLS");
									std::cout << "Error! Value not in tree! Try again!\n\n";
									std::cout << "These are the values in the tree: ";
									Tree.Inorder();
									std::cout << "\n\n";

									//We must run loop again.
									Error = true;

								} else {

									//Start at node to delete.
									Tree.DeleteNode(Tree.FindNodeByValue(InputValue));

								}

							} while (Error);

							system("CLS");

						}


					} else if (Input != 'Q' && Input != 'q') {

						system("CLS");
						std::cout << "Invalid Input! Try again!\n\n";

					}

				} while (Input != 'Q' && Input != 'q');

				system("CLS");

				break;

			}

			case '2': {

				system("CLS");

				if (Tree.IsEmpty()) {

					std::cout << "The Binary seatch tree is empty.";

				} else {

					std::cout << "Preorder: ";
					Tree.Preorder();

				}

				std::cout << "\n\nPress any key to return to the main menu: ";
				std::cin >> Input;
				system("CLS");

				break;

			}

			case '3': {

				system("CLS");

				if (Tree.IsEmpty()) {

					std::cout << "The Binary seatch tree is empty.";

				} else {

					std::cout << "Inorder: ";
					Tree.Inorder();


				}

				std::cout << "\n\nPress any key to return to the main menu: ";
				std::cin >> Input;
				system("CLS");

				break;

			}

			case '4': {

				system("CLS");

				if (Tree.IsEmpty()) {

					std::cout << "The Binary seatch tree is empty.";

				} else {

					std::cout << "Postorder: ";
					Tree.Postorder();


				}

				std::cout << "\n\nPress any key to return to the main menu: ";
				std::cin >> Input;
				system("CLS");

				break;

			}

			case '5': {

				system("CLS");
				break;
				//Needed so default case doesn't run when 5 is hit.

			}

			}

		} while (Input != '5');

		//Ask to start over with new Tree.

		std::cout << "Would you like to start again with a new tree? (Type 'Y' or 'y' for yes): ";
		std::cin >> Input;

		std::cout << "\n\n";

	} while (Input == 'Y' || Input == 'y');

}
