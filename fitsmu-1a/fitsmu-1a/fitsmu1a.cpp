// Project 1a
//
// Team: fitsmu
// Justin Fitch
// Sam Smucny
//
// fitsmu1a.cpp : Defines the entry point for the console application.
// This is the Mastermind game
// The Codemaker will create a secret code based on the input from the
// code breaker
//
// The Codebreaker must enter 2 digits:
//  - One defining the code length
//  - Another defining the range of digits
// The Codebreaker will then have 10 guesses to enter the secret code
// After each guess the Codemaker will output 2 digits
//  - One telling how many digits were in the correct place
//  - Another telling how many correct digits were in the wrong place

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include "code.h"

// Main function, entry point for application
int main()
{
   // Seed the random funtion with the time of execution
	 srand(time(NULL));

   // Accept user Input and create secret code object
   std::cout << "Welcome to the MASTERMIND Game!\n";

   // Instantiate code object - 5 digits long and max digit of 9
   code secretCode = code(5,9);

   // Print out the secret code
	 secretCode.printCode();

   // Create User code object with guess as secret
	 auto a = secretCode.checkUserInput(code({ 5,0,3,2,6 }, 9));
	 auto b = secretCode.checkUserInput(code({ 2,1,2,2,2 }, 9));
	 auto c = secretCode.checkUserInput(code({ 1,3,3,4,5 }, 9));

   // Print out user code and comparison output
	 std::cout << "5, 0, 3, 2, 6  (" << a.correctDigitCorrectPlacement << ", " <<
     a.correctDigitIncorrectPlacement << ")" << std::endl;

   std::cout << "2, 1, 2, 2, 2  (" << b.correctDigitCorrectPlacement << ", " <<
     b.correctDigitIncorrectPlacement << ")" << std::endl;

   std::cout << "1, 3, 3, 4, 5  (" << c.correctDigitCorrectPlacement << ", " <<
     c.correctDigitIncorrectPlacement << ")" << std::endl;

   // Wait for user input to end program
	 std::cin.get();
}
