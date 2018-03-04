#ifndef IOUTILITIES_H
#define IOUTILITIES_H

#include <cstdlib>
#include <iostream>
#include <string>

// initialize library

void initialize();

// error logging

void logErrorMessage(const std::string& message);

void abortProgram(const std::string& message);

void logMissingItemErrorMessageAndAbortProgram(const std::string& missingItem);

// getting input

char readNextCharacter();

char readCurrentCharacter();

char peekFollowingCharacter();

void matchAndDiscardCharacter(char character);

void matchAndDiscardSequenceOfCharacters(const std::string& sequence);

void matchAndDiscardTerminalSequenceOfCharacters(const std::string& terminalSequence);

void discardWhitespaceAndReadNextCharacter();

std::string readNextIdentifier();

std::string readCurrentIdentifier();

std::string readNextString();

std::string readCurrentString();

double readNextNumber();

double readCurrentNumber();

// printing output

void print(const std::string& str);

void printLine(const std::string& line);

void printLabel(const std::string& label);

void printInstruction(const std::string& instruction);

#endif