﻿#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <windows.h>

#define MAX_ROWS 4
#define MAX_COLUMNS 6

typedef int BCMAT[MAX_ROWS][MAX_COLUMNS];

void fill_column(BCMAT mat, int* column_number, int number);
void fill_matrix(BCMAT mat, int* column_number, int hours, int minutes, int seconds);
void print_binary_clock(BCMAT mat);
void print_decimal_clock(struct tm* local_time);

int main(void) {
	while (1) {
		BCMAT binary_clock_matrix = {};
		int column_number = 0;

		time_t rawtime;
		time(&rawtime);
		struct tm* local_time = localtime(&rawtime);
		
		fill_matrix(binary_clock_matrix, &column_number, local_time->tm_hour, local_time->tm_min, local_time->tm_sec);
		print_binary_clock(binary_clock_matrix);
		print_decimal_clock(local_time);

		//printf("24h Binary Clock\nby @mihajloslav\n");

		Sleep(1000);
		system("cls");
	}
	return 0;
}

void fill_column(BCMAT mat, int* column_number, int number) {
	for (int i = MAX_ROWS - 1; i >= 0; i--) {
		mat[i][*column_number] = (number % 2 != 0);
		number /= 2;
	}
	(*column_number)++;
}

void fill_matrix(BCMAT mat, int* column_number, int hours, int minutes, int seconds) {
	fill_column(mat, column_number, hours / 10);
	fill_column(mat, column_number, hours % 10);
	fill_column(mat, column_number, minutes / 10);
	fill_column(mat, column_number, minutes % 10);
	fill_column(mat, column_number, seconds / 10);
	fill_column(mat, column_number, seconds % 10);
}

void print_binary_clock(BCMAT mat) {
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c\n%c", 201, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 187, 186); //201(╔), 205(═), 187(╗), 186(║)
	for (int i = 0; i < MAX_ROWS; i++) {
		for (int j = 0; j < MAX_COLUMNS; j++)
			if (j != MAX_COLUMNS - 1)
				(mat[i][j] == 1) ? printf("%c ", 254) : printf("%c ", 250); //254(■) //250(·)
			else (mat[i][j] == 1) ? printf("%c", 254) : printf("%c", 250); //254(■) //250(·)
		(i != MAX_ROWS - 1) ? printf("%c\n%c", 186, 186) : printf("%c\n", 186); //186(║)
	}
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 204, 205, 205, 205, 203, 205, 205, 205, 203, 205, 205, 205, 185); //204(╠), 205(═), 203(╦), 185(╣)
}
void print_decimal_clock(struct tm* local_time) {
	printf("%c%d %d%c%d %d%c%d %d%c\n", 186, local_time->tm_hour / 10, local_time->tm_hour % 10, 186, local_time->tm_min / 10, local_time->tm_min % 10, 186, local_time->tm_sec / 10, local_time->tm_sec % 10, 186); //186(║)
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 200, 205, 205, 205, 202, 205, 205, 205, 202, 205, 205, 205, 188); //200(╚), 205(═), 202(╩), 188(╝)
}