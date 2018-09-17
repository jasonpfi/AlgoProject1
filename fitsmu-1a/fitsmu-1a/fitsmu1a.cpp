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

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>

struct codeGuess {
	int correctDigitCorrectPlacement;
	int correctDigitIncorrectPlacement;
};

class code {
	int codeLen;
	int maxDig;
	std::vector<int> secret;

public:

	code();
	code(int codeLen, int maxDig);

	void generateSecretCode();
	void printCode();
	const code& generateUserCode();
	bool checkValidity();
	codeGuess checkUserInput(const code& userCode);
	bool checkWin(const codeGuess& codeGuessOutput);
};

code::code() {
	codeLen = 0;
	maxDig = 0;
}

code::code(int codeLen, int maxDig) {
	this->codeLen = codeLen;
	this->maxDig = maxDig;
}

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

bool code::checkValidity() {
	for (int i = 0; i < this->codeLen; i++) {
		if (this->secret.at(i) > this->maxDig)
			return false;
	}

	return true;
}

const code& code::generateUserCode() {
	code userCode(this->codeLen, this->maxDig);
	userCode.secret.resize(this->codeLen);

	for (int i = 0; i < this->codeLen; i++) {
		std::cout << "Guess " << i << ": ";
		std::cin >> userCode.secret.at(i);
	}

	return userCode;
}

void code::generateSecretCode() {
	int randomNumber;

	for (int i = 0; i < this->codeLen; i++) {
		randomNumber = rand() % this->maxDig;
		this->secret.push_back(randomNumber);
	}
}

void code::printCode() {
	for (int i = 0; i < this->secret.size(); i++) {
		std::cout << this->secret.at(i) << ", ";
	}
	std::cout << std::endl;
}

// Main funtion, entry point of program
int main()
{
	srand(time(NULL));

	int codeLength;
	int maxDigit;

	std::cout << "Welcome to the MASTERMIND Game!\n";
	std::cout << "Please enter the desired length of the secret code: ";
	std::cin  >> codeLength;
	std::cout << "Please enter the maximum digit you want to be in the secret code: ";
	std::cin  >> maxDigit;

	code secretCode(codeLength, maxDigit);
	secretCode.generateSecretCode();

	// secretCode.printCode();

	code userCode;

	std::cout << "You have 10 guesses to get the secret code.";
	for (int i = 0; i < 10; i++) {
		userCode = secretCode.generateUserCode();
		if (!userCode.checkValidity()) {
			std::cout << "Hmm... some of your input digits were larger than your maximum possible digit.";
			std::cout << "Try again.";
			userCode = secretCode.generateUserCode();
		}

		codeGuess codeGuessOutput = secretCode.checkUserInput(userCode);

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

