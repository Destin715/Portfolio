//
//  Adder.h
//  StringAdder
//
//  Created by Destin Piagentini and Kevin Yonamine on 10/7/18.
//  Copyright © 2018 Destin Piagentini and Kevin Yonamine. All rights reserved.
//
//  This file contains the class interface for the "Adder" class.

#pragma once

#include <iostream>
#include <string>

using std::string;

class Adder {
public:

	Adder(); //Default constructor - Included just for good programming practice
	Adder(const string& Input1, const string& Input2); //Constructor accepting two strings to use as the calculations(already confirmed as valid inputs).

	void Perform(); //Function used by the "main" function to initiate the calculation.

	//Accessor function for the variable that stores the first input. Used by "main" function to print the solution.
	string GetS_ENT1() const {

		return S_ENT1;

	}

	//Accessor function for the variable that stores the second input.. Used by "main" function to print the solution.
	string GetS_ENT2() const {

		return S_ENT2;

	}

	//Accessor function for the variable that stores the solutuion. Used by "main" function to print the solution.
	string GetS_ENT3() const {

		return S_ENT3;

	}

private:

	string S_ENT1, S_ENT2, S_ENT3; //Variables used to store two inputs and answer

	enum CaseHandler { TwoPositive, OnePositiveOneNegative, TwoNegative }; //Enum to decide which case the inputted numbers meet.

	//Removes any additional zeroes before a number for better readability by both userand program.
	string RemoveExtraneousZeros(string Input);

	CaseHandler DecideCase() const; //Function used to decide which case the "Perform" function needs to execute.

	void ReverseString(string& Reverse); //Used to reverse numbers in preparation for addition / subtraction.

	//Function to add two number strings once they have been reversed. RECURSIVE
	void AddDigitsFromReverse(const int& DigitPlace, const string & Reverse1, const string & Reverse2, bool CarryOver);

	//Used to find the largest digit regardless of positive/negative status.
	int LargestDigits(const string& Reverse1, const string& Reverse2);

	//Function used to subtract two number strings via reverse).
	//Largest digit gets put on "top" (goes first).
	void SubtractDigitsFromReverse(const int& DigitPlace, const string&
	LargestReverse, const string& SmallestReverse, bool ApplyBorrow);

};
