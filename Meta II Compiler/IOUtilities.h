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

void discardWhitespaceAndReadNextCharacter();

void matchAndDiscardComment();

std::string readNextIdentifier();

std::string readCurrentIdentifier();

std::string readNextString();

std::string readCurrentString();

double readNextNumber();

double readCurrentNumber();

// printing output

void print(const std::string& str);

void printCurrentIdentifier();

void printCurrentNumber();

void printLine(const std::string& line);

#endif