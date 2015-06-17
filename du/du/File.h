#ifndef __FILE_H__
#define __FILE_H__

#include <list>
#include <tchar.h>
#include <windows.h>

// Recursive directory tree
class File {
private:
	bool directory;
	TCHAR* name;
	std::list<File*> children;
	unsigned long size;
public:
	
	File::File(TCHAR *fullPath);
	~File();
	TCHAR* File::getName();
	bool File::isDirectory();
	unsigned long File::getSize();
	std::list<File*>& getChildren();
};

#endif