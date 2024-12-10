#ifndef STUDENT_H 
#define STUDENT_H

#include <iostream> 
#include <string> 
#include <sstream> 
#include <limits>

using namespace std;


class Student {
private:
	string surname;
	float* grades;	
	int gradesCount;		

public:
	Student(); 
	Student(const string& surname, const float* grades, int gradesCount); 
	Student(const Student& other); 
	~Student(); 


	string getSurname() const;
	void setSurname(const string& surname);


	void setGrades(const float* grades, int gradesCount); void getGrades() const;

	double getAverageGrade() const; 


	friend ostream& operator<<(ostream& out, const Student& student); 

	friend istream& operator>>(istream& in, Student& student); 
};


#endif 
