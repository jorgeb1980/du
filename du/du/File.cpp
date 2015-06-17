#include "File.h"
#include <iostream>

using namespace std;

// Constructor
File::File(TCHAR *fullPath) {
	// VERY carefully allocate and initialize to zeroes all the space that we will need
	int pathSize = _tcslen(fullPath);
	name = new TCHAR[pathSize + 1];
	memset(name, 0, sizeof(TCHAR)*(pathSize + 1));
	_tcscpy(name, fullPath);

	// Own file data
	WIN32_FIND_DATA searchData;
	// Clean the result
	memset(&searchData, 0, sizeof(WIN32_FIND_DATA));

	HANDLE handle = FindFirstFile(fullPath, &searchData);

	// Is it a directory?
	directory = (searchData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

	if (directory) {
		// VERY carefully allocate and initialize to zeroes all the space that we will need
		TCHAR *searchPath = new TCHAR[pathSize + 3*sizeof(TCHAR)];
		memset(searchPath, 0, sizeof(TCHAR)*(pathSize + 3));

		_tcscpy(searchPath, fullPath);
		_tcscat(searchPath, TEXT("\\*"));

		size = 0;
		
		HANDLE handle = FindFirstFile(searchPath, &searchData);
		// Iterate through its children
		while(handle != INVALID_HANDLE_VALUE)
		{
			// Have care to ignore /. and /..
			if (_tcscmp(searchData.cFileName, TEXT(".")) != 0 && _tcscmp(searchData.cFileName, TEXT("..")) != 0) {
				// VERY carefully allocate and initialize to zeroes all the space that we will need
				TCHAR *filePath = new TCHAR[_tcslen(fullPath) + _tcslen(searchData.cFileName) + 2];
				memset(filePath, 0, sizeof(TCHAR)*(_tcslen(fullPath) + _tcslen(searchData.cFileName) + 2));
				_tcscpy(filePath, fullPath);
				_tcscat(filePath, TEXT("\\"));
				_tcscat(filePath, searchData.cFileName);

				File *f = new File(filePath);
				children.push_back(f);
				size += f->getSize();

				delete[] filePath;
			}
			int next = FindNextFile(handle, &searchData);
			if(next == FALSE)
			break;
		}

		//Close the handle after use or memory/resource leak
		FindClose(handle);

		delete[] searchPath;
	}
	else {
		size = (searchData.nFileSizeHigh * (MAXDWORD+1)) + searchData.nFileSizeLow;
	}
}

// Desctructor
File::~File() {
	delete[] name;
}

// Name getter
TCHAR* File::getName() {
	return name;
}

// isDirectory getter
bool File::isDirectory() {
	return directory;
}

// Children list
std::list<File*>& File::getChildren() {
	return children;
}

// size getter
unsigned long File::getSize() {
	return size;
}