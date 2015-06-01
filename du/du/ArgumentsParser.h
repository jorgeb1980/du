#ifndef __ARGUMENTS_PARSER_H__
#define __ARGUMENTS_PARSER_H__

#include <list>
#include <set>
#include "DuConfig.h"

/*
 * Simple command line parser.  Will try to read the arguments combo passed by the command line.
 */
class ArgumentsParser {

private:
	// Parameters passed to command line
	int argc;
	std::list<std::string> arguments;
	
	// Parsed arguments
	std::set<std::string> options;

	// Parsed files
	std::list<std::string> files;

	// Configuration object
	DuConfig config;
public:
	ArgumentsParser(int theArgc, char* theArgv[]);
	void listArguments();
	DuConfig& exportConfig();
};

#endif