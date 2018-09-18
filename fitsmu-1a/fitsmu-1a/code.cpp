#include "code.h"

// Empty Constructor
code::code()
{
	codeLen = 1;
	maxDig = 1;
	generateSecretCode();
}

// Instantiating Constructor
code::code(int codeLen, int maxDig)
{
	this->codeLen = codeLen;
	this->maxDig = maxDig;
	generateSecretCode();
}

code::code(const std::vector<int>& newSecret, const int& maxDigit)
{
	secret = newSecret;
	codeLen = newSecret.size();
	maxDig = maxDigit;
}

// Check if the passed integer is contained in the vector
bool code::find(const std::vector<int>& v, const int& digit)
{
	for (int i = 0; i < v.size(); i++)
	{
		if (v.at(i) == digit)
			return true;
	}
	return false;
}

// Check if the correct digits in the correct place is equal to the length
//  of the secret code. Then the code has been guessed
// codeGuessOutput: the structure containing the output of checking the
//                  user code against the secret code. Passed by reference
//                  so the struct in the main funtion can be changed
bool code::checkWin(const codeGuess& codeGuessOutput) const
{
	if (codeGuessOutput.correctDigitCorrectPlacement == this->codeLen)
		return true;
	else
		return false;
}

// TODO Write the Algoritm
codeGuess code::checkUserInput(const code& userCode) const
{
	codeGuess codeGuessOutput;
	codeGuessOutput.correctDigitCorrectPlacement = checkCorrect(userCode);
	codeGuessOutput.correctDigitIncorrectPlacement = checkIncorrect(userCode);

	return codeGuessOutput;

}

// Check if the User input code is of correct parameters: i.e.
//  the maximum user input digit is <= the maximum digit defined
//  in the secret code
bool code::checkValidity() const
{
	for (int i = 0; i < codeLen; i++)
	{
		if (this->secret.at(i) > maxDig)
			return false;
	}

	return true;
}

// Creates the vector containing the user code by asking for
//  user input
code code::generateUserCode()
{
	code userCode(codeLen, maxDig);
	userCode.secret.resize(this->codeLen);

	for (int i = 0; i < codeLen; i++)
	{
		std::cout << "Digit " << i << ": ";
		std::cin >> userCode.secret.at(i);
	}

	return userCode;
}

// Returns the number of items that were guessed
// with the correct value and correct position.
int code::checkCorrect(const code & guess) const
{
	int correct = 0;
	for (int i = 0; i < this->secret.size(); i++)
	{
		if (guess.secret.at(i) == this->secret.at(i))
			correct++;
	}

	return correct;
}

int code::checkIncorrect(const code & guess) const
{
	// Array containing digits already checked in the secret code
	std::vector<int> checkedDigits;
	int correctDigitIncorrectPosition = 0;


  // TODO This should be pulled into helper function
  for (int i = 0; i < this->codeLen; i++) {
    if (guess.secret.at(i) == this->secret.at(i))
      checkedDigits.push_back(i);
  }

	for (int i = 0; i < guess.codeLen; i++)
	{
		for (int j = 0; j < this->codeLen; j++)
		{
			if (j != i && !code::find(checkedDigits, j) && (this->secret.at(j) == guess.secret.at(i)))
			{
				correctDigitIncorrectPosition++;
				checkedDigits.push_back(j);
				break;
			}
		}
	}
	return correctDigitIncorrectPosition;
}

// Creates the secret code based on the previous user input,
// defining the maximum digit and the code length. The rand()
// funtion is used to create a random code
void code::generateSecretCode()
{
	int randomNumber;

	for (int i = 0; i < codeLen; i++)
	{
		// generate random number from 1 to maxDig
		randomNumber = rand() % (maxDig+1);
		secret.push_back(randomNumber);
	}
}

// Print the code, used for error checking
void code::printCode() const
{
	for (int i = 0; i < secret.size(); i++)
	{
		std::cout << secret.at(i) << ", ";
	}
	std::cout << std::endl;
}
