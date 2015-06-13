#include "stdafx.h"
#include <iostream>
#include "ArgumentsParser.h"
#include <list>
#include <windows.h>
#include <tchar.h>
#include "File.h"

using namespace std;

// Prints the help message
void printHelp() {
	cout << "du tool\n"

<<"Usage: du [OPTION]... [FILE]...\n"
<<"Summarize disk usage of each FILE, recursively for directories.\n"

<<"  -a, --all             write counts for all files, not just directories\n"
<<"  -b, --bytes           print size in bytes\n"
<<"  -c, --total           produce a grand total\n"
<<"  -h, --human-readable  print sizes in human readable format (e.g., 1K 234M 2G)\n"
<<"  -k, --kilobytes       use 1024-byte blocks, not 512 despite POSIXLY_CORRECT\n"
<<"  -m, --megabytes       use 1024K-byte blocks, not 512 despite POSIXLY_CORRECT\n"
<<"  -S, --separate-dirs   do not include size of subdirectories\n"
<<"  -s, --summarize       display only a total for each argument\n"
<<"      --help            display this help and exit\n";
}

// Lists the wrong arguments
void printWrongArguments(string argument) {
	cout << "du:invalid option --> " << argument.c_str() << "\n"
	<< "Try `du --help' for more information.";
}

// Lists the contents of the directory
void listContents(DuConfig& config) {


	File root(config.currentDirectory);
	root.traverse();
}

// Application entry point
// Quite outdated, my C++ is not quite up-to-date
int main(int argc, char *argv[]) {
	try {
		ArgumentsParser parser(argc, argv);
		//parser.listArguments();
		DuConfig& config = parser.exportConfig();
		if (config.help) {
			printHelp();
		}
		else {
			listContents(config);
		}
	}
	catch (string s) {
		printWrongArguments(s);
	}	
}
