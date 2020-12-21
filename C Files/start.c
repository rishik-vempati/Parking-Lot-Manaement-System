#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>

#include "Test.h"

//Linking C programs
void Test(void);
void guestUser_VehicleParking(void);

void start() {
	int option, finish;
	system("cls");
    Sleep(2000);
	finish = 1;
	
	while (finish) {
		system("cls");
		createRectangularBox(45, 10, 115, 35);
		Sleep(1000);
		gotoxy(70, 13);
		printf("1.   RegisteredUser");
		gotoxy(70, 18);
		printf("2.   GuestUser");
		gotoxy(70, 23);
		printf("3.   EXIT");
		gotoxy(50, 28);
		printf("Choose your option: ");
		printf("\t\t\t");
		scanf("%d", &option);
		if (option == 1) {
			system("cls");
			Test();
		}
		else if (option == 2) {
			system("cls");
			guestUser_VehicleParking();
		}
		else if (option == 3) {
			system("cls");
			finish = 0;
		}
	}
	
	printf("Press any key to continue..");
	getch();
	system("cls");
}