#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#include "Test.h"

//Global Variable
COORD co_ordinates = {0, 0};

//Linking C programs
void registeredUser_Register(void);
void registeredUser_Login(void);

void Test() {
	int option, finish;
	system("cls");
    Sleep(2000);
	finish = 1;
	
	while (finish) {
		system("cls");
		createRectangularBox(45, 10, 115, 35);
		Sleep(1000);
		gotoxy(70, 13);
		printf("1.   Register");
		gotoxy(70, 18);
		printf("2.   Login");
		gotoxy(70, 23);
		printf("3.   LOGOUT");
		gotoxy(50, 28);
		printf("Choose your option: ");
		printf("\t\t\t");
		scanf("%d", &option);
		if (option == 1) {
			system("cls");
			registeredUser_Register();
		}
		else if (option == 2) {
			system("cls");
			registeredUser_Login();
		}
		else if (option == 3) {
			system("cls");
			finish = 0;
		}
	}
	Sleep(3000);
	system("cls");
}

//Pre-Defined Function Implementation
void gotoxy(short x, short y) {
    co_ordinates.X = x;
    co_ordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), co_ordinates);
}

//Function Implementation
void createRectangularBox(int dim1, int dim2, int dim3, int dim4) {
    int i, j;

    //For Horizantal Lines
    for (i = dim1; i < dim3; i++) {
        gotoxy(i, dim2); printf("\xcd");
        gotoxy(i, dim4); printf("\xcd");
    }

    //For vertical Lines
    for (j = dim2 + 1; j < dim4; j++) {
        gotoxy(dim1, j); printf("\xba");
        gotoxy(dim3, j); printf("\xba");
    }

    gotoxy(dim1, dim2); printf("\xc9");
    gotoxy(dim3, dim2); printf("\xbb");
    gotoxy(dim1, dim4); printf("\xc8");
    gotoxy(dim3, dim4); printf("\xbc");
}
