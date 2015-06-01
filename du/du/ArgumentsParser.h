#ifndef __ARGUMENTS_PARSER_H__
#define __ARGUMENTS_PARSER_H__

#include <list>
#include <string>

using namespace std;

class ArgumentsParser {

private:
	// Parameters passed to command line
	int argc;
	list<string> arguments;

public:
	ArgumentsParser(int theArgc, char* theArgv[]);
	void listArguments();
};

#endif