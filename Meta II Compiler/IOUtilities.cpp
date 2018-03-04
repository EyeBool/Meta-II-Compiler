#include "IOUtilities.h"

static char currentCharacter;
static char followingCharacter;

static std::string currentIdentifier;
static std::string currentString;
static double currentNumber;

// initialize library

void initialize() {
	do {
		currentCharacter = getchar();
	} while (isspace(currentCharacter));

	if (currentCharacter != EOF)
		followingCharacter = getchar();
	else
		followingCharacter = EOF;
}

// error logging

void logErrorMessage(const std::string& message) {
	std::cerr << "Error: " << message << ".\n";
}

void abortProgram(const std::string& message) {
	logErrorMessage(message);
	abort();
}

void logMissingItemErrorMessageAndAbortProgram(const std::string& missingItem) {
	abortProgram(missingItem + " expected");
}

// getting input

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

	discardWhitespaceAndReadNextCharacter();
}

void matchAndDiscardSequenceOfCharacters(const std::string& sequence) {
	for (char character : sequence) {
		if (currentCharacter != character) {
			logMissingItemErrorMessageAndAbortProgram("sequence \"" + sequence + "\"");
		}
		else {
			readNextCharacter();
		}
	}
}

void matchAndDiscardTerminalSequenceOfCharacters(const std::string& terminalSequence) {
	if (terminalSequence.empty())
		return;

	if(currentCharacter != terminalSequence[0])
		logMissingItemErrorMessageAndAbortProgram("terminal sequence \"" + terminalSequence + "\"");

	for (unsigned int i = 1; i < terminalSequence.length(); i++) {
		if (followingCharacter != terminalSequence[i]) {
			logMissingItemErrorMessageAndAbortProgram("sequence \"" + terminalSequence + "\"");
		}
		else if(i != terminalSequence.length() - 1) {
			followingCharacter = getchar();
		}
	}
}

void discardWhitespaceAndReadNextCharacter() {
	while (isspace(currentCharacter))
		readNextCharacter();
}

char readNextCharacter() {
	currentCharacter = followingCharacter;
	if (followingCharacter != EOF)
		followingCharacter = getchar();
	else
		abortProgram("EOF reached");
	return currentCharacter;
}

char readCurrentCharacter() {
	return currentCharacter;
}

char peekFollowingCharacter() {
	return followingCharacter;
}

std::string readNextIdentifier() {
	if(!isalpha(currentCharacter))
		logMissingItemErrorMessageAndAbortProgram("identifier");

	currentIdentifier.clear();
	currentIdentifier.append(1, currentCharacter);

	while (isalnum(readNextCharacter())) {
		currentIdentifier.append(1, currentCharacter);
	}

	return currentIdentifier;
}

std::string readCurrentIdentifier() {
	return currentIdentifier;
}

std::string readNextString() {
	currentString.clear();

	matchAndDiscardCharacter('\'');
	currentString.append(1, '\'');

	while (currentCharacter != '\'' && currentCharacter != EOF) {
		currentString.append(1, currentCharacter);
		readNextCharacter();
	}

	if (currentCharacter == EOF)
		logErrorMessage("EOF reached");

	matchAndDiscardCharacter('\'');
	currentString.append(1, '\'');

	return currentString;
}

std::string readCurrentString() {
	return currentString;
}

double readNextNumber() {
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

double readCurrentNumber() {
	return currentNumber;
}

// printing output

void print(const std::string& str) {
	std::cout << str;
}

void printLine(const std::string& line) {
	print(line);
	print("\n");
}

void printLabel(const std::string& label) {
	printLine(label);
}

void printInstruction(const std::string& instruction) {
	print("\t");
	printLine(instruction);
}