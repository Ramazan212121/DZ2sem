#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <malloc.h>
#include <locale.h>

char state;
char status;
int m;
int l;
int s;
int boo;
int kaunt = 0;

void logging(int, char,char*);
int checkStud(char*);
char* datecmp(char* , char* );
int checkout(char*);
int checkBook(char*);
char* writestr(char[]);
void lookAtStud(char*);
void lookAtBook(char*);
int MainMenustd();
int MainMenu();

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");
	system("cls");
	FILE* users;
	users = fopen("users.csv", "r+");
	char data[100];
	char book[5];
	char studs[5];
	char login[100];
	char passwd[100];
	int arr = 0;
		printf("Введите логин: ");
		writestr(login);
		while (fgets(data, 100, users)) {
			char cpy[100];
			char* tmp;
			strcpy(cpy, data);
			tmp = strtok(cpy, ";");
			if (strcmp(login, tmp) == 0) {
				printf("Введите пароль: ");
				arr++;
				tmp = strtok(NULL, ";");
				writestr(passwd);
				if (strcmp(passwd, tmp) != 0) {
						printf("Пароль неверный, попробуйте еще раз: ");
						return 0;
				}
				else {
						tmp = strtok(NULL, ";");
						strcpy(book, tmp);
						tmp = strtok(NULL, ";");
						strcpy(studs, tmp);
						break;
				}
				
				
			}
		}if (arr == 0) {
			printf("Данного пользователя нет\n\nПопробуйте еще раз!\n\n");
			return 0;
		}
	

		while (status != '0') {
			char isbn[11];
			char numb[7];
			char c[2];
			system("cls");
			if (kaunt != 0) {
				writestr(c);
			}
			if (book[0] == '1' && studs[0] == '1') {
				printf("----------Главное меню-------------\n");
				printf("(1) Меню книг\n");
				printf("(2) Меню студентов\n");
				printf("(0) Выйти\n");
				printf("    Ваш Выбор: ");
				status = getc(stdin);
				while (true) {
					if (status == '1') {
						system("cls");
						m=MainMenu();
						break;
					}
					else if (status == '2') {
						system("cls");
						m=MainMenustd();
						break;
					}
					else if (status == '0') {
						printf("\n----------До связи----------");
						return 0;

					}
					else {
						printf("\nВведите другую цифру: ");
						status = getc(stdin);
					}
				}
			}
			else if (book[0] == '1' && studs[0] != '1') {
				m = 1;
			}
			else if (book[0] != '1' && studs[0] == '1') {
				m = 2;
			}
			if (kaunt != 0) {
				kaunt = 0;
				state = NULL;
			}

			while (state != '0') {
				if (m == 1) {
					if (kaunt!=0 ||(book[0] != '1' || studs[0] != '1')) {
						MainMenu();
					}
					state = getc(stdin);
					//--------------------------------------ДОБАВЛЕНИЕ КНИГИ--------------------------------------------------------------//
					if (state == '1') {
						char k[2];
						system("cls");
						printf("-----Добавление книг-----\n");
						writestr(k);
						printf("\nВведите номер ISBN: ");
						writestr(isbn);
						FILE* addBook;
						if (!(addBook = fopen("books.csv", "r+"))) {
							printf("Есть косяк!");
						}
						char line[1024];
						int count = 0;
						while (fgets(line, 1025, addBook)) {
							char* temp;
							temp = strtok(line, ";");
							if (strcmp(isbn, temp) == 0) {
								printf("\nКнига с таким номером ISBN уже существует!\n");
								system("pause");
								count++;
								system("cls");
							}

						}if (count == 0) {
							printf("\nВведите фамилию автора: ");
							char sur[100];
							writestr(sur);
							printf("\nВведите название книги: ");
							char name[100];
							writestr(name);
							printf("\nВведите количество книг: ");
							char quan[100];
							writestr(quan);
							fprintf(addBook, "\n%s;%s;%s;%s;%s", isbn, sur, name, quan, quan);
							printf("Книга успешно добавлена!\n");
							system("pause");
							system("cls");
							fclose(addBook);

						}
						logging(m, state, login);
						kaunt++;
					}
					//------------------ДОБАВЛЕНИЕ КНИГИ--------------------------------------------------------------//

					//------------------УДАЛЕНИЕ КНИГИ---------------------------------------------------------------//	
					if (state == '2') {
						char k[2];
						system("cls");
						printf("-----Удаление книг-----\n");
						writestr(k);
						printf("\nВведите номер ISBN книги, которую хотите удалить: ");
						writestr(isbn);
						FILE* delBook;
						if (!(delBook = fopen("books.csv", "r+"))) {
							printf("Есть косяк!");
						}
						char line[100];
						char buf[100];
						int delline = 0;
						
						FILE* delBook1;
						if (!(delBook1 = fopen("books1.csv", "w+"))) {
							printf("Есть косяк!");
						}

						while (fgets(line, 100, delBook)) {
							l=checkBook(isbn);
							if (l == 1) {
								printf("Эта книга занята, удалить невозможно!\n");
								break;
							}
							else {
								char* temp;
								char copy[100];
								strncpy(copy, line, sizeof(line));
								temp = strtok(copy, ";");
								if (strcmp(isbn, temp) != 0) {
									fprintf(delBook1, "%s", line);
								}
								else {
									delline++;
								}
							}
						}fclose(delBook);
						fclose(delBook1);
						if (l == 0) {
							FILE* delBook2;
							if (!(delBook2 = fopen("books1.csv", "r+"))) {
								printf("Есть косяк!");
							}
							FILE* delBook3;
							if (!(delBook3 = fopen("books.csv", "w+"))) {
								printf("Есть косяк!");
							}
							while (fgets(buf, 100, delBook2)) {
								fprintf(delBook3, "%s", buf);
							}

							if (delline == 0 && l == 0) {
								printf("\n-------Книги с таким ISBN нет!-------\n");

							}
							else if (delline != 0) {
								printf("\nКнига успешно удалена\n");
							}
							
							fclose(delBook2);
							fclose(delBook3);
						}
						l = 0;
						system("pause");
						system("cls");
						logging(m, state, login);
						kaunt++;

					}
					//--------------------УДАЛЕНИЕ КНИГ--------------------------------//	

				//---------------------------РЕДАКТИРОВАНИЕ КНИГ-----------------------------//
					if (state == '3') {
						char k[2];
						system("cls");
						printf("-----Редактирование книги-----\n");
						writestr(k);
						printf("\nВведите номер ISBN книги, которую хотите редактировать: ");
						writestr(isbn);
						FILE* delBook;
						if (!(delBook = fopen("books.csv", "r+"))) {
							printf("Есть косяк!");
						}
						char line[100];
						char buf[100];
						int i;
						i = checkBook(isbn);
						int delline = 0;
						if (i == 0) {
							FILE* delBook1;
							if (!(delBook1 = fopen("books1.csv", "w+"))) {
								printf("Есть косяк!");
							}

							while (fgets(line, 100, delBook)) {
								char* temp;
								char copy[100];
								strncpy(copy, line, sizeof(line));
								temp = strtok(copy, ";");
								if (strcmp(isbn, temp) != 0) {
									fprintf(delBook1, "%s", line);
								}
								else {
									char sur[100];
									printf("------Введите фамилию автора------\n");
									writestr(sur);
									char name[100];
									printf("------Введите название произведения------\n");
									writestr(name);
									char atal[10];
									printf("------Введите количество книг------\n");
									writestr(atal);
									fprintf(delBook1, "%s;%s;%s;%s;%s\n", temp, sur, name, atal, atal);
									delline++;
								}
							}fclose(delBook);
							fclose(delBook1);
							FILE* delBook2;
							if (!(delBook2 = fopen("books1.csv", "r+"))) {
								printf("Есть косяк!");
							}
							FILE* delBook3;
							if (!(delBook3 = fopen("books.csv", "w+"))) {
								printf("Есть косяк!");
							}
							while (fgets(buf, 100, delBook2)) {
								fprintf(delBook3, "%s", buf);
							}fclose(delBook2);
							fclose(delBook3);

							if (delline == 0) {
								printf("\n-------Книги с таким ISBN нет!-------\n");

							}
							else {
								printf("\n-------Книга успешно редактированна------\n");
							}
						}
						else {
							printf("Невозможно редактировать книгу, так как она есть у студента(ов)!\n");
						}
						system("pause");
						system("cls");
						logging(m, state, login);
						
						kaunt++;
					}
					//---------------------Редактирование КНИГ--------------------------//	

					//---------------------ИЗМЕНЕНИЕ КОЛИЧЕСТВА КНИГ-----------------------------//
					if (state == '4') {
						char k[2];
						system("cls");
						printf("-----Изменение количества книг-----\n");
						writestr(k);
						printf("\nВведите номер ISBN книги, количество которой нужно изменить: ");
						writestr(isbn);
						FILE* delBook;
						if (!(delBook = fopen("books.csv", "r+"))) {
							printf("Есть косяк!");
						}
						char line[100];
						char buf[100];
						int i = 0;
						int delline = 0;
						FILE* delBook1;
						if (!(delBook1 = fopen("books1.csv", "w+"))) {
							printf("Есть косяк!");
						}

						while (fgets(line, 100, delBook)) {
							char* temp;
							char copy[100];
							strncpy(copy, line, sizeof(line));
							temp = strtok(copy, ";");
							if (strcmp(isbn, temp) != 0) {
								fprintf(delBook1, "%s", line);
							}
							else {
								temp = strtok(NULL, ";");
								char sur[100];
								strcpy(sur, temp);
								char name[100];
								temp = strtok(NULL, ";");
								strcpy(name, temp);
								char atal[10];
								temp = strtok(NULL, ";");
								char prev[10];
								strcpy(prev, temp);
								printf("\n------Введите новое количество книг---------\n");
								printf(" Новое количество: ");
								temp = strtok(NULL, ",");
								writestr(atal);
								while (1) {

									if (atoi(prev) - atoi(atal) > atoi(temp) && atoi(prev) > atoi(atal)) {
										printf("Недопустимое количество книг, введите еще раз: ");
										writestr(atal);
									}
									else {
										break;
									}
								}
								int c;
								c = atoi(atal) - atoi(prev) + atoi(temp);

								fprintf(delBook1, "%s;%s;%s;%s;%d\n", isbn, sur, name, atal, c);
								delline++;

							}
						}fclose(delBook);
						fclose(delBook1);
						FILE* delBook2;
						if (!(delBook2 = fopen("books1.csv", "r+"))) {
							printf("Есть косяк!");
						}
						FILE* delBook3;
						if (!(delBook3 = fopen("books.csv", "w+"))) {
							printf("Есть косяк!");
						}
						while (fgets(buf, 100, delBook2)) {
							fprintf(delBook3, "%s", buf);
						}

						if (delline == 0) {
							printf("\n-------Книги с таким ISBN нет!-------\n");

						}
						else {
							printf("\n-------Количество книг успешно изменено!-----\n");
						}
						system("pause");
						system("cls");
						fclose(delBook2);
						logging(m, state, login);
						fclose(delBook3);
						kaunt++;
					}
					
	//---------------------------------------ИЗМЕНЕНИЕ КОЛИЧЕСТВА КНИГ-------------------------------------------//
	//-------------------------------------------ПРОСМОТР ИНФОРМАЦИИ ПО КНИГЕ-------------------------------------//
					
					if (state == '5') {
					char k[2];
					system("cls");
					printf("-----Просмотр информации по книге взятых студентами-----\n");
					writestr(k);
					printf("\n----Введите номер ISBN книги, чтобы посмотреть информацию о студенте: ");
					writestr(isbn);
					lookAtBook(isbn);
					kaunt++;
					logging(m, state, login);
					system("pause");
					system("cls");

				}
	//-------------------------------------------ПРОСМОТР ИНФОРМАЦИИ ПО КНИГЕ-------------------------------------//
					//-------------------------------------------------Выдача книг------------------------------------------------------------//
					if (state == '6') {
						char k[2];
						int f;
						int q = 0;
						char date[10];
						char bufer[100];
						system("cls");
						printf("-----Выдача книг-----\n");
						writestr(k);
						FILE* newBook;
						newBook = fopen("students_books.csv", "r+");

						printf("\n----Введите номер ISBN: ");
						writestr(isbn);
						f = checkout(isbn);
						if (f == 1) {
							printf("\n----Введите номер зачентной книжки: ");
							writestr(numb);
							while (fgets(bufer, 100, newBook)) {
								char* temp;
								temp = strtok(bufer, ";");
								if (strcmp(temp, isbn) == 0) {
									temp = strtok(NULL, ";");
									if (strcmp(temp, numb) == 0) {
										q++;
										printf("Эта книга уже взята этим студентом\n");
									}
								}
							}if (q == 0) {
								printf("\n----Введите дату сдачи книги в формате dd.mm.yy: ");
								writestr(date);
								fprintf(newBook, "\n%s;%s;%s", isbn, numb, date);
							}
							FILE* delBook;
							if (!(delBook = fopen("books.csv", "r+"))) {
								printf("Есть косяк!");
							}
							char line[100];
							char buf[100];
							int i = 0;
							int delline = 0;
							FILE* delBook1;
							if (!(delBook1 = fopen("books1.csv", "w+"))) {
								printf("Есть косяк!");
							}

							while (fgets(line, 100, delBook)) {
								char* temp;
								char copy[100];
								strncpy(copy, line, sizeof(line));
								temp = strtok(copy, ";");
								if (strcmp(isbn, temp) != 0) {
									fprintf(delBook1, "%s", line);
								}
								else {
									temp = strtok(NULL, ";");
									char sur[100];
									strcpy(sur, temp);
									char name[100];
									temp = strtok(NULL, ";");
									strcpy(name, temp);
									temp = strtok(NULL, ";");
									char prev[10];
									strcpy(prev, temp);
									temp = strtok(NULL, ";");
									int c;
									c = atoi(temp);
									c--;
									fprintf(delBook1, "%s;%s;%s;%s;%d\n", isbn, sur, name, prev, c);
									delline++;

								}
							}fclose(delBook);
							fclose(delBook1);
							FILE* delBook2;
							if (!(delBook2 = fopen("books1.csv", "r+"))) {
								printf("Есть косяк!");
							}
							FILE* delBook3;
							if (!(delBook3 = fopen("books.csv", "w+"))) {
								printf("Есть косяк!");
							}
							while (fgets(buf, 100, delBook2)) {
								fprintf(delBook3, "%s", buf);
							}fclose(delBook2);
							fclose(delBook3);
						}
						fclose(newBook);
						logging(m, state, login);
						kaunt++;
						system("pause");
						system("cls");


					}
					//--------------------
					//-------------------------------------------------Выдача книг------------------------------------------------------------//
					//------------------------------------------------------CДАЧА КНИГ-----------------------------------------------------------------//
					if (state == '7') {
						char k[2];
						system("cls");
						printf("-----Сдача книги-----\n");
						writestr(k);
						printf("\nВведите номер ISBN, номер книги которой вы хотите сдать: ");
						writestr(isbn);
						FILE* eXchange;
						if (!(eXchange = fopen("students_books.csv", "r+"))) {
							printf("Есть косяк!");
						}printf("Введите номер зачетки студента, который сдает книгу: ");
						writestr(numb);
						char line[100];
						int qq = 0;
						int qi = 0;
						while (fgets(line, 100, eXchange)) {
							char* temp;
							char copy[100];
							strncpy(copy, line, sizeof(line));
							temp = strtok(copy, ";");
							if (strcmp(isbn, temp) == 0) {
								if (qq == 0) {
									qq++;
								}
								temp = strtok(NULL, ";");
								if (strcmp(numb, temp) == 0) {
									qq++;
								}

							}

						}fclose(eXchange);
						if (qq == 2) {
							FILE* wrtstudbook;
							if (!(wrtstudbook = fopen("students_books.csv", "r+"))) {
								printf("Есть косяк!");
							}FILE* delstudbook;
							if (!(delstudbook = fopen("students_books1.csv", "w+"))) {
								printf("Есть косяк!");
							}

							while (fgets(line, 100, wrtstudbook)) {
								char copys[100];
								char* temp;
								strcpy(copys, line);
								temp = strtok(copys, ";");
								if (strcmp(temp, isbn) != 0) {
									fprintf(delstudbook, "%s", line);
								}
								else {
									temp = strtok(NULL, ";");
									if (strcmp(temp, numb) != 0) {
										fprintf(delstudbook, "%s", line);
									}
								}
							}fclose(wrtstudbook);
							fclose(delstudbook);
							FILE* newwrtstudbook;
							if (!(newwrtstudbook = fopen("students_books.csv", "w+"))) {
								printf("Есть косяк!");
							}FILE* newdelstudbook;
							if (!(newdelstudbook = fopen("students_books1.csv", "r+"))) {
								printf("Есть косяк!");
							}while (fgets(line, 100, newdelstudbook)) {
								fprintf(newwrtstudbook, "%s", line);
							}
							fclose(newwrtstudbook);
							fclose(newdelstudbook);
							FILE* delBook;
							if (!(delBook = fopen("books.csv", "r+"))) {
								printf("Есть косяк!");
							}
							char lines[100];
							char buf[100];
							char bufer[100];
							FILE* delBook1;
							if (!(delBook1 = fopen("books1.csv", "w+"))) {
								printf("Есть косяк!");
							}

							while (fgets(lines, 100, delBook)) {
								char* temp;
								strncpy(buf, lines, sizeof(line));
								temp = strtok(buf, ";");
								if (strcmp(isbn, temp) != 0) {
									fprintf(delBook1, "%s", lines);
								}
								else {
									temp = strtok(NULL, ";");
									char sur[100];
									strcpy(sur, temp);
									char name[100];
									temp = strtok(NULL, ";");
									strcpy(name, temp);
									char atal[10];
									temp = strtok(NULL, ";");
									strcpy(atal, temp);
									char prev[10];
									temp = strtok(NULL, ";");
									strcpy(prev, temp);
									int c;
									c = atoi(prev);
									c++;
									fprintf(delBook1, "%s;%s;%s;%s;%d\n", isbn, sur, name, atal, c);

								}
							}fclose(delBook);
							fclose(delBook1);
							FILE* delBook2;
							if (!(delBook2 = fopen("books1.csv", "r+"))) {
								printf("Есть косяк!");
							}
							FILE* delBook3;
							if (!(delBook3 = fopen("books.csv", "w+"))) {
								printf("Есть косяк!");
							}
							while (fgets(bufer, 100, delBook2)) {
								fprintf(delBook3, "%s", bufer);
							}fclose(delBook2);
							fclose(delBook3);

						}if (qq == 1) {
							printf("У данного студента нет этой книги!\n");
						}if (qq == 0) {
							printf("Эта книга находится в библиотке!\n");
						}
						system("pause");
						system("cls");
						kaunt++;
						logging(m, state, login);
					}
					//--------------------------------------------------СДАЧА КНИГ----------------------------------------------------------------------//
				if (state == '0') {
					kaunt++;
					logging(m, state, login);
					if (book[0] == '1' && studs[0] != '1') {
						status = '0';
					}
					else if (book[0] != '1' && studs[0] == '1') {
						status = '0';
					}
					break;

				}
				}
			//--------------------------------------ДОБАВЛЕНИЕ СТУДЕНТА----------------------------------------------------//
				if (m == 2) {
					if (kaunt!=0 || (book[0] != '1' || studs[0] != '1')) {
						MainMenustd();
					}
					state = getc(stdin);
					if (state == '1') {
						char k[2];
						system("cls");
						printf("-----Добавление студента-----\n");
						writestr(k);
						printf("\nВведите номер зачетной книжки: ");
						writestr(numb);
						FILE* addStud;
						if (!(addStud = fopen("students.csv", "r+"))) {
							printf("Есть косяк!");
						}
						char line[100];
						int count = 0;
						while (fgets(line, 1025, addStud)) {
							char* temp;
							temp = strtok(line, ";");
							if (strcmp(isbn, temp) == 0) {
								printf("\nЭтот студент уже есть в базе данных!\n");
								system("pause");
								count++;
								system("cls");
							}

						}if (count == 0) {
							printf("\nВведите фамилию студента: ");
							char sur[100];
							writestr(sur);
							printf("\nВведите имя студента: ");
							char name[100];
							writestr(name);
							printf("\nВведите отчество студента: ");
							char patr[100];
							writestr(patr);
							printf("\nВведите факультет: ");
							char fac[5];
							writestr(fac);
							printf("\nВведите специальность: ");
							char spec[100];
							writestr(spec);
							fprintf(addStud, "\n%s;%s;%s;%s;%s;%s", numb, sur, name, patr, fac, spec);
							printf("Студент успешно добавлен!\n");
							system("pause");
							system("cls");
							fclose(addStud);

						}
						logging(m, state, login);
						kaunt++;
					}
					//--------------------------ДОБАВЛЕНИЕ СТУДЕНТА---------------------------------//

					//------------------------УДАЛЕНИЕ СТУДЕНТА-------------------------------------//
					if (state == '2') {
						char k[2];
						system("cls");
						printf("-----Удаление студента из базы-----\n");
						writestr(k);
						printf("\nВведите номер зачтной книги, по которой хотите удалить студента: ");
						writestr(numb);
						FILE* delStud;
						if (!(delStud = fopen("students.csv", "r+"))) {
							printf("Есть косяк!");
						}
						char line[100];
						char buf[100];
						int delline = 0;
						FILE* delStud1;
						if (!(delStud1 = fopen("students1.csv", "w+"))) {
							printf("Есть косяк!");
						}

						while (fgets(line, 100, delStud)) {
							s = checkStud(numb);
							if (s == 1) {
								printf("У этого студента есть книга , удаление невозможно!\n");
								break;
							}
							else {
								char* temp;
								char copy[100];
								strncpy(copy, line, sizeof(line));
								temp = strtok(copy, ";");
								if (strcmp(numb, temp) != 0) {
									fprintf(delStud1, "%s", line);
								}
								else {
									delline++;
								}
							}
						}fclose(delStud);
						fclose(delStud1);
						if (s == 0) {
							FILE* delStud2;
							if (!(delStud2 = fopen("students1.csv", "r+"))) {
								printf("Есть косяк!");
							}
							FILE* delStud3;
							if (!(delStud3 = fopen("students.csv", "w+"))) {
								printf("Есть косяк!");
							}
							while (fgets(buf, 100, delStud2)) {
								fprintf(delStud3, "%s", buf);
							}

							if (delline == 0 && s==0) {
								printf("\n-------Номер такой зачетной книжки не существует!-------\n");

							}
							else if(delline!=0){
								printf("\nСтудент успешно удален\n");
							}
							
							fclose(delStud2);
							fclose(delStud3);
						}
						system("pause");
						system("cls"); 
						logging(m, state, login);
						kaunt++;
						l = 0;
					}

					//----------------------УДАЛЕНИЕ СТУДЕНТА-----------------------------------//
					//---------------------------РЕДАКТИРОВАНИЕ СТУДЕНТА-----------------------------//
					if (state == '3') {
						char k[2];
						system("cls");
						printf("-----Редактирование студента-----\n");
						writestr(k);
						printf("\nВведите номер зачетной книги, по которой хотите редактировать информацию о студенте: ");
						writestr(numb);
						FILE* delStud;
						if (!(delStud = fopen("students.csv", "r+"))) {
							printf("Есть косяк!");
						}
						char line[100];
						char buf[100];
						int delline = 0;
						FILE* delStud1;
						if (!(delStud1 = fopen("students1.csv", "w+"))) {
							printf("Есть косяк!");
						}

						while (fgets(line, 100, delStud)) {
							char* temp;
							char copy[100];
							strncpy(copy, line, sizeof(line));
							temp = strtok(copy, ";");
							if (strcmp(numb, temp) != 0) {
								fprintf(delStud1, "%s", line);
							}
							else {
								printf("\nВведите фамилию студента: ");
								char sur[100];
								writestr(sur);
								printf("\nВведите имя студента: ");
								char name[100];
								writestr(name);
								printf("\nВведите отчество студента: ");
								char patr[100];
								writestr(patr);
								printf("\nВведите факультет: ");
								char fac[5];
								writestr(fac);
								printf("\nВведите специальность: ");
								char spec[100];
								writestr(spec);
								fprintf(delStud1, "%s;%s;%s;%s;%s;%s\n", numb, sur, name, patr, fac, spec);
								delline++;
							}
						}fclose(delStud);
						fclose(delStud1);
						FILE* delStud2;
						if (!(delStud2 = fopen("students1.csv", "r+"))) {
							printf("Есть косяк!");
						}
						FILE* delStud3;
						if (!(delStud3 = fopen("students.csv", "w+"))) {
							printf("Есть косяк!");
						}
						while (fgets(buf, 100, delStud2)) {
							fprintf(delStud3, "%s", buf);
						}

						if (delline == 0) {
							printf("\n-------Зачетной книги с таким номером нет!-------\n");

						}
						else {
							printf("\n-------Студент успешно редактирован------\n");
						}
						system("pause");
						system("cls");
						fclose(delStud2);
						fclose(delStud3);
						logging(m, state, login);
						kaunt++;
					}
					//---------------------Редактирование Студента--------------------------//
					//------------------------ПРОСМОТР ИНФОРМАЦИИ О СТУДЕНТЕ--------------------------//
					if (state == '4') {
						char k[2];
						system("cls");
						printf("-----Просмотр информации о студенте-----\n");
						writestr(k);
						printf("\nВведите номер зачетной книги, по которой хотите просмотреть информацию о студенте: ");
						writestr(numb);
						FILE* lookStud;
						if (!(lookStud = fopen("students.csv", "r+"))) {
							printf("Есть косяк!");
						}
						char line[100];
						char buf[100];
						int delline = 0;
						while (fgets(line, 100, lookStud)) {
							char* temp;
							char copy[100];
							strncpy(copy, line, sizeof(line));
							temp = strtok(copy, ";");
							if (strcmp(numb, temp) == 0) {
								delline++;
								fprintf(stdout, "%s, ", temp);
								int i = 0;
								while (i < 5) {
									temp = strtok(NULL, ";");
									if (i == 2 || i == 3) {
										fprintf(stdout, "%s, ", temp);
									}
									else {
										fprintf(stdout, "%s ", temp);
									}i++;

								}
							}

						}if (delline == 0) {
							printf("\nСтудента с таким номером зачетной книги не существует!\n");
						}fclose(lookStud);
						system("pause");
						system("cls");
						kaunt++;
						logging(m, state, login);

					}

					//----------------------------ПРОСМОТР ИНФОРМАЦИИ О СТУДЕНТЕ-------------------------//
						//-------------------------------------------ПРОСМОТР ИНФОРМАЦИИ ПО КНИГАМИ ВЗЯТЫМ СТУДеНТАМИ-------------------------------------//

					if (state == '5') {
						char k[2];
						system("cls");
						printf("-----Просмотр информации  книги по номеру зачетки-----\n");
						writestr(k);
						printf("\n----Введите номер зачентной книги, чтобы посмотреть информацию о студенте: ");
						writestr(numb);
						lookAtStud(numb);
						kaunt++;
						system("pause");
						system("cls");
						logging(m, state, login);
						//-------------------------------------------ПРОСМОТР ИНФОРМАЦИИ ПО КНИГАМИ ВЗЯТЫМ СТУДеНТАМИ-------------------------------------//
					}
	//-------------------------------------------------Выдача книг------------------------------------------------------------//
					if (state == '6') {
						char k[2];
						int f;
						int q = 0;
						char date[10];
						char bufer[100];
						system("cls");
						printf("-----Выдача книг-----\n");
						writestr(k);
						FILE* newBook;
						newBook = fopen("students_books.csv", "r+");

						printf("\n----Введите номер ISBN: ");
						writestr(isbn);
						f = checkout(isbn);
						if (f == 1) {
							printf("\n----Введите номер зачентной книжки: ");
							writestr(numb);
							while (fgets(bufer, 100, newBook)) {
								char* temp;
								temp = strtok(bufer, ";");
								if (strcmp(temp, isbn) == 0) {
									temp = strtok(NULL, ",");
									if (strcmp(temp, numb) == 0) {
										q++;
										printf("Эта книга уже взята этим студентом\n");
									}
								}
							}
							if (q == 0) {
								printf("\n----Введите дату сдачи книги в формате dd.mm.yy: ");
								writestr(date);
								fprintf(newBook, "\n%s;%s;%s", isbn, numb, date);
								fclose(newBook);
								FILE* delBook;
								if (!(delBook = fopen("books.csv", "r+"))) {
									printf("Есть косяк!");
								}
								char line[100];
								char buf[100];
								FILE* delBook1;
								if (!(delBook1 = fopen("books1.csv", "w+"))) {
									printf("Есть косяк!");
								}

								while (fgets(line, 100, delBook)) {
									char* temp;
									char copy[100];
									strncpy(copy, line, sizeof(line));
									temp = strtok(copy, ";");
									if (strcmp(isbn, temp) != 0) {
										fprintf(delBook1, "%s", line);
									}
									else {
										temp = strtok(NULL, ";");
										char sur[100];
										strcpy(sur, temp);
										char name[100];
										temp = strtok(NULL, ";");
										strcpy(name, temp);
										temp = strtok(NULL, ";");
										char prev[10];
										strcpy(prev, temp);
										temp = strtok(NULL, ";");
										int c;
										c = atoi(temp);
										c--;
										char kek[10];
										_itoa(c,kek,10);
										fprintf(delBook1, "%s;%s;%s;%s;%s\n", isbn, sur, name, prev, kek);

									}
								}fclose(delBook);
								fclose(delBook1);
								FILE* delBook2;
								if (!(delBook2 = fopen("books1.csv", "r+"))) {
									printf("Есть косяк!");
								}
								FILE* delBook3;
								if (!(delBook3 = fopen("books.csv", "w+"))) {
									printf("Есть косяк!");
								}
								while (fgets(buf, 100, delBook2)) {
									fprintf(delBook3, "%s", buf);
								}fclose(delBook2);
								fclose(delBook3);
							}
						}
						else {
							printf("Данной книги нет в библиотеке!\n");
						}
						logging(m, state, login);
						kaunt++;
						system("pause");
						system("cls");
						

					}
//-------------------------------------------------Выдача книг------------------------------------------------------------//
					//------------------------------------------------------CДАЧА КНИГ-----------------------------------------------------------------//
					if (state == '7') {
						char k[2];
						system("cls");
						printf("-----Сдача книги-----\n");
						writestr(k);
						printf("\nВведите номер ISBN, номер книги которой вы хотите сдать: ");
						writestr(isbn);
						FILE* eXchange;
						if (!(eXchange = fopen("students_books.csv", "r+"))) {
							printf("Есть косяк!");
						}printf("Введите номер зачетки студента, который сдает книгу: ");
						writestr(numb);
						char line[100];
						int qq = 0;
						int qi = 0;
						while (fgets(line, 100, eXchange)) {
							char* temp;
							char copy[100];
							strncpy(copy, line, sizeof(line));
							temp = strtok(copy, ";");
							if (strcmp(isbn, temp) == 0) {
								if ( qq==0) {
									qq++;
								}
								temp = strtok(NULL, ";");
								if (strcmp(numb, temp) == 0) {
									qq++;
								}

							}

						}fclose(eXchange);
						if (qq == 2) {
							FILE* wrtstudbook;
							if (!(wrtstudbook = fopen("students_books.csv", "r+"))) {
								printf("Есть косяк!");
							}FILE* delstudbook;
							if (!(delstudbook = fopen("students_books1.csv", "w+"))) {
								printf("Есть косяк!");
							}

							while (fgets(line, 100, wrtstudbook)) {
								char copys[100];
								char* temp;
								strcpy(copys, line);
								temp = strtok(copys, ";");
								if (strcmp(temp, isbn) != 0) {
									fprintf(delstudbook, "%s", line);
								}
								else {
									temp = strtok(NULL, ";");
									if (strcmp(temp, numb) != 0) {
										fprintf(delstudbook, "%s", line);
									}
								}
							}fclose(wrtstudbook);
							fclose(delstudbook);
							FILE* newwrtstudbook;
							if (!(newwrtstudbook = fopen("students_books.csv", "w+"))) {
								printf("Есть косяк!");
							}FILE* newdelstudbook;
							if (!(newdelstudbook = fopen("students_books1.csv", "r+"))) {
								printf("Есть косяк!");
							}while (fgets(line, 100, newdelstudbook)) {
								fprintf(newwrtstudbook, "%s", line);
							}
							fclose(newwrtstudbook);
							fclose(newdelstudbook);
							FILE* delBook;
							if (!(delBook = fopen("books.csv", "r+"))) {
								printf("Есть косяк!");
							}
							char lines[100];
							char buf[100];
							char bufer[100];
							FILE* delBook1;
							if (!(delBook1 = fopen("books1.csv", "w+"))) {
								printf("Есть косяк!");
							}

							while (fgets(lines, 100, delBook)) {
								char* temp;
								strncpy(buf, lines, sizeof(line));
								temp = strtok(buf, ";");
								if (strcmp(isbn, temp) != 0) {
									fprintf(delBook1, "%s", lines);
								}
								else {
									temp = strtok(NULL, ";");
									char sur[100];
									strcpy(sur, temp);
									char name[100];
									temp = strtok(NULL, ";");
									strcpy(name, temp);
									char atal[10];
									temp = strtok(NULL, ";");
									strcpy(atal, temp);
									char prev[10];
									temp = strtok(NULL, ";");
									strcpy(prev, temp);
									int c;
									c = atoi(prev);
									c++;
									fprintf(delBook1, "%s;%s;%s;%s;%d\n", isbn, sur, name, atal, c);

								}
							}fclose(delBook);
							fclose(delBook1);
							FILE* delBook2;
							if (!(delBook2 = fopen("books1.csv", "r+"))) {
								printf("Есть косяк!");
							}
							FILE* delBook3;
							if (!(delBook3 = fopen("books.csv", "w+"))) {
								printf("Есть косяк!");
							}
							while (fgets(bufer, 100, delBook2)) {
								fprintf(delBook3, "%s", bufer);
							}fclose(delBook2);
							fclose(delBook3);

						}if (qq == 1) {
							printf("У данного студента нет этой книги!\n");
						}if (qq == 0) {
							printf("Эта книга находится в библиотке!\n");
						}
						system("pause");
						system("cls");
						kaunt++;
						logging(m, state, login);
					}
					//--------------------------------------------------СДАЧА КНИГ----------------------------------------------------------------------//

					if (state == '0') {
						logging(m, state, login);
						if (book[0] == '1' && studs[0] != '1') {
							status = '0';
						}
						else if (book[0] != '1' && studs[0] == '1') {
							status = '0';
						}
						kaunt++;
						break;
					}
				}
				
			}
		}
}
	
int checkBook(char* isbn) {
	FILE* checkBook;
	char checkline[100];
	if (!(checkBook = fopen("students_books.csv", "r+"))) {
		printf("Есть косяк!");
	}
	while (fgets(checkline, 100, checkBook)) {
		char* tmp;
		tmp = strtok(checkline, ";");
		if (strcmp(tmp, isbn) == 0) {
			fclose(checkBook);
			return 1;
		}
	}
	fclose(checkBook);
	return 0;
}
int checkStud(char* numb) {
	FILE* checkStud;
	char checkstud[100];
	if (!(checkStud = fopen("students_books.csv", "r+"))) {
		printf("Есть косяк!");
	}
	while (fgets(checkstud, 100, checkStud)) {
		char* tmp;
		tmp = strtok(checkstud, ";");
		tmp = strtok(NULL, ";");
		if (strcmp(tmp, numb) == 0) {
			fclose(checkStud);
			return 1;
		}
	}
	fclose(checkStud);
	return 0;
}
int checkout(char* isbn) {
	int uval;
	FILE* checkBook;
	if (!(checkBook = fopen("books.csv", "r+"))) {
		printf("Есть косяк!");
	}
	char line[100];
	
	char buf[100];
	while (fgets(line, 100, checkBook)) {
		int i = 0;
		char copy[100];
		char* temp;
		temp = strtok(line, ";");
		strcpy(copy, temp);
		if (strcmp(copy, isbn)==0) {
			while (i < 4) {
				temp = strtok(NULL, ";");
				i++;
			}uval = atoi(temp);
		}
		
	}
	fclose(checkBook);
	FILE* datecmpr;
	datecmpr = fopen("students_books.csv", "r+");
	char *lessdate=NULL;
	char *date1=NULL;
	char loc[100];
	char booknum[100];
	char *date;
	int j = 0;
	while (fgets(buf, 100, datecmpr)) {
		char* tmp;
		strcpy(loc, buf);
		tmp = strtok(loc, ";");
		strcpy(booknum, tmp);
		tmp = strtok(NULL, ";");
		tmp = strtok(NULL, ";");
		date = (char*)malloc(sizeof(tmp));
		strcpy(date, tmp);
		if (strcmp(isbn, booknum) == 0) {
			
				if (j == 0) {
					date1 = (char*)malloc(sizeof(date));
					strcpy(date1, date); 
					
				}
				else if (j > 0 && j<2) {
					lessdate = (char*)malloc(sizeof(date));
					lessdate = datecmp(date, date1);
				}
				else  {
					date1 = NULL;
					date1 = (char*)realloc(date1,sizeof(lessdate));
					strcpy(date1, lessdate);
					lessdate = NULL;
					lessdate = (char*)realloc(lessdate,sizeof(date));
					lessdate = datecmp(date, date1);

				}
				
				j++;
		}
		
	}
	if (uval == 0) {
			printf("\nДанной книги в библиотеке пока нет, ближайшая дата возврата: %s\n", lessdate);
			return 0;
	}
	else {
		return 1;
	}
	free(date1);
	free(date);
	free(lessdate);
	fclose(datecmpr);
}
void logging(int f, char state, char* login) {
	FILE* logging;
	logging = fopen("logging.log", "a+");
	time_t s_time;
	struct tm* m_time;
	char str_t[100];
	s_time = time(NULL);
	m_time = localtime(&s_time);
	strftime(str_t, 128, "%d.%m.%y %H:%M:%S", m_time);

	if (f == 1) {
		if (state == '0') {
			fprintf(logging, "%s;%s;%s\n", str_t, login, "Выход");
		}if (state == '1') {
			fprintf(logging, "%s;%s;%s\n", str_t, login, "Добавление книги");
		}if (state == '2') {
			fprintf(logging, "%s;%s;%s\n", str_t, login, "Удаление книги");
		}if (state == '3') {
			fprintf(logging, "%s;%s;%s\n", str_t, login, "Редактирование книги");
		}if (state == '4') {
			fprintf(logging, "%s;%s;%s\n", str_t, login, "Изменение количества книг");
		}if (state == '5') {
			fprintf(logging, "%s;%s;%s\n", str_t, login, "Просмотр информации о студентах, с книгами");
		}
	}if (f == 2) {
		if (state == '0') {
			fprintf(logging, "%s;%s;%s\n", str_t, login, "Выход");
		}if (state == '1') {
			fprintf(logging, "%s;%s;%s\n", str_t, login, "Добавление студента");
		}if (state == '2') {
			fprintf(logging, "%s;%s;%s\n", str_t, login, "Удаление студента");
		}if (state == '3') {
			fprintf(logging, "%s;%s;%s\n", str_t, login, "Редактирование информации о студенте");
		}if (state == '4') {
			fprintf(logging, "%s;%s;%s\n", str_t, login, "Просмотр информации о студенте");
		}if (state == '5') {
			fprintf(logging, "%s;%s;%s\n", str_t, login, "Просмотр книг у студента");
		}
	}if (state == '6') {
		fprintf(logging, "%s;%s;%s\n", str_t, login, "Выдача книги");
	}if (state == '7') {
		fprintf(logging, "%s;%s;%s\n", str_t, login, "Сдача книги");
	}
	fclose(logging);
}



char* datecmp(char* date, char* date1) {
	char* y1, * m1, * d1, * y, * m, * d;
	int k, l;
	char copydate[10];
	char countdate[10];
	char countdate1[10];
	char copydate1[10];
	strcpy(copydate, date);
	strcpy(copydate1, date1);
	d = strtok(copydate, ".");
	m = strtok(NULL, ".");
	y = strtok(NULL, ".");
	y[2] = '\0';
	d1 = strtok(copydate1, ".");
	m1 = strtok(NULL, ".");
	y1 = strtok(NULL, ".");
	y1[2] = '\0';
	strcpy(countdate, y);
	strcat(countdate, m);
	strcat(countdate, d);
	strcpy(countdate1, y1);
	strcat(countdate1, m1);
	strcat(countdate1, d1);
	k=atoi(countdate);
	l=atoi(countdate1);
	//printf("%d %d\n", k, l);
	if ((k - l) < 0) {
		return date;
	}
	else {
		return date1;
	}


}

void lookAtStud(char* numb) {
	FILE* lookStud;
	char lookstud[100];
	int k=0;
	char openbook[100];
	if (!(lookStud = fopen("students_books.csv", "r+"))) {
		printf("Есть косяк!");
	}while (fgets(lookstud, 100, lookStud)) {
		char* tmp;
		tmp = strtok(lookstud, ";");
		char book[15];
		strcpy(book, tmp);
		tmp = strtok(NULL, ";");
		if (strcmp(tmp, numb) == 0) {
			tmp = strtok(NULL, ";");
			k++;
			char date[10];
			strcpy(date, tmp);
			FILE* openBook;
			openBook = fopen("books.csv", "r+");
			while (fgets(openbook, 100, openBook)) {
				char* temp;
				char copy[100];
				strcpy(copy, openbook);
				temp = strtok(copy, ";");
				if (strcmp(temp, book) == 0) {
					printf("\n%s\n", openbook);
				}
			}fclose(openBook);
			printf("Дата сдачи: %s\n", date);
		}
		
	}if (k == 0) {
		printf("\nЭтот студент не брал книги!\n");
	}
	fclose(lookStud);
}


void lookAtBook(char* isbn) {
	FILE* lookBook;
	char lookbook[100];
	char openstud[100];
	int k = 0;
	if (!(lookBook = fopen("students_books.csv", "r+"))) {
		printf("Есть косяк!");
	}while (fgets(lookbook, 100, lookBook)) {
		char* tmp;
		tmp = strtok(lookbook, ";");
		if (strcmp(tmp, isbn) == 0) {
			k++;
			tmp = strtok(NULL, ";");
			char num[10];
			strcpy(num, tmp); 
			tmp = strtok(NULL, ";");
			char date[10];
			strcpy(date, tmp);
			FILE* openStud;
			openStud=fopen("students.csv","r+");
			while (fgets(openstud, 100, openStud)) {
				char* temp;
				char copy[100];
				strcpy(copy, openstud);
				temp = strtok(copy, ";");
				if (strcmp(temp, num) == 0) {
					printf("\n%s\n", openstud);
				}
			}fclose(openStud);
			printf("Дата сдачи: %s\n", date);
		}
		
	}if (k == 0) {
		printf("\nЭта книга еще не была взята студентами!\n");
	}
	fclose(lookBook);
}


	

char* writestr(char str[]) {
	int i=0;
	int c=getchar();
	while (c  != EOF && c != '\n') {
		str[i++] = c;
		c = getchar();
	}str[i] = '\0';
	return str;
}

int MainMenu() {
	printf("-------Книжное меню-------\n\n");
	printf("(1) Добавить новую книгу\n");
	printf("(2) Удалить книгу\n");
	printf("(3) Редактировать информацию по книге\n");
	printf("(4) Изменить количество книг по номеру ISBN\n");
	printf("(5) Просмотреть информацию студентов по номеру ISBN\n");
	printf("(6) Выдача книг\n");
	printf("(7) Сдача книги\n");
	printf("(0) Выйти\n");
	printf("    Ваш выбор: ");
	return 1;
}

int MainMenustd() {
	printf("\n-------Студентечское меню-------\n\n");
	printf("(1) Добавить нового студента\n");
	printf("(2) Удалить студента\n");
	printf("(3) Редактировать информацию по студенту\n");
	printf("(4) Посмотреть информацию по студенту\n");
	printf("(5) Просмотреть информацию книг по номеру зачетной книжки\n");
	printf("(6) Выдача книг\n");
	printf("(7) Сдача книги\n");
	printf("(0) Выйти\n");
	printf("    Ваш выбор: ");
	return 2;
	
}

