#include "MetaII.h"
#include "IOUtilities.h"

#include <string>


void out1();

void output();

void ex3();

void ex2();

void ex1();

void st();

// utility functions

std::string generateNewLabel() {
	static char currentLabelIndex = 0;

	return "L" + std::to_string(currentLabelIndex++);
}

// implementation

void out1() {
	switch (readCurrentCharacter()) {
	case '*':
		matchAndDiscardCharacter('*');
		switch (readCurrentCharacter()) {
		case '1':
			matchAndDiscardCharacter('1');
			printInstruction("GN1");
			break;
		case '2':
			matchAndDiscardCharacter('2');
			printInstruction("GN2");
			break;
		default:
			printInstruction("CI");
		}
		break;

	case '\'':
		readNextString();
		discardWhitespaceAndReadNextCharacter();
		printInstruction("CL " + readCurrentString());
		break;

	default:
		logMissingItemErrorMessageAndAbortProgram("* or \'");
	}
}

void output() {
	matchAndDiscardCharacter('.');

	switch (readCurrentCharacter()) {
	case 'O':
		matchAndDiscardSequenceOfCharacters("OUT");
		matchAndDiscardCharacter('(');
		while (readCurrentCharacter() != ')')
			out1();
		matchAndDiscardCharacter(')');
		break;
	case 'L':
		matchAndDiscardSequenceOfCharacters("LABEL");
		discardWhitespaceAndReadNextCharacter();
		printInstruction("LB");
		out1();
		break;
	default:
		logMissingItemErrorMessageAndAbortProgram(".OUT or .LABEL");
	}

	printInstruction("OUT");
}

void ex3() {
	std::string label;

	switch (readCurrentCharacter()) {
	case '.':
		matchAndDiscardCharacter('.');
		switch (readCurrentCharacter()) {
		case 'E':
			matchAndDiscardSequenceOfCharacters("EMPTY");
			discardWhitespaceAndReadNextCharacter();
			printInstruction("SET");
			break;
		case 'I':
			matchAndDiscardSequenceOfCharacters("ID");
			discardWhitespaceAndReadNextCharacter();
			printInstruction("ID");
			break;
		case 'N':
			matchAndDiscardSequenceOfCharacters("NUMBER");
			discardWhitespaceAndReadNextCharacter();
			printInstruction("NUM");
			break;
		case 'S':
			matchAndDiscardSequenceOfCharacters("STRING");
			discardWhitespaceAndReadNextCharacter();
			printInstruction("STR");
			break;
		default:
			abortProgram("unknown symbol");
		}
		break;
	case '(':
		matchAndDiscardCharacter('(');
		ex1();
		matchAndDiscardCharacter(')');
		break;
	case '$':
		matchAndDiscardCharacter('$');
		label = generateNewLabel();
		printLabel(label);
		ex3();
		printInstruction("BT " + label);
		printInstruction("SET");
		break;
	case '\'':
		readNextString();
		discardWhitespaceAndReadNextCharacter();
		printInstruction("TST " + readCurrentString());
		break;
	default:
		if (isalpha(readCurrentCharacter())) {
			readNextIdentifier();
			discardWhitespaceAndReadNextCharacter();
			printInstruction("CLL " + readCurrentIdentifier());
		}
		else {
			logMissingItemErrorMessageAndAbortProgram("identifier or string or symbol (not .OUT nor .LABEL) or $ or (");
		}
	}
}

void ex2() {
	std::string label = generateNewLabel();

	switch (readCurrentCharacter()) {
	case '.':
		switch (peekFollowingCharacter()) {
		case 'O':
		case 'L':
			output();
			break;
		case 'E':
		case 'I':
		case 'N':
		case 'S':
			ex3();
			printInstruction("BF " + label);
			break;
		default:
			logMissingItemErrorMessageAndAbortProgram("symbol");
		}
		break;
	case '\'':
	case '(':
	case '$':
		ex3();
		printInstruction("BF " + label);
		break;
	default:
		if (isalpha(readCurrentCharacter())) {
			ex3();
			printInstruction("BF " + label);
		}
		else
			logMissingItemErrorMessageAndAbortProgram("statement");
	}

	char currentCharacter = readCurrentCharacter();
	bool endOfStatementReached = false;
	while (isalpha(currentCharacter)
		|| currentCharacter == '\''
		|| currentCharacter == '.'
		|| currentCharacter == '('
		|| currentCharacter == '$') {

		if (endOfStatementReached)
			break;

		switch (currentCharacter) {
		case '.':
			switch (peekFollowingCharacter()) {
			case ',':
				endOfStatementReached = true;
				break;
			case 'O':
			case 'L':
				output();
				break;
			case 'E':
			case 'I':
			case 'N':
			case 'S':
				ex3();
				printInstruction("BE");
				break;
			default:
				logMissingItemErrorMessageAndAbortProgram("symbol or .,");
			}
			break;
		case '\'':
		case '(':
		case '$':
			ex3();
			printInstruction("BE");
			break;
		default:
			if (isalpha(currentCharacter)) {
				ex3();
				printInstruction("BE");
			}
			else
				logMissingItemErrorMessageAndAbortProgram("statement");
		}

		currentCharacter = readCurrentCharacter();
	}

	printLabel(label);
}

void ex1() {
	std::string label = generateNewLabel();

	ex2();

	while (readCurrentCharacter() == '/') {
		matchAndDiscardCharacter('/');
		printInstruction("BT " + label);
		ex2();
	}

	printLabel(label);
}

void st() {
	readNextIdentifier();
	discardWhitespaceAndReadNextCharacter();
	printLabel(readCurrentIdentifier());
	matchAndDiscardCharacter('=');
	ex1();
	matchAndDiscardSequenceOfCharacters(".,");
	discardWhitespaceAndReadNextCharacter();
	printInstruction("R");
}

// program
void compile() {
	initialize();

	matchAndDiscardSequenceOfCharacters(".SYNTAX");
	discardWhitespaceAndReadNextCharacter();
	readNextIdentifier();
	discardWhitespaceAndReadNextCharacter();
	printInstruction("ADR " + readCurrentIdentifier());

	while (isalpha(readCurrentCharacter()))
		st();

	matchAndDiscardTerminalSequenceOfCharacters(".END");

	printInstruction("END");
}