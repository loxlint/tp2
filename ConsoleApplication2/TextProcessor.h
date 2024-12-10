#ifndef TEXTPROCESSOR_H 
#define TEXTPROCESSOR_H

#include <string>


class TextProcessor {
public:
	static char* swapAdjacentWords(const char* line);

	static void processFile(const char* inputFile);

	static void display(const char* inputFile);
};


#endif 
