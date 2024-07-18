//Modular Binary Clock in C
//Made by @mihajloslav
//Source Code: https://github.com/mihajloslav/BinaryClockInC
#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#define SLEEP(ms) Sleep(ms)
#define CLEAR_SCREEN() system("cls")
#else
#include <unistd.h>
#define SLEEP(ms) sleep(ms)
#define CLEAR_SCREEN() system("clear")
#endif

#include <stdio.h>
#include <time.h>

#define BORDER_TOP_LEFT     201 // ╔
#define BORDER_HORIZONTAL   205 // ═
#define BORDER_TOP_RIGHT    187 // ╗
#define BORDER_VERTICAL     186 // ║
#define BORDER_BOTTOM_LEFT  200 // ╚
#define BORDER_BOTTOM_RIGHT 188 // ╝
#define BORDER_CROSS_LEFT   204 // ╠
#define BORDER_CROSS_RIGHT  185 // ╣
#define BORDER_CROSS_TOP    203 // ╦
#define BORDER_CROSS_BOTTOM 202 // ╩

#define BLOCK               254 // ■
#define DOT                 250 // ·

#define PRINT_YEARS() printf("%-2d%-2d%-2d%d%c", (local_time->tm_year + 1900) / 1000, ((local_time->tm_year + 1900) / 100) % 10, ((local_time->tm_year + 1900) / 10) % 10, (local_time->tm_year + 1900) % 10, BORDER_VERTICAL)
#define PRINT_MONTHS() printf("%-2d%d%c", (local_time->tm_mon + 1)  / 10, (local_time->tm_mon + 1) % 10, BORDER_VERTICAL)
#define PRINT_DAYS() printf("%-2d%d%c", local_time->tm_mday / 10, local_time->tm_mday % 10, BORDER_VERTICAL)
#define PRINT_HOURS() printf("%-2d%d%c", local_time->tm_hour / 10, local_time->tm_hour % 10, BORDER_VERTICAL);
#define PRINT_MINUTES() printf("%-2d%d%c", local_time->tm_min / 10, local_time->tm_min % 10, BORDER_VERTICAL);
#define PRINT_SECONDS() printf("%-2d%d%c", local_time->tm_sec / 10, local_time->tm_sec % 10, BORDER_VERTICAL);

#define WITHYEAR 1 //0 OR 1

#define MAX_ROWS 10
#define MAX_COLUMNS 20

typedef int BCMAT[MAX_ROWS][MAX_COLUMNS];

typedef enum border_type { TOP, MIDDLE, BOTTOM } BORDER;

void fill_column(BCMAT mat, int* column_number, int number);
void fill_matrix(BCMAT mat, int* column_number, int years, int months, int days, int hours, int minutes, int seconds);
void printer_border_type(BORDER border_type);
void print_binary_clock(BCMAT mat);
void print_decimal_clock(struct tm* local_time);

int main(void) {
	while (1) {
		BCMAT binary_clock_matrix;
		int column_number = 0;

		time_t rawtime;
		time(&rawtime);
		struct tm* local_time = localtime(&rawtime);
		fill_matrix(binary_clock_matrix, &column_number, local_time->tm_year + 1900, local_time->tm_mon + 1, local_time->tm_mday, local_time->tm_hour, local_time->tm_min, local_time->tm_sec);
		print_binary_clock(binary_clock_matrix);
		print_decimal_clock(local_time);

		printf("Binary Clock in C\nMade by @mihajloslav\nSource Code: https://github.com/mihajloslav/BinaryClockInC");
		SLEEP(1000);
		CLEAR_SCREEN();
	}
	return 0;
}

void fill_column(BCMAT mat, int* column_number, int number) {
	for (int i = MAX_ROWS - 1; i >= 0; i--) {
		mat[i][*column_number] = number % 2;
		number /= 2;
	}
	(*column_number)++;
}

void fill_matrix(BCMAT mat, int* column_number, int year, int months, int day, int hours, int minutes, int seconds) {
	int numbers[] = { year / 1000, (year / 100) % 10, (year / 10) % 10, year % 10, months / 10, months % 10,  day / 10, day % 10, hours / 10 , hours % 10, minutes / 10, minutes % 10, seconds / 10, seconds % 10 };
	for (int i = 0; i < sizeof(numbers) / sizeof(int); i++)
		fill_column(mat, column_number, numbers[i]);
}

void printer_border_type(BORDER border_type) {
	switch (border_type)
	{
	case TOP: { //╔═══════════════════════╗
		printf("%c", BORDER_TOP_LEFT);
		for (int i = 0; i < MAX_COLUMNS + MAX_COLUMNS - 1; i++)
			printf("%c", BORDER_HORIZONTAL);
		printf("%c\n%c", BORDER_TOP_RIGHT, BORDER_VERTICAL);
		break;
	}
	case MIDDLE: {//╠═══╦═══╦═══╦═══╦═══╦═══╣
		printf("%c", BORDER_CROSS_LEFT);
		char count = 0;
		char withyear = WITHYEAR;
		for (int i = 0; i < MAX_COLUMNS + MAX_COLUMNS - 1; i++) {
			if (withyear) {
				if (count == 7) {
					printf("%c", BORDER_CROSS_TOP);
					withyear = count = 0;
				}
				else {
					printf("%c", BORDER_HORIZONTAL);
					count++;
				}
			}
			else {
				if (count == 3) {
					printf("%c", BORDER_CROSS_TOP);
					count = 0;
				}
				else {
					printf("%c", BORDER_HORIZONTAL);
					count++;
				}
			}
		}
		printf("%c\n", BORDER_CROSS_RIGHT);
		break;
	}
	case BOTTOM: { //╚═══╩═══╩═══╩═══╩═══╩═══╝
		printf("%c", BORDER_BOTTOM_LEFT);
		char count = 0;
		char withyear = WITHYEAR;
		for (int i = 0; i < MAX_COLUMNS + MAX_COLUMNS - 1; i++) {
			if (withyear) {
				if (count == 7) {
					printf("%c", BORDER_CROSS_BOTTOM);
					withyear = count = 0;
				}
				else {
					printf("%c", BORDER_HORIZONTAL);
					count++;
				}
			}
			else {
				if (count == 3) {
					printf("%c", BORDER_CROSS_BOTTOM);
					count = 0;
				}
				else {
					printf("%c", BORDER_HORIZONTAL);
					count++;
				}
			}
		}
		printf("%c\n", BORDER_BOTTOM_RIGHT);
		break;
	}
	}
}

void print_binary_clock(BCMAT mat) {
	printer_border_type(TOP);
	for (int i = 0; i < MAX_ROWS; i++) {
		for (int j = 0; j < MAX_COLUMNS; j++)
			if (j != MAX_COLUMNS - 1)
				(mat[i][j] == 1) ? printf("%c ", BLOCK) : printf("%c ", DOT);
			else (mat[i][j] == 1) ? printf("%c", BLOCK) : printf("%c", DOT);
		(i != MAX_ROWS - 1) ? printf("%c\n%c", BORDER_VERTICAL, BORDER_VERTICAL) : printf("%c\n", BORDER_VERTICAL);
	}
	printer_border_type(MIDDLE);
}
void print_decimal_clock(struct tm* local_time) {
	int count = 1;
	char end = 0;
	printf("%c", BORDER_VERTICAL);
	for (int i = 1; i < MAX_COLUMNS + MAX_COLUMNS + 1; i++) {
		if (end) {
			if (i % 4 == 0 || i == MAX_COLUMNS + MAX_COLUMNS)
				printf("%c", BORDER_VERTICAL);
			else printf("%c", ' ');
		}
		else {
			switch (i)
			{
			case 8: {
				PRINT_YEARS();
				break;
			} 
			case 12: {
				PRINT_MONTHS();
				break;
			}
			case 16: {
				PRINT_DAYS();
				break;
			}
			case 20: {
				PRINT_HOURS();
				break;
			}
			case 24: {
				PRINT_MINUTES();
				break;
			}
			case 28: {
				PRINT_SECONDS();
				end = 1;
				break;
			}
			}
		}
	}
	printf("\n");
	printer_border_type(BOTTOM);
}