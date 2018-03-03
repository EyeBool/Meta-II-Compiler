#ifndef UTILITIES_H
#define UTILITIES_H

#include <cstdlib>
#include <iostream>
#include <string>

static char currentCharacter;
static std::string currentIndentifier;
static double currentNumber;

// error logging

void logErrorMessage(const std::string& message);

void abortProgram(const std::string& message);

void logMissingItemErrorMessageAndAbortProgram(const std::string& missingItem);

// getting input

char readNextCharacter();

void matchAndDiscardCharacter(char character);

void discardWhitespace();

void matchAndDiscardComment();

std::string getIdentifier();

double getNumber();

// printing output

void print(const std::string& str);

void printCurrentIdentifier();

void printCurrentNumber();

void printLine(const std::string& line);

#endif