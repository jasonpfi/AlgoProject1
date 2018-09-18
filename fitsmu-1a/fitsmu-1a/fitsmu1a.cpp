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

//#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>

// Structure defining the output of checking the user code input
//  compared to the secret code
// correctDigitCorrectPlacement: how many digits were guessed in the
//                                correct positions
// correctDigitIncorrectPlacement: how many digits were guessed
//                                  correctly in the incorrect positions
struct codeGuess {
	int correctDigitCorrectPlacement;
	int correctDigitIncorrectPlacement;
};

// Main class defining a code, secret or user input
// A code is defined by its length and the value of
//  the maximum digit, as well as a vector defining the code
class code {
	int codeLen;
	int maxDig;
	std::vector<int> secret;

public:

	code();
	code(int codeLen, int maxDig);

	void generateSecretCode();
	void printCode();
	code generateUserCode();
	bool checkValidity();
	codeGuess checkUserInput(const code& userCode);
	bool checkWin(const codeGuess& codeGuessOutput);
};

// Empty Constructor
code::code() {
	codeLen = 0;
	maxDig = 0;
}

// Instantiating Constructor
code::code(int codeLen, int maxDig) {
	this->codeLen = codeLen;
	this->maxDig = maxDig;
}

// Check if the correct digits in the correct place is equal to the length
//  of the secret code. Then the code has been guessed
// codeGuessOutput: the structure containing the output of checking the
//                  user code against the secret code. Passed by reference
//                  so the struct in the main funtion can be changed
bool code::checkWin(const codeGuess& codeGuessOutput) {
	if (codeGuessOutput.correctDigitCorrectPlacement == this->codeLen)
		return true;
	else
		return false;
}

// TODO Write the Algoritm
codeGuess code::checkUserInput(const code& userCode) {
	codeGuess codeGuessOutput;
	codeGuessOutput.correctDigitCorrectPlacement = 0;
	codeGuessOutput.correctDigitIncorrectPlacement = 0;

	return codeGuessOutput;

	for (int i = 0; i < this->codeLen; i++) {

	}
}

// Check if the User input code is of correct parameters: i.e.
//  the maximum user input digit is <= the maximum digit defined
//  in the secret code
bool code::checkValidity() {
	for (int i = 0; i < this->codeLen; i++) {
		if (this->secret.at(i) > this->maxDig)
			return false;
	}

	return true;
}

// Creates the vector containing the user code by asking for
//  user input
code code::generateUserCode() {
	code userCode(this->codeLen, this->maxDig);
	userCode.secret.resize(this->codeLen);

	for (int i = 0; i < this->codeLen; i++) {
		std::cout << "Digit " << i << ": ";
		std::cin >> userCode.secret.at(i);
	}

	return userCode;
}

// Creates the secret code based on the previous user input,
//  defining the maximum digit and the code length. The rand()
//  funtion is used to create a random code
void code::generateSecretCode() {
	int randomNumber;

	for (int i = 0; i < this->codeLen; i++) {
		randomNumber = rand() % this->maxDig;
		this->secret.push_back(randomNumber);
	}
}

// Print the code, used for error checking
void code::printCode() {
	for (int i = 0; i < this->secret.size(); i++) {
		std::cout << this->secret.at(i) << ", ";
	}
	std::cout << std::endl;
}

code acceptInput() {

  int codeLength;
	int maxDigit;

	std::cout << "Welcome to the MASTERMIND Game!\n";
	std::cout << "Please enter the desired length of the secret code: ";
	std::cin  >> codeLength;
  std::cout << "Please enter the maximum digit you want to be in the secret code: ";
	std::cin  >> maxDigit;

  return code(codeLength, maxDigit);
}

// Main funtion, entry point of program
int main()
{
  // Seed the random funtion with the time of execution
	srand(time(NULL));

  // Accept user Input and create secret code object
	code secretCode = acceptInput();
	secretCode.generateSecretCode();

	// secretCode.printCode();

  // create user input code object
	code userCode;

  // Main game loop. returns if the code has been guessed or if the
  //  code has not been guessed after 10 guesses
	std::cout << "You have 10 guesses to get the secret code.\n";
	for (int i = 0; i < 10; i++) {
    std::cout << "Guess Number " << i << ":\n";
		userCode = secretCode.generateUserCode();

		while (!userCode.checkValidity()) {
			std::cout << "Hmm... some of your input digits were larger than your maximum possible digit.\n";
			std::cout << "Try again.\n";
			userCode = secretCode.generateUserCode();
		}

		codeGuess codeGuessOutput = secretCode.checkUserInput(userCode);

    std::cout << "Correct Digits in the correct place: " << codeGuessOutput.correctDigitCorrectPlacement << std::endl;
    std::cout << "Correct Digits in the incorrect place: " << codeGuessOutput.correctDigitIncorrectPlacement << std::endl;

		if (secretCode.checkWin(codeGuessOutput)) {
			std::cout << "Congratulations!! You won!";
			std::cin.get();
			std::cin.get();
			return 0;
		}
	}

	std::cout << "Sorry, you lost...";
	std::cout << "Better Luck Next Time!";
	std::cin.get();
	std::cin.get();

    return 0;
}

