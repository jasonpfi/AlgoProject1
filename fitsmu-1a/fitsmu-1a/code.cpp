// Project 1a
//
// Team: fitsmu
// Justin Fitch
// Sam Smucny
//
// code.cpp: source file for code class

#include "code.h"

code::code()
// Empty Constructor
{
	 codeLen = 1;
   maxDig = 1;
	 generateSecretCode();
}

code::code(const int& codeLen, const int& maxDig)
// Instantiating Constructor, calls generateSecretCode method to
// fill the secret vector with random integers
//
// codeLen: Defines the length of the secret code
// maxDig: Defines the maximum possible digit in the code
{
	 this->codeLen = codeLen;
	 this->maxDig = maxDig;
	 generateSecretCode();
}

code::code(const std::vector<int>& newSecret, const int& maxDigit)
// Constructor to create code object with a vector and a maximum digit
//
// newSecret: Vector containing the integers of a secret code
// maxDigit: Defines the maximum possible digit in the code
{
	 secret = newSecret;
	 codeLen = newSecret.size();
	 maxDig = maxDigit;
}

code code::acceptInput()
// Read data from User's keyboard to initialize the code.
// Asks the user multiple again if input is invalid.
{

	 int codeLength;
	 int maxDigit;

   // Get user input
	 std::cout << "Please enter the desired length of the secret code: ";
	 std::cin >> codeLength;
	 std::cout << "Please enter the maximum digit you want to be in the"
                "secret code: ";
	 std::cin >> maxDigit;

   // check negative input
	 if (codeLength <= 0 || maxDigit <= 0)
	 {
      std::cout << "One or both of the values you entered were not valid."
                   "Please choose two non negative integers." << std::endl;
		  return acceptInput();
	 }
	 else
	 {
		  return code(codeLength, maxDigit);
	 }
} // End of acceptInput()

bool code::find(const std::vector<int>& v, const int& digit)
// Check if the passed integer is contained in the passed vector
// This is a static method because has no instance importance but is
// related to code class
//
// v: Vector of integers populated by function, if "this" object
//    contains the digit
// digit: Vector is checked to see if it contains this int
{
	 for (int i = 0; i < v.size(); i++)
	 {
      // is the digit located at index "i" in the vector
		  if (v.at(i) == digit)
			   return true;
	 }

	 return false;
}

bool code::checkWin(const codeGuess& codeGuessOutput) const
// Check if the correct digits in the correct place is equal to the length
// of the secret code. Then the code has been guessed
//
// codeGuessOutput: the structure containing the output of checking the
//                  user code against the secret code. Passed by reference
//                  so the struct in the main funtion can be changed
{
	 return codeGuessOutput.correctDigitCorrectPlacement == this->codeLen;
}

codeGuess code::checkUserInput(const code& userCode) const
// Checks how the code that the user has input matches with the
// secret code. This will return a struct that contains 2 integers
// that tell how many correct digits were in the correst place and
// how many correct digits were in the incorrect place.
// To get the value of the integers, two helper functions are called
// in each case to compare the two code objects
//
// userCode: The code object containing the code guessed by
//           the player
{
	 codeGuess codeGuessOutput;
	 codeGuessOutput.correctDigitCorrectPlacement = checkCorrect(userCode);
	 codeGuessOutput.correctDigitIncorrectPlacement = checkIncorrect(userCode);

	 return codeGuessOutput;
}

bool code::checkValidity() const
// Check if the User input code is of correct parameters: i.e.
// the maximum user input digit is <= the maximum digit defined
// in the secret code
{
	 for (int i = 0; i < codeLen; i++)
	 {
      // if the user code has digits greater than the max digit
      //  then return false
		  if (this->secret.at(i) > this->maxDig)
			   return false;
	 }

	 return true;
}

code code::generateUserCode() const
// Creates the vector containing the user code by asking for
// user input
{
	 code userCode(this->codeLen, this->maxDig);
	 userCode.secret.resize(this->codeLen);

   // Accept input for each digit in user code
	 for (int i = 0; i < this->codeLen; i++)
	 {
		  std::cout << "Digit " << i << ": ";
		  std::cin >> userCode.secret.at(i);
	 }

	 return userCode;
} // end of generateUserCode()

int code::checkCorrect(const code & guess) const
// Returns the number of items that were guessed
// with the correct value and correct position.
//
// guess: the code object containing the secret code guessed by
//        the player
{
	 int correct = 0;


   for (int i = 0; i < this->secret.size(); i++)
	 {
		  if (guess.secret.at(i) == this->secret.at(i))
			   correct++;
	 }

	 return correct;
} // end of checkCorrect()

void code::checkCorrectForIncorrect(std::vector<int>& checkedDigits,const code&
    guess) const
// Check how many digits in the user code are in the correct place in
// the secret code
// Adds the index of these correctly placed digits into the checkedDigits
// vector
// so the code::checkIncorrect method does not mistakenly take a correctly
// placed
// digit for an incorrect one (i.e. if the digit was correctly placed at index 4,
// but another instace of the digit is as index 1)
//
// checkedDigits: The vector containing the indices of the number in the secret
//                code that have already been mathched to the user's guess
// guess: The code object containing the secret code guessed by
//        the player
{
	 for (int i = 0; i < this->codeLen; i++)
	 {
      // Check if the codes have the same digit in the same place. If so,
      //  add the index to the vector
		  if (guess.secret.at(i) == this->secret.at(i))
			   checkedDigits.push_back(i);
	 }
}

int code::checkIncorrect(const code& guess) const
// Returns the number of correct digits placed incorrectly. In other words, how
// how many digits are in the secret code, but have been entered at the incorrect
// index.
// The method only counts instances once, using a local vector to keep track
// of indexes already verified to have the correct digit.
//
// guess: The code object containing the secret code guessed by
//        the player
{
   // Array containing digits already checked in the secret code
	 std::vector<int> checkedDigitsSecret;
	 std::vector<int> checkedDigitsUser;
	 int correctDigitIncorrectPosition = 0;

   // Called to preallocate all indices that have correct guesses in
   // correct positions
	 this->checkCorrectForIncorrect(checkedDigitsSecret, guess);
	 this->checkCorrectForIncorrect(checkedDigitsUser, guess);

   // Loop to check through both the user guess and the secret code and
   // compare their digits
	 for (int i = 0; i < guess.codeLen; i++)
	 {
		  for (int j = 0; j < this->codeLen; j++)
		  {
			   if (j != i && !code::find(checkedDigitsSecret, j) &&
             !code::find(checkedDigitsUser, i) && (this->secret.at(j) ==
             guess.secret.at(i)))
			   {
				    correctDigitIncorrectPosition++;
				    checkedDigitsSecret.push_back(j);
				    checkedDigitsUser.push_back(i);
				    break; // necessary to not count multiple instances
			   }
		  }
	 } // End for loop

	 return correctDigitIncorrectPosition;
} // End of checkIncorrect()

void code::generateSecretCode()
// Creates the secret code based on the previous user input,
// defining the maximum digit and the code length. The rand()
// funtion is used to create a random code
{
	 int randomNumber;

	 for (int i = 0; i < codeLen; i++)
	 {
	    // generate random number from 0 to maxDig
		  randomNumber = rand() % (maxDig + 1);
		  secret.push_back(randomNumber);
	 }
}

void code::printCode() const
// Print the code, used for error checking
{
	 for (int i = 0; i < secret.size(); i++)
	 {
		  std::cout << secret.at(i) << ", ";
	 }

   std::cout << std::endl;
}
