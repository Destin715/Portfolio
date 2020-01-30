//
//  Adder.cpp
//  StringAdder
//
//  Created by Destin Piagentini and Kevin Yonamine on 10/7/18.
//  Copyright © 2018 Destin Piagentini and Kevin Yonamine. All rights reserved.
//

//#include "pch.h"
#include "Adder.h"

//Default constructor.
//Runs when no inputs are given.
//Initializes each variable to generic values.
//Included for good programming practice.
Adder::Adder() {

	S_ENT1 = "0";
	S_ENT2 = "0";
	S_ENT3 = "0";

}

//Constructor that accepts two number strings (strings consisting of only numbers and/or a negative sign at the beginning)
//Sets variables to the values of the two inputs.
//The two inputs are stripped of extraneous zeroes (zeroes at the beginning of a number that do not effect its value)
//for human readability and program readability.
//Note: The two variables were already determined valid in the "main" function.
//@params string Input1, Input2: The user input of numbers in the form of strings.
Adder::Adder(const string& Input1, const string& Input2) {

	S_ENT1 = RemoveExtraneousZeros(Input1);
	S_ENT2 = RemoveExtraneousZeros(Input2);
	S_ENT3 = "";

}

/*Function that removes extra zeros at the start of number that don't change the value
 For readability of program and functionality when using the program
@param string Input: The string of the number to remove zeros from
*/
string Adder::RemoveExtraneousZeros(string Input)
{
	bool OriginallyNegative = false;//if the number is negative at the start, we need to make it negative at the end

		if (Input[0] == '-') { //if number is negative

			Input.erase(0, 1); //erase the element at 0 which is the negative sign, so that we get the number by itself
			OriginallyNegative = true; //set the boolean to true so we know that the number was negative at the beginning

		} 
		
		while (Input[0] == '0' && Input.length() >= 2) { //if the first character is 0 then remove it.the length will be at minimum, 2 so that last digit always kept
				
			Input.erase(0, 1); //erase extra 0 from front of string
		
		}
		
		if (OriginallyNegative) { //if the number was negative at the start
			
			Input.insert(0, 1, '-');//insert in the 0 position, length 1, the character -; meaning a negative sign before the number
		
		}
		return Input; //Return the altered string.
}

/*
Function used to perform the calculation.
Called in the "main" function.
First decides which case to execute based on the result of the "CaseHandler" function.
Performs the appropriate case.

TwoPositive: Both numbers positive. Add as normal.

TwoNegative: Two negative numbers. Technically subtraction, but same result
achieved by removing both negative signs, adding as normal, place negative sign on answer.

OnePositiveOneNegative: Two numbers with different signs.
First we find the absolute largest digit (largest number regardless of negative/positive status).
Then, we remove the negative signs and subtract (adding two numbers of opposite signs is the same as subtraction).
The difference between the two numbers will always be the same. The question is whether the difference is negative or not.
If the larger number was negative, the difference will be negative.
If the larger number was positive, the answer will still be positive.
If equal, the two will cancel eachother out.

By the end of this function, S_ENT3 will be appropriately calculated.
*/
void Adder::Perform() {

	//Make temporary variables based on the real variables so we can alter the temporaries without changing the real variables.
	string Reverse1 = S_ENT1, Reverse2 = S_ENT2;

	CaseHandler Result = DecideCase(); //Decide what case to run by running the DecideCase function.

	switch (Result) {

		//Case both numbers are positive
		case TwoPositive:

			//Reverse
			ReverseString(Reverse1);
			ReverseString(Reverse2);

			//Compute

			AddDigitsFromReverse(0, Reverse1, Reverse2, false);

			//Reverse answer
			ReverseString(S_ENT3);

			break;

			//Case both numbers are negative
			//Adding two negative numbers = Remove negative signs, add as normal, place negative sign on answer.

		case TwoNegative:
			
			//RemoveNeg

			Reverse1.erase(0, 1);//Erase first char (which is '-')
			Reverse2.erase(0, 1);

			//Reverse

			ReverseString(Reverse1);
			ReverseString(Reverse2);

			//Add

			AddDigitsFromReverse(0, Reverse1, Reverse2, false);

			//ReverseAnswer

			ReverseString(S_ENT3);

			//PutNeg

			S_ENT3.insert(0, 1, '-');

			break;

		case OnePositiveOneNegative:

			//Used to keep track of which number is larger, which is negative.
			int Negative, Largest;

			//Determine which is negative, and erase the negative sign (in preparation of comparisonand subtraction)

			if (Reverse1[0] == '-') {

				Reverse1.erase(0, 1);
				Negative = 1;

			} else { //If not 1, then 2

				Reverse2.erase(0, 1);
				Negative = 2;

			}

			//Compare

			//1 = First number is largest, 2 = Seocnd number is largest, 3 = Values are equal

			Largest = LargestDigits(Reverse1, Reverse2);

			//Reverse

			ReverseString(Reverse1);
			ReverseString(Reverse2);

			//Cases

			if (Largest == 1) {

				//Place larger number on top.Then subtract.
				SubtractDigitsFromReverse(0, Reverse1, Reverse2, false);
				ReverseString(S_ENT3);
				S_ENT3 = RemoveExtraneousZeros(S_ENT3); //Without this, will produce extra 0s if sizes are different(Ex: 1000 + -1001 = -0001).

				//If the largest number was negative, we know the answer is negative.If not, a smaller number was subtracted from a larger number, which results in a positive answer.
				if (Negative == 1) {

					S_ENT3.insert(0, 1, '-'); //If larger number was negative, insert negative sign into answer.

				}

			} else if (Largest == 2) {

				//Place larger number on top. Then subtract.
				SubtractDigitsFromReverse(0, Reverse2, Reverse1, false);
				ReverseString(S_ENT3);
				S_ENT3 = RemoveExtraneousZeros(S_ENT3);

				//If the largest number was negative, we know the answer is negative. If not, a smaller number was subtracted from a larger number, which results in a positive answer.
				if (Negative == 2) {

					S_ENT3.insert(0, 1, '-'); //If larger number was negative, insert negative sign into answer.

				}

			} else if (Largest == 3) {

				//If they are equal, they cancel eachother out.
				S_ENT3 = "0";

			}

			break;

		}

}

//Function utilizes enum in the class to tell the "perform" function which case to execute.
//Checks for negative signs in front of both numbers, or either number, and if not then determines neither are negative.
//Note: Numbers already determined valid. We know negative signs must be in proper place, (in front) if they exist.
Adder::CaseHandler Adder::DecideCase() const {

	//Check for - and - or + and -
	if (S_ENT1[0] == '-' && S_ENT2[0] == '-') {

		return TwoNegative;

	} else if (S_ENT1[0] == '-' || S_ENT2[0] == '-') { //If both are not negative, check if just one is.

		return OnePositiveOneNegative;

	}

	return TwoPositive; //All other cases have been tested.

}

//Takes an input string, and reverses it in preperation for addition or subtraction, 
//or to reverse the solution since it will be calculated in reverse order.
//@param string Reverse: string to be reversed.
void Adder::ReverseString(string& Reverse) {

	string TempString = "";

	for (int i = Reverse.length() - 1; i >= 0; i--) {

		TempString = TempString + Reverse[i];

	}

	Reverse = TempString;

}

/*
Addition function. Takes two number strings (order doesnt matter) and adds them via recursion and focusing on one number place at a time.
Calls itself, each time moving one number place forward.
If the sum of the two digits in a given place exceeds 9, function will record that the next number place needs to apply a carry.
Adds to S_ENT3 in reverse order. S_ENT3 reversed in "Perform" function to negate this effect.

@Params const int & DigitPlace: index of the digits of both functions in focus.
const string & Reverse1, Reverse2: Numbers (which have already been reversed) to be added together
bool CarryOver: Determines (based on the previous recursive run) if a carry (+1) needs to be applied to the current digit at the current index

*/
void Adder::AddDigitsFromReverse(const int& DigitPlace, const string& Reverse1, const string& Reverse2, bool CarryOver) {

	//A negative number will never be entered here, so we dont need to check for it.

	//Temp variables. 
	//Digit1 = first number's digit, Digit2 = second number's digit, Digit3 = the sum of the two when we calculate it.
	int Digit1, Digit2, Digit3;

	if (DigitPlace < Reverse1.length() && DigitPlace < Reverse2.length()) { //If both are still in play.

		Digit1 = int(Reverse1[DigitPlace]) - 48; //0 ASCII is 48, 9 is 57. - 48 to the digits int() means we get the digits int value.
		Digit2 = int(Reverse2[DigitPlace]) - 48;

	} else if (DigitPlace >= Reverse1.length() && DigitPlace < Reverse2.length()) { //If Reverse1 is at its end but not Reverse2.

		Digit1 = 0; //Treat a digit place that is larger than the digit length as a 0.
		Digit2 = int(Reverse2[DigitPlace]) - 48;

	} else if (DigitPlace < Reverse1.length() && DigitPlace >= Reverse2.length()) { //If Reverse2 is at its end but not Reverse2.

		Digit1 = int(Reverse1[DigitPlace]) - 48;
		Digit2 = 0; //Treat a digit place that is larger than the digit length as a 0.

	} else if (DigitPlace >= Reverse1.length() && DigitPlace >= Reverse2.length() && CarryOver == true) { //If both are at their end but we still need to carry one over

		S_ENT3 = S_ENT3 + '1'; //Add the carry to the end (or the front after reversal).
		return; //End recursion - WE ARE DONE

	} else { //If both are at their end (and no carry to apply).

		return; //End recursion - WE ARE DONE

	}

	//Apply a carry if needed.
	if (CarryOver == true) {

		Digit1 = Digit1 + 1;

	}

	Digit3 = Digit1 + Digit2; //Add the two to calculate this number places value.

	if (Digit3 > 9) { //If we need to apply a carry to the next number place

		Digit3 = Digit3 - 10; //We will add one to the next number place to account for this ten.For now, we want to get the digit back to single digits.
		CarryOver = true; //Record that we need to apply a carry next.

	} else { //If we dont need to apply a carry next pass through.

		CarryOver = false;

	}

	//Record the value. + 48 to get proper ASCII of the digit.
	S_ENT3 = S_ENT3 + char(Digit3 + 48); // 0 + 48 = ASCII of 48 = '0'. 9 + 48 = ASCII of 57 = '9'

	//Call function again for next digit place with correct CarryOver value.
	return AddDigitsFromReverse(DigitPlace + 1, Reverse1, Reverse2, CarryOver);

}

/*
 Function determines which input is larger based on absolute value. Ignores negative numbers because they will be positive when this function is used.
 Returns 1 if first input is larger, 2 if second input is larger, if they are equal returns 3
 */
int Adder::LargestDigits(const string& Reverse1, const string& Reverse2)
{

	if (Reverse1.length() > Reverse2.length()) { //if one has a longer length we know it is the larger number(extra zeros at the start have already been removed)
		
		return 1;

	} else if (Reverse2.length() > Reverse1.length()) { //same for the second input

		return 2;

	} else { //if the numbers are the same length it does not imply the same value

		int i = 0; //start at first DigitPlace

		do {//Get int value and compares

			int Digit1 = int(Reverse1[i] - 48);
			int Digit2 = int(Reverse2[i] - 48);

			if (Digit1 > Digit2) { //run until we find a digit that is not equal. We can now find which is larger

				return 1;

			} else if (Digit2 > Digit1) {

				return 2;

			}

			i++;

		} while (i < Reverse1.length());

		return 3; //if it exits loop without returning already, we know they are equal

	}
}

/*
Subtraction function taking in 2 strings(Larger first) and subtracts them using recursion. Used if one number is positive and the other is negative.
Calls itself, each repetition moves one digit forward
If the difference of the 2 digits in a given place is less than 0, function records that the next number place needs to borrow
Adds S_ENT3 in reverse order
*/
void Adder::SubtractDigitsFromReverse(const int& DigitPlace, const string& LargestReverse, const string& SmallestReverse, bool ApplyBorrow)
{
	//Digit1 = larger number's digit, Digit2 = smallest numbers digit, Digit3 = the difference

	int Digit1, Digit2, Digit3;//temporary

	if (DigitPlace < LargestReverse.length() && DigitPlace < SmallestReverse.length()) {

		Digit1 = int(LargestReverse[DigitPlace]) - 48; //in ASCII 0 is 48, 9 is 57
		Digit2 = int(SmallestReverse[DigitPlace]) - 48;

	} else if (DigitPlace < LargestReverse.length() && DigitPlace >= SmallestReverse.length()) {
		
		Digit1 = int(LargestReverse[DigitPlace]) - 48;
		Digit2 = 0;

	} else if (DigitPlace >= LargestReverse.length()) { //no need to check the smaller, if doesn't apply to larger, it wont apply to the smaller

		return;

	}

	if (ApplyBorrow == true) { //need borrow

		Digit1 = Digit1 - 1; //the borrowing subtracts 1 from the top

	}

	Digit3 = Digit1 - Digit2; //subtract

	if (Digit3 < 0) { //if difference is less than 0, borrow from the next position

		Digit3 = Digit3 + 10; //borrow makes the digit above 0
		ApplyBorrow = true; //borrow applied

	} else {

		ApplyBorrow = false;

	}

	S_ENT3 = S_ENT3 + char(Digit3 + 48); //set the value to 48 higher to get the actual value in ASCII

	return SubtractDigitsFromReverse(DigitPlace + 1, LargestReverse, SmallestReverse, ApplyBorrow); //Call function again with ApplyBorrow bool

}
