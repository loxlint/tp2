#include "Group.h" 
#include "Exceptions.h" 
using namespace std;


Group::Group() : groupNumber(0), students(nullptr), studentCount(0) {
	cout << "������ ����������� �� ��������� ��� ������ (�����: " << this << ")\n";
}


Group::Group(int groupNumber) : groupNumber(groupNumber), students(nullptr), studentCount(0) {
	if (groupNumber <= 0) {
		throw GroupException("������: ����� ������ ������ ���� �������������!");
	}
	cout << "������ ����������� � ����������� ��� ������ #" << groupNumber << " (�����: " << this
		<< ")\n";
}


Group::Group(const	Group& other) : groupNumber(other.groupNumber), studentCount(other.studentCount) {
	cout << "������ ����������� ����������� ��� ������ #" << other.groupNumber << " (�����: " <<
		this << ")\n";
	if (other.studentCount > 0) {
		students = new Student * [other.studentCount]; for (int i = 0; i < other.studentCount; ++i) {
			students[i] = new Student(*other.students[i]);
		}
	}
	else {
		students = nullptr;
	}

}


Group::~Group() {
	for (int i = 0; i < studentCount; ++i) {
		delete students[i];
	}
	delete[] students;
	cout << "������ ���������� ��� ������ #" << groupNumber << " (�����: " << this << ")\n";
}


int Group::getGroupNumber() const {
	return groupNumber;
}


void Group::setGroupNumber(int number) {
	if (number <= 0) {
		throw GroupException("������: ����� ������ ������ ���� �������������!");
	}
	groupNumber = number;
}


void Group::addStudent(Student* student) {
	if (!student) {
		throw GroupException("������: ��������� �� �������� �� ����� ���� null!");
	}


	Student** newStudents = new Student * [studentCount + 1]; for (int i = 0; i < studentCount; ++i) {
		newStudents[i] = students[i]; 
	}
	newStudents[studentCount] = student; 


	delete[] students;

	students = newStudents;


	++studentCount;


	cout << "������� ������� �������� � ������ #" << groupNumber << ".\n";
}




void Group::addStudentAtPosition(Student* student, int position) {
	if (!student) {
		throw GroupException("������: ��������� �� �������� �� ����� ���� null!");
	}
	if (position < 0 || position > studentCount) {
		throw GroupException("������: ������������ ������� ��� ���������� ��������!");
	}


	Student** newStudents = new Student * [studentCount + 1]; for (int i = 0, j = 0; i < studentCount + 1; ++i) {
		if (i == position) {
			newStudents[i] = student; 
		}
		else {
			newStudents[i] = students[j++]; 
		}
	}


	delete[] students; students = newStudents;
	++studentCount;


	cout << "������� �������� �� ������� " << position + 1 << " � ������ #" << groupNumber << ".\n";
}

void Group::removeStudent(int index) {
	if (index < 0 || index >= studentCount) {
		throw GroupException("������: ������������ ������ ��������!");
	}


	delete students[index];
	for (int i = index; i < studentCount - 1; ++i) {
		students[i] = students[i + 1];
	}
	--studentCount;
	cout << "������� ������� ����� �� ������ #" << groupNumber << ".\n";
}


void Group::showStudents() const {
	if (studentCount == 0) {
		cout << "������ #" << groupNumber << " �����.\n"; return;
	}


	cout << "������ #" << groupNumber << ":\n"; for (int i = 0; i < studentCount; ++i) {
		cout << " ������� #" << i + 1 << ": " << students[i]->getSurname()
			<< ", ������� ����: " << students[i]->getAverageGrade() << "\n";
	}
}


double Group::getAverageGrade() const {
	if (studentCount == 0) {
		throw GroupException("������: ���������� ��������� ������� ���� ��� ������ ��� ���������!");
	}


	double total = 0.0;
	for (int i = 0; i < studentCount; ++i) {
		total += students[i]->getAverageGrade();

	}
	return total / studentCount;
}


Student* Group::getStudent(int index) const {
	if (index < 0 || index >= studentCount) {
		throw GroupException("������: ������������ ������ ��������!");
	}
	return students[index];
}


int Group::getStudentCount() const {
	return studentCount;
}
