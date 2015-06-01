#ifndef __DU_CONFIG_H__
#define __DU_CONFIG_H__

// precision of the file size reading
typedef enum Precision { HUMAN_READABLE, MEGABYTES, KILOBYTES, BYTES };

// class (struct actually) with the information
class DuConfig {
public:
	bool help;
	bool all;
	bool summarize;
	Precision precision;

	DuConfig();
};

#endif