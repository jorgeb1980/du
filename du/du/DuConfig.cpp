#include "DuConfig.h"

#define BUFSIZE MAX_PATH

DuConfig::DuConfig() {
	precision = Precision::KILOBYTES;
	help = false;
	all = false;
	summarize = false;

	// Get current directory
	DWORD dwRet;
	currentDirectory = new TCHAR[BUFSIZE];

	dwRet = GetCurrentDirectory(BUFSIZE, currentDirectory);
}

// Cleans the reserved memory
DuConfig::~DuConfig() {
	delete[] currentDirectory;
}