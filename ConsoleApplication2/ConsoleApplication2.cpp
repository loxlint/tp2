#include <iostream>
#include <limits> 
#include <algorithm> 
#include "Group.h" 
#include "Exceptions.h"
#include "TextProcessor.h"

using namespace std;



void createGroup(Group**& groups, int& groupCount, int& groupCapacity);
void deleteGroup(Group**& groups, int& groupCount);
void addStudentToGroup(Group** groups, int groupCount); 
void editGroup(Group** groups, int groupCount);
void editStudentInGroup(Group** groups, int groupCount);

void deleteStudentFromGroup(Group** groups, int groupCount);

void addGroupAtPosition(Group**& groups, int& groupCount, int& groupCapacity); void addStudentAtPosition(Group** groups, int groupCount);
void showGroups(Group** groups, int groupCount);

void showHighAchievers(Group** groups, int groupCount);



int main() {
	setlocale(LC_ALL, "Rus");


	int groupCapacity = 2; int groupCount = 0;
	Group** groups = new Group * [groupCapacity];



	TextProcessor processor;

	const char* inputFile = "Text.txt";



	while (true) {

		cout << "Главное меню:\n";

		cout << "1. Задание 1: Работа с группами и студентами\n"; 
		cout << "2. Задание 2: Обработка текста из файла\n";
		cout << "0. Выход\n";

		cout << "Ваш выбор: ";

		int choice; 
		cin >> choice;

		system("cls");
		cin.ignore();



		if (choice == 0) {

			cout << "Выход из программы.\n"; break;
		}

		else if (choice == 1) {

			while (true) {

				cout << "Меню задания 1:\n"; cout << "1. Создать группу\n"; cout << "2. Удалить группу\n";
				cout << "3. Добавить студента в группу\n"; cout << "4. Редактировать группу\n";
				cout << "5. Редактировать студента в группе\n"; cout << "6. Удалить студента из группы\n";
				cout << "7. Добавить студента на определённую позицию в группе\n"; cout << "8. Показать все группы\n";
				cout << "9. Показать студентов с баллом > 4.0\n"; cout << "0. Назад в главное меню\n";
				cout << "Ваш выбор: ";

				int subChoice; 
				cin >> subChoice;
				system("cls");
				cin.ignore();



				if (subChoice == 0) {


					break;

				}



				try {

					switch (subChoice) {
					case 1:
						createGroup(groups, groupCount, groupCapacity); break;
					case 2:

						deleteGroup(groups, groupCount); break;
					case 3:

						addStudentToGroup(groups, groupCount); break;
					case 4:

						editGroup(groups, groupCount); break;
					case 5:

						editStudentInGroup(groups, groupCount); break;
					case 6:

						deleteStudentFromGroup(groups, groupCount); break;

					case 7:

						addStudentAtPosition(groups, groupCount); break;
					case 8:

						showGroups(groups, groupCount); break;
					case 9:

						showHighAchievers(groups, groupCount); break;
					default:

						cout << "Ошибка: некорректный выбор.\n";

					}

				}

				catch (const exception& e) {

					cout << "Ошибка: " << e.what() << "\n";

				}

			}

		}

		else if (choice == 2) {


			system("cls");

			while (true) {

				cout << "\nМеню:\n";

				cout << "1. Вывести текст из файла\n";

				cout << "2. Вывести текст с изменением порядка слов\n"; cout << "0. Выход\n";
				cout << "Выберите действие: ";



				int subChoice; 


				cin >> subChoice;

				if (subChoice == 0) {

					cout << "Возврат в главное меню.\n";

					break; 

				}


				system("cls");

				switch (subChoice) {
				case 1:
					processor.display(inputFile);
					break;
				case 2:

					processor.processFile(inputFile); 
					break;


				default:

					cout << "Некорректный ввод. Попробуйте снова.\n";

				}

			}

		}





	}


	for (int i = 0; i < groupCount; ++i) {
		delete groups[i];
	}

	delete[] groups;

	return 0;

}



void createGroup(Group**& groups, int& groupCount, int& groupCapacity) {
	if (groupCount == groupCapacity) {
		groupCapacity *= 2;

		Group** newGroups = new Group * [groupCapacity]; for (int i = 0; i < groupCount; ++i) {
			newGroups[i] = groups[i];

		}

		delete[] groups; groups = newGroups;
	}



	int groupNumber;

	cout << "Введите номер группы: ";

	cin >> groupNumber;



	groups[groupCount++] = new Group(groupNumber); cout << "Группа успешно создана.\n";



	sort(groups, groups + groupCount, [](Group* a, Group* b) { return a->getGroupNumber() < b->getGroupNumber();
		});

	cout << "Группы упорядочены по возрастанию номера.\n";

}


void deleteGroup(Group**& groups, int& groupCount) {
	if (groupCount == 0) {
		throw GroupException("Список групп пуст. Удалять нечего.");

	}



	cout << "Введите номер группы для удаления: ";

	int groupNumber; cin >> groupNumber;


	for (int i = 0; i < groupCount; ++i) {

		if (groups[i]->getGroupNumber() == groupNumber) {
			delete groups[i];
			for (int j = i; j < groupCount - 1; ++j) {
				groups[j] = groups[j + 1];
			}

			--groupCount;

			cout << "Группа успешно удалена.\n"; return;
		}

	}



	throw GroupException("Группа с указанным номером не найдена.");

}




void addStudentToGroup(Group** groups, int groupCount) {

	if (groupCount == 0) {

		cout << "Список групп пуст. Сначала создайте группу.\n"; return;
	}



	cout << "Введите номер группы, куда хотите добавить студента: ";

	int groupNumber; cin >> groupNumber;


	if (cin.fail()) {

		cin.clear(); 
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
		cout << "Ошибка: некорректный ввод номера группы.\n";
		return;

	}



	cin.ignore(); 




	Group* targetGroup = nullptr;

	for (int i = 0; i < groupCount; ++i) {

		if (groups[i]->getGroupNumber() == groupNumber) {
			targetGroup = groups[i];
			break;

		}

	}



	if (!targetGroup) {

		cout << "Группа с указанным номером не найдена.\n"; return;
	}




	Student* newStudent = new Student(); try {
		cout << "Введите данные студента:\n";

		cin >> *newStudent; 

		targetGroup->addStudent(newStudent); 

	}

	catch (const exception& e) {

		delete newStudent; 
		cout << "Ошибка: " << e.what() << "\n";
	}

}



void editGroup(Group** groups, int groupCount) {
	if (groupCount == 0) {
		throw GroupException("Список групп пуст. Редактировать нечего.");

	}



	cout << "Введите номер группы для редактирования: ";

	int groupNumber; 
	cin >> groupNumber;


	for (int i = 0; i < groupCount; ++i) {

		if (groups[i]->getGroupNumber() == groupNumber) {

			cout << "Введите новый номер для группы #" << groupNumber << ": "; int newNumber;
			cin >> newNumber;

			groups[i]->setGroupNumber(newNumber);




			sort(groups, groups + groupCount, [](Group* a, Group* b) { return a->getGroupNumber() < b->getGroupNumber();
				});



			cout << "Номер группы успешно изменён и группы упорядочены.\n"; return;
		}

	}



	throw GroupException("Группа с указанным номером не найдена.");

}




void editStudentInGroup(Group** groups, int groupCount) {
	if (groupCount == 0) {
		cout << "Список групп пуст. Создайте группу сначала.\n"; return;
	}



	cout << "Введите номер группы: ";

	int groupNumber;

	cin >> groupNumber;



	if (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "Ошибка: некорректный ввод номера группы.\n"; return;
	}



	Group* targetGroup = nullptr;

	for (int i = 0; i < groupCount; ++i) {

		if (groups[i]->getGroupNumber() == groupNumber) {
			targetGroup = groups[i];
			break;

		}

	}



	if (!targetGroup) {

		cout << "Группа с указанным номером не найдена.\n"; return;
	}



	cout << "Введите номер студента для редактирования: ";

	int studentIndex; cin >> studentIndex;


	if (cin.fail()) {

		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Ошибка: некорректный ввод номера студента.\n"; return;
	}




	if (studentIndex <= 0 || studentIndex > targetGroup->getStudentCount()) {
		cout << "Ошибка: некорректный номер студента.\n";
		return;

	}



	Student* studentToEdit = targetGroup->getStudent(studentIndex - 1); if (!studentToEdit) {
		cout << "Ошибка: студент не найден.\n"; return;
	}



	cout << "Редактирование студента:\n";

	cin.ignore(); 

	try {

		cin >> *studentToEdit; 

		cout << "Студент успешно отредактирован.\n";

	}

	catch (const exception& e) {

		cout << "Ошибка при редактировании студента: " << e.what() << "\n";

	}

}


void deleteStudentFromGroup(Group** groups, int groupCount) {
	if (groupCount == 0) {
		throw GroupException("Список групп пуст. Удалять нечего.");

	}



	cout << "Введите номер группы: ";

	int groupNumber; cin >> groupNumber;


	for (int i = 0; i < groupCount; ++i) {

		if (groups[i]->getGroupNumber() == groupNumber) {
			cout << "Введите номер студента для удаления: "; int studentIndex;
			cin >> studentIndex;



			groups[i]->removeStudent(studentIndex - 1);

			cout << "Студент успешно удалён из группы #" << groupNumber << ".\n"; return;
		}

	}



	throw GroupException("Группа с указанным номером не найдена.");

}



void addGroupAtPosition(Group**& groups, int& groupCount, int& groupCapacity) {
	if (groupCount == groupCapacity) {

		groupCapacity *= 2;

		Group** newGroups = new Group * [groupCapacity]; for (int i = 0; i < groupCount; ++i) {
			newGroups[i] = groups[i];

		}

		delete[] groups; groups = newGroups;
	}



	int position, groupNumber;

	cout << "Введите позицию для новой группы (1-" << groupCount + 1 << "): "; cin >> position;


	if (position < 1 || position > groupCount + 1) {

		throw InputException("Некорректная позиция.");

	}



	cout << "Введите номер новой группы: ";

	cin >> groupNumber;



	for (int i = groupCount; i >= position; --i) {
		groups[i] = groups[i - 1];
	}



	groups[position - 1] = new Group(groupNumber);

	++groupCount;




	sort(groups, groups + groupCount, [](Group* a, Group* b) { return a->getGroupNumber() < b->getGroupNumber();
		});

	cout << "Группа успешно добавлена и группы упорядочены по возрастанию номера.\n";

}




void addStudentAtPosition(Group** groups, int groupCount) {
	if (groupCount == 0) {
		cout << "Список групп пуст. Создайте группу сначала.\n"; return;
	}



	try {

		cout << "Введите номер группы: ";

		int groupNumber; cin >> groupNumber;


		if (cin.fail()) {

			throw InputException("Ошибка ввода! Некорректный номер группы.");

		}



		// Поиск группы

		Group* targetGroup = nullptr;

		for (int i = 0; i < groupCount; ++i) {

			if (groups[i]->getGroupNumber() == groupNumber) {
				targetGroup = groups[i];
				break;

			}

		}



		if (!targetGroup) {

			throw GroupException("Группа с указанным номером не найдена.");

		}



		cout << "Введите позицию для нового студента (1-" << targetGroup->getStudentCount() + 1 << "):";

			int position; 
			cin >> position;


		if (cin.fail() || position < 1 || position > targetGroup->getStudentCount() + 1) {

			throw InputException("Ошибка ввода! Некорректная позиция для добавления студента.");

		}



		Student* newStudent = new Student(); 

		cout << "Введите данные студента:\n";

		cin.ignore(); 

		cin >> *newStudent; 



		try {

			targetGroup->addStudentAtPosition(newStudent, position - 1); 

			cout << "Студент успешно добавлен на позицию " << position << " в группе #" << groupNumber
				<< ".\n";

		}

		catch (const exception& e) {

			delete newStudent; 
			throw; 

		}

	}

	catch (const InputException& e) {

		cout << "Ошибка ввода: " << e.what() << "\n"; cin.clear(); 
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
	}

	catch (const GroupException& e) {

		cout << "Ошибка с группой: " << e.what() << "\n";

	}

	catch (const exception& e) {

		cout << "Произошла ошибка: " << e.what() << "\n";

	}

}




void showGroups(Group** groups, int groupCount) {
	if (groupCount == 0) {
		cout << "Список групп пуст.\n"; return;
	}



	for (int i = 0; i < groupCount; ++i) {
		groups[i]->showStudents();
		cout << "	\n";

	}

}


void showHighAchievers(Group** groups, int groupCount) {
	if (groupCount == 0) {
		cout << "Список групп пуст.\n"; return;
	}



	for (int i = 0; i < groupCount; ++i) {
		Group* group = groups[i];
		cout << "Группа #" << group->getGroupNumber() << ":\n";



		bool found = false; 

		for (int j = 0; j < group->getStudentCount(); ++j) {
			Student* student = group->getStudent(j);
			if (student->getAverageGrade() > 4.0) {

				cout << " Студент #" << (j + 1) << ": " 

					<< student->getSurname()

					<< ", Средний балл: " << student->getAverageGrade() << "\n"; found = true;
			}

		}



		if (!found) {

			cout << " Нет студентов со средним баллом больше 4.0.\n";

		}



		cout << "	\n";

	}

}

