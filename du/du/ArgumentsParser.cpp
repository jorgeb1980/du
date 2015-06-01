#include <list>
#include <iostream>
#include "ArgumentsParser.h"

ArgumentsParser::ArgumentsParser(int theArgc, char* theArgv[]) {
	this->argc = theArgc;
	for (int i = 0; i < argc; i++) {
		string str(theArgv[i]);
		this->arguments.push_back(str);
	}
}

void ArgumentsParser::listArguments() {
	for (list<string>::iterator it = this->arguments.begin(); it != this->arguments.end(); it++) {
		cout << *it;
	}
}