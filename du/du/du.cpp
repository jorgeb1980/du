// du.cpp: archivo de proyecto principal.

#include "stdafx.h"
#include <iostream>
#include "ArgumentsParser.h"

using namespace std;

int main(int argc, char *argv[]) {
	cout << "Argumentos a la llamada:\n";
	ArgumentsParser parser(argc, argv);
	parser.listArguments();
}
