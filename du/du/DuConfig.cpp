#include "DuConfig.h" 
#include <iostream>

#define BUFSIZE MAX_PATH

DuConfig::DuConfig(ArgumentsParser& arguments) {
	precision = Precision::KILOBYTES;
	help = false;
	all = false;
	summarize = false;
	total = false;

	// Get current directory
	DWORD dwRet;
	currentDirectory = new TCHAR[BUFSIZE];

	dwRet = GetCurrentDirectory(BUFSIZE, currentDirectory);

	// Populate the config object
	// Are we going to show the help?
	if (CONTAINS(arguments.getOptions(), string("--help"))) {
		help = true;
	}
	else {
		if (CONTAINS(arguments.getOptions(), string("a"))) {
			all = true;
		}
		if (CONTAINS(arguments.getOptions(), string("s"))) {
			summarize = true;
		}
		if (CONTAINS(arguments.getOptions(), string("c"))) {
			total = true;
		}
		// Presentation in hierarchical order
		if (CONTAINS(arguments.getOptions(), string("m"))) {
			precision = Precision::MEGABYTES;
		}
		if (CONTAINS(arguments.getOptions(), string("h"))) {
			precision = Precision::HUMAN_READABLE;
		}
		if (CONTAINS(arguments.getOptions(), string("k"))) {
			precision = Precision::KILOBYTES;
		}
		if (CONTAINS(arguments.getOptions(), string("b"))) {
			precision = Precision::BYTES;
		}
		// Files specified
		for (list<string>::iterator it = arguments.getArgs().begin(); it != arguments.getArgs().end(); it++) {
			if (*(it) == ".") {
				wstring str(currentDirectory);
				files.push_back(str);
			}
			else if ((*it).find_first_of('*', 0) != string::npos) {
				// If it has any wildcard character
				list<wstring>* expanded = expand(wstring((*it).begin(), (*it).end()), currentDirectory);
				for (list<wstring>::iterator fileIt = expanded->begin(); fileIt != expanded->end(); fileIt++) {
					files.push_back(*fileIt);
				}
				delete expanded;
			}
			else {
				wstring str(currentDirectory);
				str.append(TEXT("\\"));
				str.append(wstring((*it).begin(), (*it).end()));
				files.push_back(str);
			}
		}
	}
}

// Cleans the reserved memory
DuConfig::~DuConfig() {
	delete[] currentDirectory;
}