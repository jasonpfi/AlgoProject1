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

class code {
	int codeLen;
	int maxDig;
	std::vector<int> secret;

public:

	code();
	code(int codeLen, int maxDig);
	code(const std::vector<int>& userCode, const code& secretCode);

	void generateSecretCode();
	void printCode();
	int getCodeLen();
};

code::code() {
	codeLen = 0;
	maxDig = 0;
}

code::code(int codeLen, int maxDig) {
	this->codeLen = codeLen;
	this->maxDig = maxDig;
}

code::code(const std::vector<int>& userCode, const code& secretCode) {
	this->secret = userCode;
	this->maxDig = secretCode.maxDig;
	this->codeLen = secretCode.codeLen;
}

int code::getCodeLen() {
	return this->codeLen;
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

	std::cout << "You have 10 guesses to get the secret code.";
	for (int i = 0; i < secretCode.get)
	std::cout << 

	std::cin.get();
	std::cin.get();

    return 0;
}

