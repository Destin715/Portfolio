/*

  StringAdder.cpp
  StringAdder

  Created by Destin Piagentini and Kevin Yonamine on 10/7/18.
  Copyright © 2018 Destin Piagentini and Kevin Yonamine. All rights reserved.

 References:

 Knowledge and use of built-in string erase function:
 http://www.cplusplus.com/reference/string/string/erase/

 Knowledge and use of built-in string insert function:
 http://www.cplusplus.com/reference/string/string/insert/

 Refresher on the theory of manual subtraction (specifically subtracting a large number from a small number):
 https://www.youtube.com/watch?v=hJWMLdDBHqw

 */

//#include "pch.h"
#include <iostream>
#include "Adder.h"

bool DetermineValid(const string& Input1, const string& Input2); //determines if the user input is valid

int main() {

	char Rerun; //For if the user wants to re-run the program
	string Input1, Input2;

	std::cout << "Welcome to the number adder!\n\n"; //A welcome message
	std::cout << "This program seeks to circumvent the maximum size of an integer value by taking the number inputs as strings.\n";
	std::cout << "By taking the number inputs as strings, we use a stepwise-refinement base approach to arrive at an answer.\n";
	std::cout << "In other words, this program can compute numbers of any length.\n\n";

		do { //Rerun loop

			do { //Input invalid

				std::cout << "A quick reminder:\n\n";//Following lines are instructions
				std::cout << "The integer must comprise entirely of digits (or a negative sign at the front).\n\n";

				std::cout << "Please enter the first integer: ";//Get the input
				std::getline(std::cin, Input1);	//Uses getline function to prevent spaces being registered as separate input
				std::cout << "Please enter the second integer: ";
				std::getline(std::cin, Input2);
				std::cout << '\n';

				if (!DetermineValid(Input1, Input2))//Check that both inputs are valid
				{
					std::cout << "Invalid inputs! Please try again.\n\n";
				}

			} while (!DetermineValid(Input1, Input2)); //Re-get input if not valid

			Adder Sum(Input1, Input2); //Instantiate object based on the inputs given by the user
			Sum.Perform(); //Calculate

			if (Sum.GetS_ENT2()[0] == '-') { //If we need to print x - y

				string TempS_ENT2 = Sum.GetS_ENT2(); //Temp variable so we can place negative sign in middle
				TempS_ENT2.erase(0, 1); //Erase negative sign from the temp varible

				std::cout << Sum.GetS_ENT1() << " - " << TempS_ENT2 << " = " <<Sum.GetS_ENT3() << "\n\n"; //Print answer with negative sign

			} else
			{ //If x + y

				std::cout << Sum.GetS_ENT1() << " + " << Sum.GetS_ENT2() << " = " <<
				Sum.GetS_ENT3() << "\n\n"; //Print the answer
			
			}


			std::cout << "Would you like to perform another calculation?\n"; //Ask to rerun
			std::cout << "(Type 'Y' or 'y', or any other key to exit): ";

			std::cin >> Rerun;
			std::cin.ignore(); //Avoid getline function errors and clear the input

		} while (Rerun == 'y' || Rerun == 'Y'); //Rerun depending on input

		return 0;
}
