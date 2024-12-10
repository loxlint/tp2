#ifndef EXCEPTIONS_H 
#define EXCEPTIONS_H

#include <exception>
#include <string>

using namespace std;


class StudentException : public exception {
private:
	string message;


public:
	explicit StudentException(const string& msg) : message(msg) {} const char* what() const noexcept override {
		return message.c_str();
	}
};


class GroupException : public exception {
private:
	string message;


public:
	explicit GroupException(const string& msg) : message(msg) {} const char* what() const noexcept override {
		return message.c_str();
	}
};


class InputException : public exception {

private:
	string message;


public:
	explicit InputException(const string& msg) : message(msg) {} const char* what() const noexcept override {
		return message.c_str();
	}
};


#endif // EXCEPTIONS_H
