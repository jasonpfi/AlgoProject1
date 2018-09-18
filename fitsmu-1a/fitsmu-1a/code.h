#pragma once
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>

using namespace std;
// Structure defining the output of checking the user code input
//  compared to the secret code
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
//  the maximum digit, as well as a vector defining the code
class code
{
public:

	code();
	code(int codeLen, int maxDig);

	void printCode();
	code generateUserCode();
	bool checkValidity();
	int checkCorrect(const code& guess);
	int checkIncorrect(const code& guess);
	codeGuess checkUserInput(const code& userCode);
	bool checkWin(const codeGuess& codeGuessOutput);

private:

	int codeLen;
	int maxDig;
	vector<int> secret;
	void generateSecretCode();
};