#ifndef GROUP_H
#define GROUP_H

#include <iostream> 
#include "Student.h"

class Group {
private:
	int groupNumber;	
	Student** students;	
	int studentCount;	
public:
	Group();	
	Group(int groupNumber);	
	Group(const Group& other);		
	~Group();	

	int getGroupNumber() const;
	void setGroupNumber(int number); 


	void addStudent(Student* student);
	void addStudentAtPosition(Student* student, int position); 
	void removeStudent(int index); void showStudents() const; double getAverageGrade() const;
	Student* getStudent(int index) const; int getStudentCount() const;

};


#endif 
