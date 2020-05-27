#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <malloc.h>
#include <locale.h>
#include "books.h"
int s;

void addStud();
void delStud();
int checkStud(char*);
void redStud();
void lookStud();
void LookAtStud();
void lookAtStud(char*);

void LookAtStud() {
	char k[2];
	system("cls");
	printf("-----Просмотр информации  книги по номеру зачетки-----\n");
	writestr(k);
	printf("\n----Введите номер зачентной книги, чтобы посмотреть информацию о студенте: ");
	writestr(numb);
	lookAtStud(numb);
}




void lookStud() {
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
}


void redStud() {
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
	fclose(delStud2);
	fclose(delStud3);
}


void delStud() {
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

		if (delline == 0 && s == 0) {
			printf("\n-------Номер такой зачетной книжки не существует!-------\n");

		}
		else if (delline != 0) {
			printf("\nСтудент успешно удален\n");
		}

		fclose(delStud2);
		fclose(delStud3);
	}
}

void addStud() {
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
void lookAtStud(char* numb) {
	FILE* lookStud;
	char lookstud[100];
	int k = 0;
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
