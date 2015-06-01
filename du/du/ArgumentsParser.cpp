#include <string>
#include <list>
#include <set>
#include "ArgumentsParser.h"
#include <iostream>

using namespace std;

// Possible options
#define NUM_OPTIONS 8
static const string ACCEPTABLE_OPTIONS_ARRAY[NUM_OPTIONS] = { 
	string("a"), 
	string("b"), 
	string("c"), 
	string("h"), 
	string("k"), 
	string("m"), 
	string("s"),
	string("--help")
};
static set<string> ACCEPTABLE_OPTIONS_SET;

// Acceptable options set
void optionsSet() {
	for (int i = 0; i < NUM_OPTIONS; i++) {
		ACCEPTABLE_OPTIONS_SET.insert(ACCEPTABLE_OPTIONS_ARRAY[i]);
	}
}

// Constructor: parses the command line
ArgumentsParser::ArgumentsParser(int theArgc, char* theArgv[]) {
	this->argc = theArgc;
	// First, parsing options
	bool parsingOptions = true;
	for (int i = 1; i < argc; i++) {
		std::string s(theArgv[i]);

		if (s.compare("--help") == 0) {
			options.insert(s);
		}
		else {
			if (parsingOptions && s[0] == '-') {
				string tmp = s.substr(1, string::npos);
				for (size_t i = 0; i < tmp.length(); i++) {
					options.insert(string(&tmp[i], 1));
				}
			}
			if (parsingOptions && s[0] != '-') {
				parsingOptions = false;
			}
			if (!parsingOptions && s[0] == '-') {
				throw s;
			}
			if (!parsingOptions && s[0] != '-') {
				// File
				files.push_back(s);
			}
		}
	}
}

// Prints the arguments in the console
void ArgumentsParser::listArguments() {
	cout << "\nArguments:\n";
	for (set<string>::iterator it = this->options.begin(); it != this->options.end(); it++) {
		string arg = *it;
		cout << (*it).c_str() << "\n";
	}
	cout << "\nFiles:\n";
	for (list<string>::iterator itF = files.begin();  itF != files.end(); itF++) {
		cout << *itF << "\n";
	}
}

#define CONTAINS(x, y) (x.find(y) != x.end())

// Creates the configuration object
DuConfig& ArgumentsParser::exportConfig() {
	// Is there any illegal option?
	optionsSet();
	// Check all the options
	for (set<string>::iterator it = options.begin(); it != options.end(); it++) {
		if (!CONTAINS(ACCEPTABLE_OPTIONS_SET, (*it))) {
			throw *it;
		}
	}
	// Are we going to show the help?
	if (CONTAINS(options, string("--help"))) {
		config.help = true;
	}
	else {
		if (CONTAINS(options, string("a"))) {
			config.all = true;
		}
	}
	return config;
}