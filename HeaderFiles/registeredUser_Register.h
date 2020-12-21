#ifndef REGISTEREDUSER_REGISTER_H
#define REGISTEREDUSER_REGISTER_H

//Creation Of structure Account
struct Account {
	char firstName[50];
	char lastName[50];
	char userName[50];
	char password[8];
};

//Functions Prototype
int userDetails();
int checkUserName(char *userName);
void createPassword();
void verificationProcess();
void storingDetails();
int* createArray();

#endif