#pragma once
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>

// Structure defining the output of checking the user code input
// compared to the secret code
// correctDigitCorrectPlacement: how many digits were guessed in the
//                                correct positions
// correctDigitIncorrectPlacement: how many digits were guessed
//                                  correctly in the incorrect positions
struct codeGuess
{
	int correctDigitCorrectPlacement;
	int correctDigitIncorrectPlacement;
};

// Main class defining a code, secret or user input
// A code is defined by its length and the value of
// the maximum digit, as well as a vector defining the code
class code
{
public:

	// Constructors
	code();
	code(const int& codeLen, const int& maxDig);
	code(const std::vector<int>& secret, const int& maxDigit);

	// Non-Static Member Functions
	void printCode() const;
	code generateUserCode() const;
	bool checkValidity() const;
	int checkCorrect(const code& guess) const;
	int checkIncorrect(const code& guess) const;
	codeGuess checkUserInput(const code& userCode) const;
	bool checkWin(const codeGuess& codeGuessOutput) const;

private:

	// Fields
	int codeLen;
	int maxDig;
	std::vector<int> secret;

	// Private Method
	void generateSecretCode();
	void checkCorrectForIncorrect(std::vector<int>& checkedDigits, const code& guess) const;

	// Static Member Functions
	static bool find(const std::vector<int>& v, const int& digit);
};
