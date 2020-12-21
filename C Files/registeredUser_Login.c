#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>

#include "Test.h"
//Defining a Macro
#define ENTER 13

//Global Variables
char Name[50], watchword[8];

//Functions Prototype
int userInformation(int countWrongUserName, int countWrongPassword);
int checkName(char *userName);
int checkPassword(char *userName, char *password);

//Linking C programs
void registeredUser_CarParking(char** userName_password);

void registeredUser_Login(void) {
	int countWrongUserName = 0, countWrongPassword = 0;
	int finalResult = userInformation(countWrongUserName, countWrongPassword);
	char** userName_password;
	if (finalResult == 1) {
		userName_password = (char**)malloc(2 * sizeof(char *));
		for (int i = 0; i < 2; i++) {
			userName_password[i] = (char*)malloc(30 * sizeof(char));
		}
		strcpy(userName_password[0], Name);
		strcpy(userName_password[1], watchword);
		registeredUser_CarParking(userName_password);
	}
}

//Functions Implementation
int userInformation(int countWrongUserName, int countWrongPassword) {
	system("cls");
	//Variables for username and password
	char userName[50], password[50];
	int result1, result2, i;
	gotoxy(69, 12);
	printf("INFORMATION TO LOGIN INTO ACCOUNT");
	createRectangularBox(45, 15, 125, 30);
	//Implementation of checking username
	gotoxy(46, 18);
	printf("\t\t\tEnter your user name: ");
	scanf("%s", userName);
	result1 = checkName(userName);
	
	if (result1) {
		strcpy(Name, userName);
		//Implementation of checking password
		gotoxy(46, 21);
		printf("\t\t\tEnter your password: ");
		i = 0;
		while (1) {
			char ch = getch();
			if (ch == 13)
				break;
			putchar('*');
			password[i] = ch;
			i += 1;
		}
		password[i] = '\0';
		result2 = checkPassword(userName, password);
		if (result2 == 1) {
			gotoxy(69, 27);
			printf("LOGGED IN SUCCESSFULLY");
			strcpy(watchword, password);
			Sleep(3000);
			return 1;
		}
		else {
			countWrongPassword += 1;
			if (countWrongPassword == 4) {
				gotoxy(67, 27);
				printf("Passwrod didn't match");
				gotoxy(58, 28);
				printf("You have entered wrong password more than 3 times");
				Sleep(3000);
				return 0;
			}
			gotoxy(67, 27);
			printf("Passwrod didn't match");
			Sleep(3000);
			userInformation(countWrongUserName, countWrongPassword);
		}
	}
	else {
		countWrongUserName += 1;
		if (countWrongUserName == 4) {
			gotoxy(65, 27);
			printf("User name doesn't EXIST");
			gotoxy(58, 28);
			printf("You have entered wrong user name more than 3 times");
			Sleep(3000);
			return 0;
		}
		gotoxy(67, 27);
		printf("User name doesn't EXIST");
		Sleep(3000);
		userInformation(countWrongUserName, countWrongPassword);
	}
}

int checkName(char *userName) {
	//Variable to return to the calling function
	int finalValue = 0;
	
	//Creation of a file pointer
	FILE *fp;
	fp = fopen("Account_Details.csv", "r");
	
	//Checking for file opening condition
	if (fp == NULL) {
		finalValue = 0;
	}
	
	char totalLine[100];
	while (fgets(totalLine, sizeof(totalLine), fp)) {
		char *token;
		token = strtok(totalLine, ",");
		int result = strcmp(userName, token);
		if (result == 0) {
			finalValue = 1;
			break;
		}
		else {
			finalValue = 0;
		}
	}
	
	fclose(fp);
	return finalValue;
}

int checkPassword(char *userName, char *password) {
	//Variable to return to the calling function
	int finalValue = 0, i;
	
	//Creation of a file pointer
	FILE *fp;
	fp = fopen("Account_Details.csv", "r");
	
	//Checking for file opening condition
	if (fp == NULL) {
		printf("Unable to open the file\n");
		finalValue = 0;
	}
	
	char totalLine[100];
	while (fgets(totalLine, sizeof(totalLine), fp)) {
		char *token, copy[9];
		token = strtok(totalLine, ",");
		int check = strcmp(userName, token);
		if (check == 0) {
			token = strtok(NULL, ",");
			i = 0;
			do {
				token++;
				copy[i] = *token;
				i += 1;
			}while (*token != '\0');
			int result = strcmp(password, copy);
			if (result == 0) {
				finalValue = 1;
				break;
			}
			else {
 				finalValue = 0;
			}
		}
		else 
			finalValue = 0;
	}
	
	fclose(fp);
	return finalValue;
}