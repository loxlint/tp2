#include "Group.h" 
#include "Exceptions.h" 
using namespace std;


Group::Group() : groupNumber(0), students(nullptr), studentCount(0) {
	cout << "Вызван конструктор по умолчанию для группы (адрес: " << this << ")\n";
}


Group::Group(int groupNumber) : groupNumber(groupNumber), students(nullptr), studentCount(0) {
	if (groupNumber <= 0) {
		throw GroupException("Ошибка: номер группы должен быть положительным!");
	}
	cout << "Вызван конструктор с параметрами для группы #" << groupNumber << " (адрес: " << this
		<< ")\n";
}


Group::Group(const	Group& other) : groupNumber(other.groupNumber), studentCount(other.studentCount) {
	cout << "Вызван конструктор копирования для группы #" << other.groupNumber << " (адрес: " <<
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
	cout << "Вызван деструктор для группы #" << groupNumber << " (адрес: " << this << ")\n";
}


int Group::getGroupNumber() const {
	return groupNumber;
}


void Group::setGroupNumber(int number) {
	if (number <= 0) {
		throw GroupException("Ошибка: номер группы должен быть положительным!");
	}
	groupNumber = number;
}


void Group::addStudent(Student* student) {
	if (!student) {
		throw GroupException("Ошибка: указатель на студента не может быть null!");
	}


	Student** newStudents = new Student * [studentCount + 1]; for (int i = 0; i < studentCount; ++i) {
		newStudents[i] = students[i]; 
	}
	newStudents[studentCount] = student; 


	delete[] students;

	students = newStudents;


	++studentCount;


	cout << "Студент успешно добавлен в группу #" << groupNumber << ".\n";
}




void Group::addStudentAtPosition(Student* student, int position) {
	if (!student) {
		throw GroupException("Ошибка: указатель на студента не может быть null!");
	}
	if (position < 0 || position > studentCount) {
		throw GroupException("Ошибка: некорректная позиция для добавления студента!");
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


	cout << "Студент добавлен на позицию " << position + 1 << " в группе #" << groupNumber << ".\n";
}

void Group::removeStudent(int index) {
	if (index < 0 || index >= studentCount) {
		throw GroupException("Ошибка: некорректный индекс студента!");
	}


	delete students[index];
	for (int i = index; i < studentCount - 1; ++i) {
		students[i] = students[i + 1];
	}
	--studentCount;
	cout << "Студент успешно удалён из группы #" << groupNumber << ".\n";
}


void Group::showStudents() const {
	if (studentCount == 0) {
		cout << "Группа #" << groupNumber << " пуста.\n"; return;
	}


	cout << "Группа #" << groupNumber << ":\n"; for (int i = 0; i < studentCount; ++i) {
		cout << " Студент #" << i + 1 << ": " << students[i]->getSurname()
			<< ", Средний балл: " << students[i]->getAverageGrade() << "\n";
	}
}


double Group::getAverageGrade() const {
	if (studentCount == 0) {
		throw GroupException("Ошибка: невозможно вычислить средний балл для группы без студентов!");
	}


	double total = 0.0;
	for (int i = 0; i < studentCount; ++i) {
		total += students[i]->getAverageGrade();

	}
	return total / studentCount;
}


Student* Group::getStudent(int index) const {
	if (index < 0 || index >= studentCount) {
		throw GroupException("Ошибка: некорректный индекс студента!");
	}
	return students[index];
}


int Group::getStudentCount() const {
	return studentCount;
}
