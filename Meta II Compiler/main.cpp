#include "Utilities.h"
#include <iostream>

void initialize() {
	readNextCharacter();
}

void expression() {
	getNumber();
	print("read: ");
	printCurrentNumber();
	printLine(" <- number");
}


int main() {
	initialize();
	expression();

	getchar();

	return 0;
}