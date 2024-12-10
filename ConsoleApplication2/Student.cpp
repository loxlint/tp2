#include "Student.h" 
#include "Exceptions.h"

Student::Student() : surname("Unknown"), grades(nullptr), gradesCount(0) {
	cout << "Вызван конструктор по умолчанию для Student: " << this << "\n";
}


Student::Student(const string& surname, const float* grades, int gradesCount)
	: surname(surname), gradesCount(gradesCount) {
	if (gradesCount <= 0) {
		throw StudentException("Некорректное количество оценок!");
	}


	this->grades = new float[gradesCount]; for (int i = 0; i < gradesCount; ++i) {
		this->grades[i] = grades[i];
	}
	cout << "Вызван конструктор с параметрами для Student: " << this << "\n";
}


Student::Student(const Student& other) : surname(other.surname), gradesCount(other.gradesCount) { grades = new float[gradesCount];
for (int i = 0; i < gradesCount; ++i) {
	grades[i] = other.grades[i];
}
cout << "Вызван конструктор копирования для Student: " << this << "\n";
}

Student::~Student() {

cout << "Вызван деструктор для Student: " << this << "\n"; delete[] grades;
}


string Student::getSurname() const {
	return surname;
}


void Student::setSurname(const string& surname) {
	this->surname = surname;
}


void Student::setGrades(const float* grades, int gradesCount) {
	if (gradesCount <= 0) {
		throw StudentException("Количество оценок должно быть положительным!");
	}


	delete[] this->grades;
	this->gradesCount = gradesCount;
	this->grades = new float[gradesCount]; for (int i = 0; i < gradesCount; ++i) {
		this->grades[i] = grades[i];
	}
}


void Student::getGrades() const {
	for (int i = 0; i < gradesCount; ++i) {
		cout << grades[i] << " ";
	}
	cout << endl;
}

double Student::getAverageGrade() const {
if (gradesCount == 0) return 0.0; float sum = 0;
for (int i = 0; i < gradesCount; ++i) {

	sum += grades[i];
}
return static_cast<double>(sum) / gradesCount;
}


ostream& operator<<(ostream& out, const Student& student) {
	out << "Фамилия и инициалы: " << student.surname << "\n"; out << "Оценки: ";
	for (int i = 0; i < student.gradesCount; ++i) {
		out << student.grades[i] << " ";
	}
	out << "\nСредний балл: " << student.getAverageGrade() << "\n"; return out;
}


istream& operator>>(istream& in, Student& student) {
	cout << "Введите фамилию и инициалы: "; getline(in, student.surname);

	cout << "Введите количество оценок: "; in >> student.gradesCount;

	if (in.fail() || student.gradesCount <= 0) {
		in.clear(); 
		in.ignore(numeric_limits<streamsize>::max(), '\n'); 
		throw InputException("Ошибка: некорректное количество оценок!");
	}


	delete[] student.grades;
	student.grades = new float[student.gradesCount];


	cout << "Введите оценки через пробел: "; for (int i = 0; i < student.gradesCount; ++i) {
		in >> student.grades[i]; if (in.fail()) {
			in.clear();

			in.ignore(numeric_limits<streamsize>::max(), '\n'); throw InputException("Ошибка ввода оценок!");
		}
	}


	in.ignore(numeric_limits<streamsize>::max(), '\n'); 
	return in;
}
