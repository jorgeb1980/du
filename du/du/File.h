#ifndef __FILE_H__
#define __FILE_H__

#include <list>
#include <tchar.h>
#include <string>
#include <windows.h>

using namespace std;

// Recursive directory tree
class File {
private:
	bool directory;
	wstring name;
	std::list<File*> children;
	DWORDLONG size;
public:
	
	File::File(wstring& fullPath);
	~File();
	wstring& File::getName();
	bool File::isDirectory();
	DWORDLONG File::getSize();
	std::list<File*>& getChildren();
};

#endif