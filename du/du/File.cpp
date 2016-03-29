#include "File.h"
#include <iostream>

// Constructor
File::File(wstring& fullPath) {

	name = fullPath;

	// Own file data
	WIN32_FIND_DATA searchData;
	// Clean the result
	memset(&searchData, 0, sizeof(WIN32_FIND_DATA));

	HANDLE handle = FindFirstFile(fullPath.c_str(), &searchData);

	// Is it a directory?
	directory = (searchData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

	if (directory) {
		wstring searchPath(fullPath);
		searchPath.append(TEXT("\\*"));

		size = 0;
		
		HANDLE handle = FindFirstFile(searchPath.c_str(), &searchData);
		// Iterate through its children
		while(handle != INVALID_HANDLE_VALUE)
		{
			// Have care to ignore /. and /..
			if (_tcscmp(searchData.cFileName, TEXT(".")) != 0 && _tcscmp(searchData.cFileName, TEXT("..")) != 0) {
				wstring filePath(fullPath);
				filePath.append(TEXT("\\"));
				filePath.append(searchData.cFileName);
				
				File *f = new File(filePath);
				children.push_back(f);
				
				size = (DWORDLONG) size + (DWORDLONG) f->getSize();
			}
			int next = FindNextFile(handle, &searchData);
			if(next == FALSE)
			break;
		}

		//Close the handle after use or memory/resource leak
		FindClose(handle);
	}
	else {
		size = (DWORDLONG) (searchData.nFileSizeHigh * (MAXDWORD+1)) + searchData.nFileSizeLow;
	}
	FindClose(handle);
}

// Desctructor
File::~File() {
	//delete[] name;
}

// Name getter
wstring& File::getName() {
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
DWORDLONG File::getSize() {
	return size;
}