/** fitsmu1a.cpp : Defines the entry point for the console application.
* This is the Mastermind game
* The Codemaker will create a secret code based on the input from the code breaker
* The Codebreaker must enter 2 digits:
*   - One defining the code length
*   - Another defining the range of digits
* The Codebreaker will then have 10 guesses to enter the secret code
* After each guess the Codemaker will output 2 digits
*  - One telling how many digits were in the correct place
*  - Another telling how many correct digits were in the wrong place
*/

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include "code.h"

code acceptInput();

// Main for part A
int main()
{
	// Seed the random funtion with the time of execution
	srand(time(NULL));

	// Accept user Input and create secret code object
	std::cout << "Welcome to the MASTERMIND Game!\n";
	code secretCode = code(5,9);

	secretCode.printCode();
	auto a = secretCode.checkUserInput(code({ 5,0,3,2,6 }, 9));
	auto b = secretCode.checkUserInput(code({ 2,1,2,2,2 }, 9));
	auto c = secretCode.checkUserInput(code({ 1,3,3,4,5 }, 9));

	std::cout << "5, 0, 3, 2, 6  (" << a.correctDigitCorrectPlacement 
		<< ", " << a.correctDigitIncorrectPlacement << ")" << std::endl;
	std::cout << "2, 1, 2, 2, 2  (" << b.correctDigitCorrectPlacement 
		<< ", " << b.correctDigitIncorrectPlacement << ")" << std::endl;
	std::cout << "1, 3, 3, 4, 5  (" << c.correctDigitCorrectPlacement 
		<< ", " << c.correctDigitIncorrectPlacement << ")" << std::endl;

	std::cin.get();
}

code acceptInput()
{

	int codeLength;
	int maxDigit;

	std::cout << "Please enter the desired length of the secret code: ";
	std::cin >> codeLength;
	std::cout << "Please enter the maximum digit you want to be in the secret code: ";
	std::cin >> maxDigit;

	if (codeLength <= 0 || maxDigit <= 0)
	{
		std::cout << "One or both of the values you entered were not valid. Please choose two non negative integers." << std::endl;
		return acceptInput();
	}
	else
	{
		return code(codeLength, maxDigit);
	}
}
