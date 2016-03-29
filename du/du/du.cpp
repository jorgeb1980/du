#include "stdafx.h"
#include <iostream>
#include "libargs.h"
#include "DuConfig.h"
#include <list>
#include <windows.h>
#include <tchar.h>
#include "File.h"
#include <sstream>

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

// Human presentation file size function shamelessly stolen from
// http://programanddesign.com/cpp/human-readable-file-size-in-c/
void readable_fs(DWORDLONG size/*in bytes*/, std::string& s) {
    int i = 0;
	double dsize = size;
    const char* units[] = {"", "K", "M", "G", "T", "P", "E", "Z", "Y"};
    while (dsize > 1024 && i <= 8) {
        dsize /= 1024;
			i++;
    }
	
	std::string number;
	std::stringstream strstream;
	strstream.precision(3);
	strstream << dsize;
	strstream >> number;
	s = number + std::string(units[i]);
}

#define TABULATION 10
// Writes a number with a certain presentation
void writeNumber(DWORDLONG number, DuConfig& config) {
	std::string size;
	// file size
	cout.width(TABULATION);
	switch(config.precision) {
	case Precision::MEGABYTES:
		cout << left << number / (1024 * 1024);
		break;
	case Precision::HUMAN_READABLE:
		readable_fs(number, size);
		cout << left << size.c_str();
		break;
	case Precision::BYTES:
		cout << left << number;
		break;
	case Precision::KILOBYTES:
	default:
		cout << left << number / 1024;
	}
}

// Presentation of a file/directory
void printFile(File& file, DuConfig& config) {

	writeNumber(file.getSize(), config);
	// Remove the starting path
	wstring original(file.getName());
	string tmp(".");
	original = original.substr(
		wstring(config.currentDirectory).length(), 
		(original.length() - wstring(config.currentDirectory).length()));
	tmp.append(string(original.begin(), original.end()));

	cout << tmp << "\n";
}

// Recursive call with depth control
void traverseI(File& file, DuConfig& config, int& depth) {
	if (file.isDirectory()) {
		std::list<File*>& children = file.getChildren();
		depth++;
		if (!config.summarize || depth <= 1) {
			for (list<File*>::iterator it = children.begin(); it != children.end(); it++) {
				File f = *(*it);
				traverseI(f, config, depth);
			}
		}
		printFile(file, config);
	}
}

// Width traverse of the File structure
void traverse(File& root, DuConfig& config) {
	int depth = 0;
	traverseI(root, config, depth);
}

// Lists the contents of the directory
void listContents(DuConfig& config) {
	for (list<wstring>::iterator it = config.files.begin(); it != config.files.end(); it++) {
		File root((*it));
		traverse(root, config);
		if (config.total) {
			// Produce grand total
			// Whatever it is used for??
			writeNumber(root.getSize(), config);
			cout << "total" << "\n";
		}
	}
}

// Options supported by the application
void populateOptions(list<string>& options) {
	options.push_back("a");
	options.push_back("b");
	options.push_back("c");
	options.push_back("h");
	options.push_back("k");
	options.push_back("m");
	options.push_back("s");
	options.push_back("--help");
}

// Application entry point
// Quite outdated, my C++ is not quite up-to-date
int main(int argc, char *argv[]) {
	try {
		list<string> options;
		populateOptions(options);
		ArgumentsParser parser(argc, argv, options);
		//parser.listArguments();
		DuConfig config(parser);
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
