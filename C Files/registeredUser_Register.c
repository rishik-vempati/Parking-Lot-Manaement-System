#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>

#include "Test.h"
#include "registeredUser_Register.h"

//Global Variables

//Creating an account for Advanced Booking customer
//Creating a structure variable of an account
struct Account* newAccount;
char userName_password[2][30];
int r[4];

//Linking C programs
void registeredUser_CarParking(char** userName_password);

void registeredUser_Register(void) {
	char** userName_password;
	int finalValue = userDetails();
	if (finalValue == 1) {
		userName_password = (char**)malloc(2 * sizeof(char *));
		for (int i = 0; i < 2; i++) {
			userName_password[i] = (char*)malloc(30 * sizeof(char));
		}
		strcpy(userName_password[0], newAccount->userName);
		strcpy(userName_password[1], newAccount->password);
		registeredUser_CarParking(userName_password);
	}
	else {
		gotoxy(43, 32);
		printf("\tUser Name with the entered first name and last name already exists!!");
		gotoxy(43, 34);
		printf("\tPress any key to continue..");
		getch();
	}
}

//Functions Implementation
int userDetails() {
	system("cls");
	newAccount = (struct Account*)malloc(sizeof(struct Account));
	gotoxy(69, 9);
	printf("INFORMATION FOR CREATING AN ACCOUNT");
	gotoxy(49, 13);
	printf("USER INFORMATION		PASSWORD SETUP		VERIFICATION PROCESS");
	createRectangularBox(45, 15, 125, 30);
	
	gotoxy(46, 18);
	printf("\t\t\tEnter your first name: ");
	scanf("%s", newAccount->firstName);
	gotoxy(46, 21);
	printf("\t\t\tEnter your last name: ");
	scanf("%s", newAccount->lastName);
	
	strcat(newAccount->firstName, "-");
	strcat(newAccount->firstName, newAccount->lastName);
	strcpy(newAccount->userName, newAccount->firstName);
	int value = checkUserName(newAccount->userName);
	if (value == 0) {
		return 0;
	}
	
	//Calling createPassword() function to create a new password
	createPassword();
	return 1;
}

void createPassword() {
	system("cls");
	int countLower, countUpper, countDigit, counter, c;
	countLower = countUpper = countDigit = counter = c = 0;

	char temp1[9];
	char temp2[9];
	
	gotoxy(55, 6);
	printf("THE PASSWORD SHOULD BE A 8 CHARACTER PASSWORD\n");
	gotoxy(55, 8);
	printf("THE PASSWORD SHOULD CONTAIN ATLEAST 1 UPPER CASE LETTER\n");
	gotoxy(55, 10);
	printf("THE PASSWORD SHOULD CONTAIN ATLEAST 1 LOWER CASE LETTER\n");
	gotoxy(55, 12);
	printf("THE PASSWORD SHOULD CONTAIN ATLEAST 1 DIGIT\n");
	gotoxy(49, 15);
	printf("USER INFORMATION-------->PASSWORD SETUP		VERIFICATION PROCESS");
	createRectangularBox(45, 17, 125, 34);
	gotoxy(46, 20);
	printf("\t\t\tEnter your password: ");
	
	while (counter < 8) {
		temp1[counter] = getch();
		putchar('*');
		counter += 1;
	}
	temp1[counter] = '\0';
		
	for (int i = 0; temp1[i] != '\0'; i++) {
		if ((temp1[i] >= 65) && (temp1[i] <= 90)) {
			countUpper += 1;
		}
		else if ((temp1[i] >= 97) && (temp1[i] <= 122)) {
			countLower += 1;
		}
		else if ((temp1[i] >= 48) && (temp1[i] <= 57)) {
			countDigit += 1;
		}
	}
	
	//Checking for the conditions of the password
	if ((countUpper >= 1) && (countLower >= 1) && (countDigit >= 1)) {
		gotoxy(70, 22);
		printf("STRONG PASSWORD!!");
		gotoxy(46, 24);
		printf("\t\t\tEnter your password again: ");
		
		while (c < 8) {
			temp2[c] = getch();
			putchar('*');
			c += 1;
		}
		temp2[c] = '\0';
		
		gotoxy(68, 26);
		printf("Rechecking your password....");
		if (strcmp(temp1, temp2) == 0) {
			gotoxy(69, 27);
			printf("Password MATCHED!!");
			strcpy(newAccount->password, temp1);
			Sleep(3000);
			verificationProcess();
		}
		else {
			gotoxy(58, 27);
			printf("OOPS!! On rechecking.. your have entered another password");
			Sleep(3000);
			createPassword();
		}
	}
	else {
		gotoxy(60, 24);
		printf("The conditions in the password didn't met");
		Sleep(3000);
		createPassword();
	}
}

void verificationProcess() {
	system("cls");
	gotoxy(70, 10);
	printf("VERIFYING YOUR ACCOUNT");
	gotoxy(49, 12);
	printf("USER INFORMATION-------->PASSWORD SETUP-------->VERIFICATION PROCESS");
	createRectangularBox(45, 14, 125, 30);
	char fruits[10][20] = {"C Progamming", "C++", "JAVA", "Java Script", "Python", "HTML", "CSS", "Kotlin", "Ruby", "Scala"};
	char vegetables[10][20] = {"Telugu", "Hindi", "English", "History", "Physics", "Chemistry", "Sanskrit", "French", "Geography", "Biology"};
	char ch;
	int i = 0, j = 0;
	int *r;
	r = createArray();
		
	i = 0;
	gotoxy(70, 16);
	printf("Pick odd one out");
	gotoxy(70, 18);
	printf("A) %s\n", fruits[r[i++]]);
	gotoxy(70, 19);
	printf("B) %s\n", fruits[r[i++]]);
	gotoxy(70, 20);
	printf("C) %s\n", vegetables[r[i++]]);
	gotoxy(70, 21);
	printf("D) %s\n", fruits[r[i++]]);
	gotoxy(70, 23);
	printf("Choose your option: ");
	scanf(" %c", &ch);
	ch = tolower(ch);
	switch(ch) {
		case 'a':
			gotoxy(70, 27);
			printf("Wrong answer entered!!");
			break;
		case 'b':
			gotoxy(70, 27);
			printf("Wrong answer entered!!");
			break;
		case 'c':
			gotoxy(67, 25);
			printf("Account Verification Successful\n");
			gotoxy(55, 27);
			printf("Account has been created with user name: %s\n\n", newAccount->userName);
			break;
		case 'd':
			gotoxy(70, 27);
			printf("Wrong answer entered!!");
			break;
		default:
			gotoxy(70, 27);
			printf("Invalid option entered");
			break;
	}
	
	if (ch == 'c') {
		Sleep(3000);
		//Calling storingDetails() function to store account details in a file.
		storingDetails();
	}
	else {
		Sleep(3000);
		//Calling verificationProcess() function again to verify the account
		verificationProcess();
	}
}

void storingDetails() {
	//Creation of a file pointer
	FILE *fp;
	fp = fopen("Account_Details.csv", "a");
	
	//Checking for file opening condition
	if (fp == NULL) {
		printf("Unable to open the file\n");
		return;
	}
	
	fprintf(fp, "%s, %s,\n", newAccount->userName, newAccount->password);
	fclose(fp);
}

int* createArray() {
	r[0] = r[1] = r[2] = r[3] = -1;
	int i, j, lower = 0, upper = 9;
	for (i = 0; i < 4; i++) {
		r[i] = (rand() % (upper - lower + 1)) + lower;
	}
		
	for (i = 0; i < 4; i++) {
		if (i != 3) {
			for (j = (i + 1); j < 4; j++) {
				if (r[i] == r[j]) {
					do {
						r[j] = (rand() % (upper - lower - 1)) + lower;
					}while (r[j] == r[i]);
				}
			}
		}
	}
	
	return r;
}

int checkUserName(char *userName) {
	//Variable to return to the calling function
	int finalValue = 1;
	
	//Creation of a file pointer
	FILE *fp;
	fp = fopen("Account_Details.csv", "r");
	
	//Checking for file opening condition
	if (fp == NULL) {
		finalValue = 1;
	}
	
	char totalLine[100];
	while (fgets(totalLine, sizeof(totalLine), fp)) {
		char *token;
		token = strtok(totalLine, ",");
		int result = strcmp(userName, token);
		if (result == 0) {
			finalValue = 0;
			break;
		}
	}
	
	fclose(fp);
	return finalValue;
}