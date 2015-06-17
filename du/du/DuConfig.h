#ifndef __DU_CONFIG_H__
#define __DU_CONFIG_H__

#include <tchar.h>
#include <windows.h>
// precision of the file size reading
typedef enum Precision { HUMAN_READABLE, MEGABYTES, KILOBYTES, BYTES };

// class (struct actually) with the information
class DuConfig {
public:
	// --help
	bool help;
	// -a
	bool all;
	// -c
	bool total;
	// -s
	bool summarize;
	// -mbkh
	Precision precision;
	TCHAR *currentDirectory;

	DuConfig();
	~DuConfig();	
};

#endif