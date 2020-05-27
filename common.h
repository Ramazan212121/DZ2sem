#pragma once
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <malloc.h>
#include <locale.h>
#include "books.h"

void exchange();
void giveout();
int checkout(char*);
char* datecmp(char*, char*);

void exchange() {
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
}


void giveout() {
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
		if (strcmp(copy, isbn) == 0) {
			while (i < 4) {
				temp = strtok(NULL, ";");
				i++;
			}uval = atoi(temp);
		}

	}
	fclose(checkBook);
	FILE* datecmpr;
	datecmpr = fopen("students_books.csv", "r+");
	char* lessdate = NULL;
	char* date1 = NULL;
	char loc[100];
	char booknum[100];
	char* date;
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
			else if (j > 0 && j < 2) {
				lessdate = (char*)malloc(sizeof(date));
				lessdate = datecmp(date, date1);
			}
			else {
				date1 = NULL;
				date1 = (char*)realloc(date1, sizeof(lessdate));
				strcpy(date1, lessdate);
				lessdate = NULL;
				lessdate = (char*)realloc(lessdate, sizeof(date));
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
	k = atoi(countdate);
	l = atoi(countdate1);
	//printf("%d %d\n", k, l);
	if ((k - l) < 0) {
		return date;
	}
	else {
		return date1;
	}


}
