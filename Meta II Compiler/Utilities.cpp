#include "Utilities.h"

// error logging

void logErrorMessage(const std::string& message) {
	std::cout << "Error: " << message << "." << std::endl;
}

void abortProgram(const std::string& message) {
	logErrorMessage(message);
	abort();
}

void logMissingItemErrorMessageAndAbortProgram(const std::string& missingItem) {
	abortProgram(missingItem + " is expected");
}

// getting input

char readNextCharacter() {
	currentCharacter = getchar();
	return currentCharacter;
}

void matchAndDiscardCharacter(char character) {
	if (currentCharacter != character) {
		std::string errorMessage = "character '";
		errorMessage.append(1, character);
		errorMessage += "'";
		logMissingItemErrorMessageAndAbortProgram(errorMessage);
	}
	else {
		readNextCharacter();
	}
}

void discardWhitespace() {
	while (isspace(currentCharacter))
		readNextCharacter();
}

void matchAndDiscardComment() {
	if (currentCharacter != '#') {
		logMissingItemErrorMessageAndAbortProgram("'#'");
	}
	else {
		do {
			readNextCharacter();
		} while (currentCharacter != '\n' && currentCharacter != '\r' && currentCharacter != EOF);
	}
}

std::string getIdentifier() {
	if(!isalpha(currentCharacter))
		logMissingItemErrorMessageAndAbortProgram("identifier");

	currentIndentifier = std::string(1, currentCharacter);

	while (isalpha(readNextCharacter())) {
		currentIndentifier.append(1, currentCharacter);
	}

	return currentIndentifier;
}

double getNumber() {
	if (!isdigit(currentCharacter) && currentCharacter != '.')
		logMissingItemErrorMessageAndAbortProgram("number");

	std::string number;
	
	do {
		number.append(1, currentCharacter);
		readNextCharacter();
	} while (isdigit(currentCharacter) || currentCharacter == '.');

	currentNumber = atof(number.c_str());
	return currentNumber;
}

// printing output

void print(const std::string& str) {
	std::cout << str;
}

void printCurrentIdentifier() {
	std::cout << currentIndentifier;
}

void printCurrentNumber() {
	std::cout << currentNumber;
}

void printLine(const std::string& line) {
	print(line);
	print("\n");
}