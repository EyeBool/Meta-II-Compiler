#include "MetaII.h"
#include "IOUtilities.h"

#include <string>

std::string generateNewLabel() {
	static char currentLabelIndex = 0;

	return "L" + std::to_string(currentLabelIndex++);
}

void out1() {
	switch (readCurrentCharacter()) {
	case '*':
		matchAndDiscardCharacter('*');
		switch (readCurrentCharacter()) {
		case '1':
			matchAndDiscardCharacter('1');
			printLine("GN1");
			break;
		case '2':
			matchAndDiscardCharacter('2');
			printLine("GN2");
			break;
		default:
			printLine("CI");
		}
		break;

	case '\'':
		readNextString();
		printLine("CL " + readCurrentString());
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
		printLine("LB");
		out1();
		break;
	default:
		logMissingItemErrorMessageAndAbortProgram(".OUT or .LABEL");
	}

	printLine("OUT");
}

void ex3() {
	std::string label;

	switch (readCurrentCharacter()) {
	case '.':
		matchAndDiscardCharacter('.');
		switch (readCurrentCharacter()) {
		case 'E':
			matchAndDiscardSequenceOfCharacters("EMPTY");
			printLine("SET");
			break;
		case 'I':
			matchAndDiscardSequenceOfCharacters("ID");
			printLine("ID");
			break;
		case 'N':
			matchAndDiscardSequenceOfCharacters("NUMBER");
			printLine("NUM");
			break;
		case 'S':
			matchAndDiscardSequenceOfCharacters("STRING");
			printLine("STR");
		default:
			logErrorMessage("unknown symbol");
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
		printLine("LABEL: " + label);
		ex3();
		printLine("BT " + label);
		printLine("SET");
		break;
	case '\'':
		readNextString();
		printLine("TST " + readCurrentString());
		break;
	default:
		if (isalpha(readCurrentCharacter())) {
			readNextIdentifier();
			printLine("CLL " + readCurrentIdentifier());
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
			printLine("BF " + label);
			break;
		default:
			logMissingItemErrorMessageAndAbortProgram("symbol");
		}
		break;
	case '\'':
	case '(':
	case '$':
		ex3();
		printLine("BF " + label);
		break;
	default:
		if (isalpha(readCurrentCharacter())) {
			ex3();
			printLine("BF " + label);
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
				printLine("BE");
				break;
			default:
				logMissingItemErrorMessageAndAbortProgram("symbol or .,");
			}
			break;
		case '\'':
		case '(':
		case '$':
			ex3();
			printLine("BE");
			break;
		default:
			if (isalpha(currentCharacter)) {
				ex3();
				printLine("BE");
			}
			else
				logMissingItemErrorMessageAndAbortProgram("statement");
		}

		currentCharacter = readCurrentCharacter();
	}

	printLine("LABEL: " + label);
}

void ex1() {
	std::string label = generateNewLabel();

	ex2();

	while (readCurrentCharacter() == '/') {
		matchAndDiscardCharacter('/');
		printLine("BT " + label);
		ex2();
	}

	printLine("LABEL: " + label);
}

void st() {
	readNextIdentifier();
	printLine("LABEL: " + readCurrentIdentifier());
	matchAndDiscardCharacter('=');
	ex1();
	matchAndDiscardSequenceOfCharacters(".,");
	discardWhitespaceAndReadNextCharacter();
	printLine("R");
}

void program() {
	initialize();

	matchAndDiscardSequenceOfCharacters(".SYNTAX");
	readNextIdentifier();
	printLine("ADR " + readCurrentIdentifier());

	while (isalpha(readCurrentCharacter()))
		st();

	matchAndDiscardSequenceOfCharacters(".END");
	printLine("END");
}