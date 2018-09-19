#include "code.h"

// Empty Constructor
code::code()
{
	codeLen = 1;
	maxDig = 1;
	generateSecretCode();
}

// Instantiating Constructor, calls generateSecretCode method to
//  fill the secret vector with random integers
//
// codeLen: Defines the length of the secret code
// maxDig: Defines the maximum possible digit in the code
code::code(int codeLen,
           int maxDig)
{
	this->codeLen = codeLen;
	this->maxDig = maxDig;
	generateSecretCode();
}

// Constructor to create code object with a vector and a maximum digit
//
// newSecret: Vector containing the integers of a secret code
// maxDigit: Defines the maximum possible digit in the code
code::code(const std::vector<int>& newSecret,
           const int& maxDigit)
{
	secret = newSecret;
	codeLen = newSecret.size();
	maxDig = maxDigit;
}

// Check if the passed integer is contained in the passed vector
// This is a static method because has no instance importance but is
//  related to code class
//
// v: Vector of integers populated by function, if "this" object
//    contains the digit
// digit: Vector is checked to see if it contains this int
bool code::find(const std::vector<int>& v,
                const int digit)
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
//
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

// Checks how the code that the user has input matches with the
//  secret code. This will return a struct that contains 2 integers
//  that tell how many correct digits were in the correst place and
//  how many correct digits were in the incorrect place.
// To get the value of the integers, two helper functions are called
//  in each case to compare the two code objects
//
//  userCode: The code object containing the secret code guessed by
//            the player
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
		if (this->secret.at(i) > this->maxDig)
			return false;
	}

	return true;
}

// Creates the vector containing the user code by asking for
//  user input
code code::generateUserCode()
{
	code userCode(this->codeLen, this->maxDig);
	userCode.secret.resize(this->codeLen);

	for (int i = 0; i < this->codeLen; i++)
	{
		std::cout << "Digit " << i << ": ";
		std::cin >> userCode.secret.at(i);
	}

	return userCode;
}

// Returns the number of items that were guessed
// with the correct value and correct position.
//
// guess: the code object containing the secret code guessed by
//        the player
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

// Check how many digits in the user code are in the correct place in
//  the secret code
// Adds the index of these correctly placed digits into the checkedDigits vector
//  so the code::checkIncorrect method does not mistakenly take a correctly placed
//  digit for an incorrect one (i.e. if the digit was correctly placed at index 4,
//  but another instace of the digit is as index 1)
//
//  checkedDigits: The vector containing the indices of the number in the secret
//                 code that have already been mathched to the user's guess
//  guess: The code object containing the secret code guessed by
//         the player
void code::checkCorrectForIncorrect(std::vector<int>& checkedDigits,
                                    const code& guess) const{
  for (int i = 0; i < this->codeLen; i++)
  {
    if (guess.secret.at(i) == this->secret.at(i))
      checkedDigits.push_back(i);
  }
}

// Returns the number of correct digits placed incorrectly. In other words, how
//  how many digits are in the secret code, but have been entered at the incorrect
//  index.
// The method only counts instances once, using a local vector to keep track
//  of indexes already verified to have the correct digit.
//
//  guess: The code object containing the secret code guessed by
//         the player
int code::checkIncorrect(const code& guess) const
{
	// Array containing digits already checked in the secret code
	std::vector<int> checkedDigitsSecret;
  std::vector<int> checkedDigitsUser;
  int correctDigitIncorrectPosition = 0;

  // Called to preallocate all indices that have correct guesses in
  //  correct positions
  this->checkCorrectForIncorrect(checkedDigitsSecret, guess);
  this->checkCorrectForIncorrect(checkedDigitsUser, guess);

  // Loop to check through both the user guess and the secret code and
  //  compare their digits
	for (int i = 0; i < guess.codeLen; i++)
	{
		for (int j = 0; j < this->codeLen; j++)
		{
			if (j != i &&
          !code::find(checkedDigitsSecret, j) &&
          !code::find(checkedDigitsUser, i) &&
          (this->secret.at(j) == guess.secret.at(i)))
			{
				correctDigitIncorrectPosition++;
				checkedDigitsSecret.push_back(j);
        checkedDigitsUser.push_back(i);
				break; // necessary to not count multiple instances of digit placed incorrectly
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
