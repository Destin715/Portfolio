//
//  MainFunctions.cpp
//  StringAdder
//
//  Created by Destin Piagentini and Kevin Yonamine on 10/7/18.
//  Copyright © 2018 Destin Piagentini and Kevin Yonamine. All rights reserved.
//

//#include "pch.h"
#include <iostream>

using std::string;

/*
Check to see if inputs are valid. Invalid if character is not a digit or -. There can only be one - and it must be the first char
*/
bool DetermineValid(const string& Input1, const string& Input2)
{

	//2 loops in case the inputs are not the same length
	for (int i = 0; i < Input1.length(); i++)//first string
	{

		//using ASCII, the digits must be between 48 and 57. 48 is 0 and 57 is 9. if not, then the character is invalid
		//if negative sign is not in front or there is invalid character
		if ((Input1[i] == '-' && i != 0) || (Input1[i] != '-' && (int(Input1[i]) < 48 || int(Input1[i]) > 57)))
		{
			
			return false;
		
		}

	}

	for (int j = 0; j < Input2.length(); j++)//second string
	{
		//using ASCII, the digits must be between 48 and 57. 48 is 0 and 57 is 9. if not, then the input is invalid
		if ((Input2[j] == '-' && j != 0) || (Input2[j] != '-' && (int(Input2[j]) < 48 || int(Input2[j]) > 57)))
		{

			return false;

		}

	}

	return true; //If we made it this far, we know both inputs are valid.

}
