#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <malloc.h>
#include <locale.h>
#include "books.h"
#include "studs.h"
#include "common.h"

char state;
char status;
int m;
int boo;
int kaunt = 0;

void logging(int, char,char*);
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
						addBook();
						logging(m, state, login);
						kaunt++;
					}
					//------------------ДОБАВЛЕНИЕ КНИГИ--------------------------------------------------------------//

					//------------------УДАЛЕНИЕ КНИГИ---------------------------------------------------------------//	
					if (state == '2') {
						delBook();
						l = 0;
						system("pause");
						system("cls");
						logging(m, state, login);
						kaunt++;

					}
					//--------------------УДАЛЕНИЕ КНИГ--------------------------------//	

				//---------------------------РЕДАКТИРОВАНИЕ КНИГ-----------------------------//
					if (state == '3') {
						redBook();
						system("pause");
						system("cls");
						logging(m, state, login);
						
						kaunt++;
					}
					//---------------------Редактирование КНИГ--------------------------//	

					//---------------------ИЗМЕНЕНИЕ КОЛИЧЕСТВА КНИГ-----------------------------//
					if (state == '4') {
						changenumbooks();
						system("pause");
						system("cls");
						logging(m, state, login);
						kaunt++;
					}
					
	//---------------------------------------ИЗМЕНЕНИЕ КОЛИЧЕСТВА КНИГ-------------------------------------------//
	//-------------------------------------------ПРОСМОТР ИНФОРМАЦИИ ПО КНИГЕ-------------------------------------//
					
					if (state == '5') {
						lookinfobook();
						kaunt++;
						logging(m, state, login);
						system("pause");
						system("cls");

				}
	//-------------------------------------------ПРОСМОТР ИНФОРМАЦИИ ПО КНИГЕ-------------------------------------//
					//-------------------------------------------------Выдача книг------------------------------------------------------------//
					if (state == '6') {
						giveout();
						logging(m, state, login);
						kaunt++;
						system("pause");
						system("cls");


					}
					//--------------------
					//-------------------------------------------------Выдача книг------------------------------------------------------------//
					//------------------------------------------------------CДАЧА КНИГ-----------------------------------------------------------------//
					if (state == '7') {
						exchange();
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
						addStud();
						logging(m, state, login);
						kaunt++;
					}
					//--------------------------ДОБАВЛЕНИЕ СТУДЕНТА---------------------------------//

					//------------------------УДАЛЕНИЕ СТУДЕНТА-------------------------------------//
					if (state == '2') {
						delStud();
						system("pause");
						system("cls"); 
						logging(m, state, login);
						kaunt++;
						l = 0;
					}

					//----------------------УДАЛЕНИЕ СТУДЕНТА-----------------------------------//
					//---------------------------РЕДАКТИРОВАНИЕ СТУДЕНТА-----------------------------//
					if (state == '3') {
						
						system("pause");
						system("cls");
						
						logging(m, state, login);
						kaunt++;
					}
					//---------------------Редактирование Студента--------------------------//
					//------------------------ПРОСМОТР ИНФОРМАЦИИ О СТУДЕНТЕ--------------------------//
					if (state == '4') {
						lookStud();
						system("pause");
						system("cls");
						kaunt++;
						logging(m, state, login);

					}

					//----------------------------ПРОСМОТР ИНФОРМАЦИИ О СТУДЕНТЕ-------------------------//
						//-------------------------------------------ПРОСМОТР ИНФОРМАЦИИ ПО КНИГАМИ ВЗЯТЫМ СТУДеНТАМИ-------------------------------------//

					if (state == '5') {
						LookAtStud();
						kaunt++;
						system("pause");
						system("cls");
						logging(m, state, login);
						//-------------------------------------------ПРОСМОТР ИНФОРМАЦИИ ПО КНИГАМИ ВЗЯТЫМ СТУДеНТАМИ-------------------------------------//
					}
	//-------------------------------------------------Выдача книг------------------------------------------------------------//
					if (state == '6') {
						giveout();
						logging(m, state, login);
						kaunt++;
						system("pause");
						system("cls");
						

					}
//-------------------------------------------------Выдача книг------------------------------------------------------------//
					//------------------------------------------------------CДАЧА КНИГ-----------------------------------------------------------------//
					if (state == '7') {
						exchange();
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


