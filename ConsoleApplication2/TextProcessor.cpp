#include "TextProcessor.h"
#include <iostream> 
#include <fstream>

#include <cstring> 
#include <cctype>

using namespace std;


bool isNumber(const char* str) {
	for (size_t i = 0; str[i] != '\0'; ++i) {
		if (!isdigit(str[i])) {
			return false;
		}
	}
	return true;
}


char* TextProcessor::swapAdjacentWords(const char* line) {
	size_t lineLength = strlen(line) + 1;
	char* buffer = new char[lineLength];
	strcpy_s(buffer, lineLength, line);

	size_t maxWords = 16; 
	char** words = new char* [maxWords]; 
	size_t wordCount = 0;

	char* context = nullptr;
	char* token = strtok_s(buffer, " \t\n", &context);


	while (token) {
		if (wordCount == maxWords) {
			size_t newMaxWords = maxWords * 2; char** temp = new char* [newMaxWords];
			memcpy(temp, words, maxWords * sizeof(char*)); delete[] words;

			words = temp;
			maxWords = newMaxWords;
		}
		words[wordCount++] = token;
		token = strtok_s(nullptr, " \t\n", &context);
	}


	size_t i = 0;
	while (i < wordCount - 1) {
		if (!isNumber(words[i]) && !isNumber(words[i + 1])) {
			char* temp = words[i]; words[i] = words[i + 1]; words[i + 1] = temp;
			i += 2;
		}
		else {
			i++;
		}
	}


	char* result = new char[lineLength]; strcpy_s(result, lineLength, "");

	for (size_t i = 0; i < wordCount; ++i) {
		strcat_s(result, lineLength, words[i]); if (i + 1 < wordCount) {
			strcat_s(result, lineLength, " ");
		}
	}


	delete[] words; delete[] buffer;

	return result;
}




void TextProcessor::processFile(const char* inputFile) {
	ifstream inFile(inputFile); 

	if (!inFile) {
		cerr << "Ошибка: Не удалось открыть файл " << inputFile << "\n"; return;
	}


	string line;
	while (getline(inFile, line)) { 
		char* processedLine = swapAdjacentWords(line.c_str()); 
		cout << processedLine << endl; 
		delete[] processedLine; 
	}


	inFile.close(); 
}


void TextProcessor::display(const char* inputFile) {
	ifstream inFile(inputFile); 


	if (!inFile) {
		cerr << "Ошибка: Не удалось открыть файл " << inputFile << "\n"; return;
	}


	string line;
	while (getline(inFile, line)) { 
		cout << line << endl; 

	}


	inFile.close(); 
}
