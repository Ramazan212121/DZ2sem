#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <malloc.h>
#include <locale.h>
char isbn[11];
char numb[10];
char c[2];
int l;
char data[100];
void delBook();
void addBook();
void redBook();
void changenumbooks();
int checkBook(char* );
char* writestr(char[]);
void lookinfobook();
void lookAtBook(char*);


void lookinfobook() {
	char k[2];
	system("cls");
	printf("-----Просмотр информации по книге взятых студентами-----\n");
	writestr(k);
	printf("\n----Введите номер ISBN книги, чтобы посмотреть информацию о студенте: ");
	writestr(isbn);
	lookAtBook(isbn);
}


void changenumbooks(){
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
			fclose(delBook3);
			fclose(delBook2);
}




//-----------------------Редактирование книг---------------------------------//
void redBook() {
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
}


void delBook() {
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
		l = checkBook(isbn);
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
}

void addBook() {
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
			
			

		}fclose(addBook);
		system("pause");
		system("cls");
		
}
char* writestr(char str[]) {
	int i = 0;
	int c = getchar();
	while (c != EOF && c != '\n') {
		str[i++] = c;
		c = getchar();
	}str[i] = '\0';
	return str;
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
			openStud = fopen("students.csv", "r+");
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
