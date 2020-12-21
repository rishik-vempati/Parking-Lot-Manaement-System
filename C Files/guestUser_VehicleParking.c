#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>

#include "Test.h"
#include "guestUser_VehicleParking.h"
#include "registeredUser_CarParking.h"

//Global Variables
char** userName_password;
int checkGuestParkingSlots[2][10];
char parkingID[10];
char resultant[11];

//Linking C programs
void parkingLotManager_addGuestRecord(struct GuestSlot* newSlot, char** userDetails);
void parkingLotManager_deleteGuestRecord(char* vehicleNumber);

void guestUser_VehicleParking() {
	int option, finish;
	system("cls");
	getAllSlots();
	finish = 1;
	userName_password = (char**)malloc(2 * sizeof(char*));
	for (int i = 0; i < 2; i++) {
		userName_password[i] = (char*)malloc(30 * sizeof(char));
		for (int j = 0; j < 30; j++) {
			userName_password[i][j] = '\0';
		}
	}
	while (finish) {
		Sleep(3000);
		system("cls");
		gotoxy(50, 12);
		printf("\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb  VEHICLE PARKING  \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb");
		gotoxy(60, 15);
		printf("\t\tPress '1' for Slot Booking");
		gotoxy(60, 16);
		printf("\t\tPress '2' for Vehicle Departure");
		gotoxy(60, 18);
		printf("\t\tPress '3' to EXIT");
		gotoxy(60, 20);
		printf("\t\tPress your action: ");
		scanf("%d", &option);
		if (option == 1) {
			getchar();
			slotBooking(userName_password);
		}
		
		else if (option == 2) {
			getchar();
			vehicleDeparture(userName_password);
		}
		
		else if (option == 3) 
			finish = 0;
	}
	Sleep(3000);
}

//Functions Implementation
void getAllSlots() {
	FILE *fp1, *fp2;
	fp1 = fopen("GuestFourWheeler_Repository.csv", "r");
	fp2 = fopen("GuestTwoWheeler_Repository.csv", "r");
	
	if ((fp1 == NULL) && (fp2 == NULL)){
		return;
	}
	else if ((fp1 != NULL) && (fp2 == NULL)) {
		char totalLine1[100];
		while (fgets(totalLine1, sizeof(totalLine1), fp1)) {
			char *token;
			int floorNumber, slotNumber;
			token = strtok(totalLine1, ",");
			token = strtok(NULL, ",");
			token = strtok(NULL, ",");
			token = strtok(NULL, ",");
			token = strtok(NULL, ",");
			token = strtok(NULL, ",");
			floorNumber = atoi(token);
			token = strtok(NULL, ",");
			slotNumber = atoi(token);
			checkGuestParkingSlots[floorNumber - 5][slotNumber - 41] = 1;
		}
		
		fclose(fp1);
		return;
	}
	else if ((fp1 == NULL) && (fp2 != NULL)) {
		char totalLine2[100];
		while (fgets(totalLine2, sizeof(totalLine2), fp2)) {
			char *token;
			int floorNumber, slotNumber;
			token = strtok(totalLine2, ",");
			token = strtok(NULL, ",");
			token = strtok(NULL, ",");
			token = strtok(NULL, ",");
			token = strtok(NULL, ",");
			token = strtok(NULL, ",");
			floorNumber = atoi(token);
			token = strtok(NULL, ",");
			slotNumber = atoi(token);
			checkGuestParkingSlots[floorNumber - 6][slotNumber - 51] = 1;
		}
		
		fclose(fp2);
		return;
	}
	else if ((fp1 != NULL) && (fp2 != NULL)) {
		char totalLine1[100];
		while (fgets(totalLine1, sizeof(totalLine1), fp1)) {
			char *token;
			int floorNumber, slotNumber;
			token = strtok(totalLine1, ",");
			token = strtok(NULL, ",");
			token = strtok(NULL, ",");
			token = strtok(NULL, ",");
			token = strtok(NULL, ",");
			token = strtok(NULL, ",");
			floorNumber = atoi(token);
			token = strtok(NULL, ",");
			slotNumber = atoi(token);
			checkGuestParkingSlots[floorNumber - 5][slotNumber - 41] = 1;
		}
		
		fclose(fp1);
		
		char totalLine2[100];
		while (fgets(totalLine2, sizeof(totalLine2), fp2)) {
			char *token;
			int floorNumber, slotNumber;
			token = strtok(totalLine2, ",");
			token = strtok(NULL, ",");
			token = strtok(NULL, ",");
			token = strtok(NULL, ",");
			token = strtok(NULL, ",");
			token = strtok(NULL, ",");
			floorNumber = atoi(token);
			token = strtok(NULL, ",");
			slotNumber = atoi(token);
			checkGuestParkingSlots[floorNumber - 6][slotNumber - 51] = 1;
		}
		
		fclose(fp2);
		
		return;
	}
}

void slotBooking(char** userDetails) {
	system("cls");
	printf("\n\nINFORMATION TO BOOK A SLOT\n\n");
	//Creating Slot For Guest User
	//Creating a structure variable for a customer
	struct GuestSlot* newSlot;
	
	int arr[2], type, check, days;
	int vehicleLength = 10;
	int vehicleCount = 0;
	char firstName[50], lastName[50];
	char vehicleNumber[50];
	
	printf("Enter your first name: ");
	gets(firstName);
	printf("Enter your last name: ");
	gets(lastName);
	
	int flag = 0;
	do {
		printf("\nCHOOSE YOUR VEHICLE TYPE\n");
		printf("ENTER '2' FOR A TWO WHEELER\n");
		printf("ENTER '4' FOR A FOUR WHEELER\n");
		printf("Enter your choice: ");
		scanf("%d", &type);
		switch(type) {
			case 4:
				getchar();
				printf("Enter your vehicle number: ");
				gets(vehicleNumber);
				if (vehicleLength != strlen(vehicleNumber)) {
					printf("\n\nVehicle number entered didn't have 10 characters\n\n");
					printf("Press any key to continue..");
					getch();
					return;
				}
				else {
					for (int l = 0; l < strlen(vehicleNumber); l++) {
						if (((vehicleNumber[l] >= 65) && (vehicleNumber[l] <= 90)) || ((vehicleNumber[l] >= 48) && (vehicleNumber[l] <= 57))) {
							//No Implementation
						}
						else {
							printf("\n\nVehicle number should contain only upper case letters and numbers\n\n");
							printf("Press any key to continu..");
							getch();
							return;
						}
					}
					
					//Conditions for checking the vehicle number
					if (((vehicleNumber[0] >= 65) && (vehicleNumber[0] <= 90)) && ((vehicleNumber[1] >= 65) && (vehicleNumber[1] <= 90))) {
						vehicleCount += 2;
					}
					
					if (((vehicleNumber[2] >= 48) && (vehicleNumber[2] <= 57)) && ((vehicleNumber[3] >= 48) && (vehicleNumber[3] <= 57))) {
						vehicleCount += 2;
					}
					
					if (((vehicleNumber[4] >= 65) && (vehicleNumber[4] <= 90)) && ((vehicleNumber[5] >= 65) && (vehicleNumber[5] <= 90))) {
						vehicleCount += 2;
					}
					
					if (((vehicleNumber[6] >= 48) && (vehicleNumber[6] <= 57)) && ((vehicleNumber[7] >= 48) && (vehicleNumber[7] <= 57))) {
						vehicleCount += 2;
					}
					
					if (((vehicleNumber[8] >= 48) && (vehicleNumber[8] <= 57)) && ((vehicleNumber[9] >= 48) && (vehicleNumber[9] <= 57))) {
						vehicleCount += 2;
					}
				}
				
				if (vehicleCount == 10) {
					check = checkVehicleNumber(vehicleNumber);
					if (check == 0) {
						printf("The vehicle number is currently parked in the Parking Lot\n");
						printf("You can't book a slot with that vehicle number\n");
						printf("Press any key to continue..");
						getch();
						return;
					}
				}
				
				checkEmptySlot(type, arr);
				printf("Enter the number of days you want to park the vehicle: ");
				scanf("%d", &days);
				if (days <= 0) {
					printf("\n\nMinimum day(s) of parking are 1\n\n");
					printf("Press any key to continue..");
					getch();
					return;
				}
				else if (days > 30) {
					printf("\n\nMaximum days(s) of parking are 30\n\n");
					printf("Press any key to continue..");
					getch();
					return;
				}
				
				if ((arr[0] != -1) && (arr[1] != -1)) {		
					printf("\n\nFOUR WHEELER VEHICLES - 10 SLOTS\n\n");
					printf("------------------------------------------------------------------\n");
					printf("Floor    |\t\t\t         Slot Numbers\n");
					printf("------------------------------------------------------------------\n");
					printf("5th Floor|\t\t 41  42  43  44  45  46  47  48  49  50\n");
					printf("------------------------------------------------------------------\n");
					char* idNumber = getParkingID(arr[0], arr[1]);
					newSlot = addGuestVehicleToParkingLot(type, days, vehicleNumber, arr[0], arr[1], firstName, lastName);
					printf("Parking ID: %s\n", idNumber);
					printf("Your vehicle has been parked at %d floor, %d slot number\n", arr[0] + 5, arr[1] + 41);
					//As we have the details of the customer, now this information to his file with name of his vehicleNumber
					strcpy(userDetails[0], newSlot->firstName);
					strcpy(userDetails[1], newSlot->lastName);
					storeGuestDetails(newSlot, userDetails, idNumber);
					parkingLotManager_addGuestRecord(newSlot, userDetails);
				}
				else {
					printf("Sorry!! There is no parking slot to park a four wheeler vehicle\n");
				}
				printf("\n\nPress any key to continue..");
				getch();
				flag = 1;
				break;
			
			case 2:
				getchar();
				printf("Enter your vehicle number: ");
				gets(vehicleNumber);
				if (vehicleLength != strlen(vehicleNumber)) {
					printf("\n\nVehicle number entered didn't have 10 characters\n\n");
					printf("Press any key to continue..");
					getch();
					return;
				}
				else {
					for (int l = 0; l < strlen(vehicleNumber); l++) {
						if (((vehicleNumber[l] >= 65) && (vehicleNumber[l] <= 90)) || ((vehicleNumber[l] >= 48) && (vehicleNumber[l] <= 57))) {
							//No Implementation
						}
						else {
							printf("\n\nVehicle number should contain only upper case letters and numbers\n\n");
							printf("Press any key to continue..");
							getch();
							return;
						}
					}
					
					//Conditions for checking the vehicle number
					if (((vehicleNumber[0] >= 65) && (vehicleNumber[0] <= 90)) && ((vehicleNumber[1] >= 65) && (vehicleNumber[1] <= 90))) {
						vehicleCount += 2;
					}
					
					if (((vehicleNumber[2] >= 48) && (vehicleNumber[2] <= 57)) && ((vehicleNumber[3] >= 48) && (vehicleNumber[3] <= 57))) {
						vehicleCount += 2;
					}
					
					if (((vehicleNumber[4] >= 65) && (vehicleNumber[4] <= 90)) && ((vehicleNumber[5] >= 65) && (vehicleNumber[5] <= 90))) {
						vehicleCount += 2;
					}
					
					if (((vehicleNumber[6] >= 48) && (vehicleNumber[6] <= 57)) && ((vehicleNumber[7] >= 48) && (vehicleNumber[7] <= 57))) {
						vehicleCount += 2;
					}
					
					if (((vehicleNumber[8] >= 48) && (vehicleNumber[8] <= 57)) && ((vehicleNumber[9] >= 48) && (vehicleNumber[9] <= 57))) {
						vehicleCount += 2;
					}
				}
				
				if (vehicleCount == 10) {
					check = checkVehicleNumber(vehicleNumber);
					if (check == 0) {
						printf("The vehicle number is currently parked in the Parking Lot\n");
						printf("You can't book a slot with that vehicle number\n");
						printf("Press any key to continue..");
						getch();
						return;
					}
				}
				
				checkEmptySlot(type, arr);
				printf("Enter the number of days you want to park the vehicle: ");
				scanf("%d", &days);
				if (days <= 0) {
					printf("\n\nMinimum day(s) of parking are 1\n\n");
					printf("Press any key to continue..");
					getch();
					return;
				}
				else if (days > 30) {
					printf("\n\nMaximum days(s) of parking are 30\n\n");
					printf("Press any key to continue..");
					getch();
					return;
				}
				
				if ((arr[0] != -1) && (arr[1] != -1)) {
					printf("\n\nTWO WHEELER VEHICLES - 10 SLOTS\n\n");
					printf("----------------------------------------------------------------------\n");
					printf("Floor    |\t\t\t         Slot Numbers\n");
					printf("----------------------------------------------------------------------\n");
					printf("6th Floor|\t\t51   52   53   54   55   56   57   58   59  60\n");
					printf("----------------------------------------------------------------------\n");
					char* idNumber = getParkingID(arr[0], arr[1]);
					newSlot = addGuestVehicleToParkingLot(type, days, vehicleNumber, arr[0], arr[1], firstName, lastName);
					printf("Parking ID: %s\n", idNumber);
					printf("Your vehicle has been parked at %d floor, %d slot number\n", arr[0] + 5, arr[1] + 51);
					//As we have the details of the customer, now this information to his file with name of his vehicleNumber
				
					strcpy(userDetails[0], newSlot->firstName);
					strcpy(userDetails[1], newSlot->lastName);
					storeGuestDetails(newSlot, userDetails, idNumber);
					parkingLotManager_addGuestRecord(newSlot, userDetails);
				}
				else {
					printf("Sorry!! There is no parking slot to park a two wheeler vehicle\n");
				}
				printf("\n\nPress any key to continue..");
				getch();
				flag = 1;
				break;
			
			default:
				printf("WRONG OPTION ENTERED\n");
				printf("PLEASE CHOOSE FROM THE OPTIONS GIVEN\n");
				break;
		}
	}while (flag != 1);
}

void vehicleDeparture(char** userDetails) {
	system("cls");
	printf("\n\nINFORMATION TO DEPARTURE A VEHICLE\n\n");
	char firstName[50], lastName[50];
	char idNumber[20];
	int arr[2];
	
	printf("Enter your first name: ");
	gets(firstName);
	printf("Enter your last name: ");
	gets(lastName);
	printf("Enter your Parking ID: ");
	gets(idNumber);
	strcpy(userDetails[0], firstName);
	strcpy(userDetails[1], lastName);
	
	int finalValue = checkID(userDetails, idNumber);
	if ((finalValue == 1) || (finalValue == -1)){
		printf("\n\nUser Details are invalid\n");
		printf("Press any key to continue..");
		getch();
		return;
	}
	
	char* vehicleNumber = getVNum(idNumber);
	char fileName[20];
	char ch;
	strcpy(fileName, vehicleNumber);
	strcat(fileName, ".txt");
	
	int d, mo, y, h, mi, s, ad;
	FILE *fp;
	fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("\nSorry, there isn't a vehicle with that parking ID\n");
		return;
	}
	int count = 0;
	char totalLine[100];
	
	if (fp != NULL) {
		while (fgets(totalLine, sizeof(totalLine), fp)) {
			count += 1;
			if (count == 3) {
				fseek(fp, 34, SEEK_CUR);
				int i, j = 0;
				char c[3], ch;
				while ((ch = fgetc(fp)) != '.') {
					c[j] = ch;
					j += 1;
				}
				ad = atoi(c);
			}
			
			else if (count == 4) {
				fseek(fp, 22, SEEK_CUR);
				int j = 0;
				char c[10], ch;
				while ((ch = fgetc(fp)) != '.') {
					c[j] = ch;
					j += 1;
				}
				c[j] = '\0';
				char *token;
				token = strtok(c, "/");
				d = atoi(token);
				token = strtok(NULL, "/");
				mo = atoi(token);
				token = strtok(NULL, "/");
				y = atoi(token);
			}
			
			else if (count == 5) {
				fseek(fp, 17, SEEK_CUR);
				int j = 0;
				char c[10], ch;
				while ((ch = fgetc(fp)) != ' ') {
					c[j] = ch;
					j += 1;
				}
				c[j] = '\0';
				char *token;
				token = strtok(c, ":");
				h = atoi(token);
				token = strtok(NULL, ":");
				mi = atoi(token);
				token = strtok(NULL, ":");
				s = atoi(token);
			}
		}
		fclose(fp);
	}
	
	int day, month, year;
	int hours, minutes, seconds;
	time_t currentTime;
	
	time(&currentTime); //Obtains Current Time
	
	struct tm *localTime = localtime(&currentTime);
	day = localTime->tm_mday;
	month = localTime->tm_mon + 1;
	year = localTime->tm_year + 1900;
	
	struct Date dt1 = addDays(d, mo, y, ad);
	struct Date dt2 = {day, month, year};
	int remainingDays;
	remainingDays = getDifference(dt2, dt1);
	remainingDays -= 1;
	
	struct Time startTime, stopTime, diff;
	if (remainingDays == 0) {
		printf("You have to departure your vehicle today\n");
		hours = localTime->tm_hour;
		minutes = localTime->tm_min;
		seconds = localTime->tm_sec;
		
		startTime.hours = hours;
		startTime.minutes = minutes;
		startTime.seconds = seconds;	
		stopTime.hours = h;
		stopTime.minutes = mi;
		stopTime.seconds = s;
		
		differenceBetweenTimePeriod(stopTime, startTime, &diff);
		if (diff.hours < 0) {
			printf("There are %d more hours to departure\n\n", (-1 * diff.hours));
		}
		else {
			printf("The departure time has been crossed before %d hours\n\n", (diff.hours));
		}
		
		int re = 1;
		do {
			printf("Do you want to departure it now(Y/N): ");
			scanf("%c", &ch);
			ch = tolower(ch);
			switch(ch) {
				case 'y':
					arr[0] = arr[1] = -1;
					getVehiclePos(idNumber, arr);
					if ((arr[0] != -1) && (arr[1] != -1)) {
						int row, col;
						row = arr[0];
						col = arr[1];
						DeleteVehicle(row, col);
						DeleteDetails(idNumber);
					}
					int type;
					if (arr[0] == 0) {
						type = 4;
					}
					else if (arr[0] == 1) {
						type = 2;
					}
					Sleep(3000);
					parkingLotManager_deleteGuestRecord(vehicleNumber);
					int s = ad;
					parkingCost(s, type);
					Sleep(3000);
					re = 0;
					break;
				case 'n':
					printf("\n\nYou vehicle is still in parking\n");
					Sleep(3000);
					re = 0;
					return;
				default:
					printf("\nYou have entered invalid character\n");
					printf("Please enter a valid character\n");
					break;
			}
		}while (re != 0);
	}
	
	else if (remainingDays > 0) {
		int re = 1;
		printf("\nThere are %d days to departure..\n\n", remainingDays);
		do {
			printf("Do you want to departure it now(Y/N): ");
			scanf("%c", &ch);
			ch = tolower(ch);
			switch(ch) {
				case 'y':
					arr[0] = arr[1] = -1;
					getVehiclePos(idNumber, arr);
					if ((arr[0] != -1) && (arr[1] != -1)) {
						int row, col;
						row = arr[0];
						col = arr[1];
						DeleteVehicle(row, col);
						DeleteDetails(idNumber);
					}
					Sleep(3000);
					system("cls");
					int type;
					if (arr[0] == 0) {
						type = 4;
					}
					else if (arr[0] == 1) {
						type = 2;
					}
					int s = (ad - remainingDays);
					parkingCost(s, type);
					parkingLotManager_deleteGuestRecord(vehicleNumber);
					Sleep(3000);
					re = 0;
					break;
				case 'n':
					printf("\n\nYou vehicle is still in parking\n");
					Sleep(3000);
					re = 0;
					return;
				default:
					printf("\nYou have entered invalid character\n");
					printf("Please enter a valid character\n");
					Sleep(3000);
					break;
			}
		}while (re != 0);
	}
	
	else if (remainingDays < 0) {
		int store = (-1 * remainingDays);
		printf("\nYou have parked %d days more than you said\n", store);
		arr[0] = arr[1] = -1;
		getVehiclePos(idNumber, arr);
		if ((arr[0] != -1) && (arr[1] != -1)) {
			int row, col;
			row = arr[0];
			col = arr[1];
			DeleteVehicle(row, col);
			DeleteDetails(idNumber);
		}
		Sleep(3000);
		int type;
		if (arr[0] == 0) {
			type = 4;
		}
		else if (arr[0] == 1) {
			type = 2;
		}
		int s = store + ad;
		parkingCost(s, type);
		parkingLotManager_deleteGuestRecord(vehicleNumber);
		printf("Press any key to continue..");
		getch();
	}
}

void storeGuestDetails(struct GuestSlot* newSlot, char** userDetails, char* idNumber) {
	FILE *fp;
	if (newSlot->vehicleType == 2) {
		fp = fopen("GuestTwoWheeler_Repository.csv", "a");
	}
	else if (newSlot->vehicleType == 4) {
		fp = fopen("GuestFourWheeler_Repository.csv", "a");
	}
	
	if (fp == NULL) {
		return;
	}
	
	fprintf(fp, "%s, %s, %s, %s, %d, %d, %d, %d\n", userDetails[0], userDetails[1], idNumber, newSlot->vehicleNumber, newSlot->vehicleType, newSlot->floor, newSlot->slotNumber, newSlot->numberOfDays);
	fclose(fp);
}

struct GuestSlot* addGuestVehicleToParkingLot(int type, int days, char* vehicleNumber, int floor, int slotNumber, char* firstName, char* lastName) {
	struct GuestSlot* newSlot = (struct GuestSlot*)malloc(sizeof(struct GuestSlot));
	newSlot->vehicleType = type;
	if (newSlot->vehicleType == 4) {
		newSlot->floor = floor + 5;
		newSlot->slotNumber = slotNumber + 41;
	}
	else if (newSlot->vehicleType == 2) {
		newSlot->floor = floor + 5;
		newSlot->slotNumber = slotNumber + 51;
	}
	newSlot->numberOfDays = days;
	strcpy(newSlot->vehicleNumber, vehicleNumber);
	strcpy(newSlot->firstName, firstName);
	strcpy(newSlot->lastName, lastName);
	
	checkGuestParkingSlots[floor][slotNumber] = 1;
	return newSlot;
}
	
	
void checkEmptySlot(int type, int *arr) {
	int floor, slotNumber;
	int fromFloor = 0, toFloor = 1;
	if (type == 2) {
		fromFloor += 1;
		toFloor += 1;
	}
	
	for (floor = fromFloor; floor < toFloor; floor++) {
		for (slotNumber = 0; slotNumber < 10; slotNumber++) {
			if (checkGuestParkingSlots[floor][slotNumber] == 0) {
				arr[0] = floor;
				arr[1] = slotNumber;
				return;
			}
		}
	}
	
	if ((floor == 1) || (floor == 2)) {
		arr[0] = -1;
		arr[1] = -1;
	}
}

char* getParkingID(int row, int col) {
	for (int i = 0; i < 10; i++) {
		parkingID[i] = '\0';
	}
	strcat(parkingID, "PC-");
	if (row == 0) {
		strcat(parkingID, "5F-");
		if ((col >= 0) && (col < 9)) {
			strcat(parkingID, "0");
			char str[3];
			sprintf(str, "%d", (col + 41));
			strcat(parkingID, str);
		}
		else {
			strcat(parkingID, "050");
		}
	}
	else if (row == 1) {
		strcat(parkingID, "6F-");
		if ((col >= 0) && (col < 9)) {
			strcat(parkingID, "0");
			char str[3];
			sprintf(str, "%d", (col + 51));
			strcat(parkingID, str);
		}
		else {
			strcat(parkingID, "060");
		}
	}
	
	return parkingID;
}

int checkID(char** userDetails, char* parkingID) {
	FILE *fp1, *fp2;
	
	int finalValue = 1;
	fp1 = fopen("GuestFourWheeler_Repository.csv", "r");
	fp2 = fopen("GuestTwoWheeler_Repository.csv", "r");
	if ((fp1 == NULL) && (fp2 == NULL)) {
		return -1;
	}
	
	char totalLine[100];
	if (fp1 != NULL) {
		while (fgets(totalLine, sizeof(totalLine), fp1)) {
			char *token, copy[30];
			char lname[30];
			int i = 0;
			token = strtok(totalLine, ",");
			if (strcmp(token, userDetails[0]) == 0) {
				token = strtok(NULL, ",");
				do {
					token++;
					lname[i] = *token;
					i += 1;
				}while (*token != '\0');
				i = 0;
				if (strcmp(lname, userDetails[1]) == 0) {
					token = strtok(NULL, ",");
					do {
						token++;
						copy[i] = *token;
						i += 1;
					}while (*token != '\0');
					int result = strcmp(parkingID, copy);
					if (result == 0) {
						finalValue = 0;
						break;
					}
				}
			}
		}
		fclose(fp1);
		if (finalValue == 0) {
			if (fp2 != NULL) 
				fclose(fp2);
			return finalValue;
		}
	}
	
	if (fp2 != NULL) {
		while (fgets(totalLine, sizeof(totalLine), fp2)) {
			char *token, copy[30];
			char lname[30];
			int i = 0;
			token = strtok(totalLine, ",");
			if (strcmp(token, userDetails[0]) == 0) {
				token = strtok(NULL, ",");
				do {
					token++;
					lname[i] = *token;
					i += 1;
				}while (*token != '\0');
				i = 0;
				if (strcmp(lname, userDetails[1]) == 0) {
					token = strtok(NULL, ",");
					do {
						token++;
						copy[i] = *token;
						i += 1;
					}while (*token != '\0');
					int result = strcmp(parkingID, copy);
					if (result == 0) {
						finalValue = 0;
						break;
					}
				}
			}
		}
		fclose(fp2);
		if (finalValue == 0) {
			return finalValue;
		}
	}
	
	return finalValue;
}

char* getVNum(char* parkingID) {
	for (int j = 0; j < 11; j++) {
		resultant[j] = '\0';
	}
	FILE *fp1, *fp2;
	
	fp1 = fopen("GuestFourWheeler_Repository.csv", "r");
	fp2 = fopen("GuestTwoWheeler_Repository.csv", "r");
	if ((fp1 == NULL) && (fp2 == NULL))
		return NULL;
	
	char totalLine[150];
	if (fp1 != NULL) {
		while (fgets(totalLine, sizeof(totalLine), fp1)) {
			char* token;
			char copy[10];
			char vnum[11];
			token = strtok(totalLine, ",");
			token = strtok(NULL, ",");
			token = strtok(NULL, ",");
			int i = 0;
			do {
				token++;
				copy[i] = *token;
				i += 1;
			}while (*token != '\0');
			int result = strcmp(parkingID, copy);
			if (result == 0) {
				token = strtok(NULL, ",");
				i = 0;
				do {
					token++;
					vnum[i] = *token;
					i += 1;
				}while (*token != '\0');
				strcpy(resultant, vnum);
				break;
			}
		}
		fclose(fp1);
	}
	
	if (fp2 != NULL) {
		while (fgets(totalLine, sizeof(totalLine), fp2)) {
			char* token;
			char copy[10];
			char vnum[11];
			token = strtok(totalLine, ",");
			token = strtok(NULL, ",");
			token = strtok(NULL, ",");
			int i = 0;
			do {
				token++;
				copy[i] = *token;
				i += 1;
			}while (*token != '\0');
			int result = strcmp(parkingID, copy);
			if (result == 0) {
				token = strtok(NULL, ",");
				i = 0;
				do {
					token++;
					vnum[i] = *token;
					i += 1;
				}while (*token != '\0');
				strcpy(resultant, vnum);
				break;
			}
		}
		fclose(fp2);
	}
	
	return resultant;
}

void getVehiclePos(char* parkingID, int* arr) {
	FILE *fp1, *fp2;
	
	int finalValue1 = 1;
	fp1 = fopen("GuestFourWheeler_Repository.csv", "r");
	fp2 = fopen("GuestTwoWheeler_Repository.csv", "r");
	
	if ((fp1 == NULL) && (fp2 == NULL)) {
		return;
	}
	
	char totalLine[100];
	if (fp1 != NULL) {
		while (fgets(totalLine, sizeof(totalLine), fp1)) {
			char *token, copy[30];
			int i = 0;
			token = strtok(totalLine, ",");
			token = strtok(NULL, ",");
			token = strtok(NULL, ",");
			do {
				token++;
				copy[i] = *token;
				i += 1;
			}while (*token != '\0');
			int result = strcmp(parkingID, copy);
			if (result == 0) {
				int floor, slot;
				token = strtok(NULL, ",");
				token = strtok(NULL, ",");
				token = strtok(NULL, ",");
				floor = atoi(token);
				token = strtok(NULL, ",");
				slot = atoi(token);
				
				arr[0] = floor - 5;
				arr[1] = slot - 41;
			}
		}
		fclose(fp1);
	}
	
	if (fp2 != NULL) {
		while (fgets(totalLine, sizeof(totalLine), fp2)) {
			char *token, copy[30];
			int i = 0;
			token = strtok(totalLine, ",");
			token = strtok(NULL, ",");
			token = strtok(NULL, ",");
			do {
				token++;
				copy[i] = *token;
				i += 1;
			}while (*token != '\0');
			int result = strcmp(parkingID, copy);
			if (result == 0) {
				int floor, slot;
				token = strtok(NULL, ",");
				token = strtok(NULL, ",");
				token = strtok(NULL, ",");
				floor = atoi(token);
				token = strtok(NULL, ",");
				slot = atoi(token);
					
				arr[0] = floor - 6;
				arr[1] = slot - 51;
			}
		}
		fclose(fp2);
	}
}

void DeleteVehicle(int row, int col) {
	int i, j;
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 10; j++) {
			if (i == row) {
				if (j == col) {
					checkGuestParkingSlots[i][j] = 0;
					return;
				}
			}
		}
	}
}

void DeleteDetails(char* parkingID) {
	FILE *fp1, *fp2, *fp3;
	fp1 = fopen("GuestFourWheeler_Repository.csv", "r");
	fp2 = fopen("GuestTwoWheeler_Repository.csv", "r");
	
	if ((fp1 == NULL) && (fp2 == NULL)) {
		return;
	}
	
	int finalValue = 1;
	char totalLine[100];
	
	char oldName1[] = "GuestCopyFourWheeler.csv";
	char newName1[] = "GuestFourWheeler_Repository.csv";
	if (fp1 != NULL) {
		fp3 = fopen("GuestCopyFourWheeler.csv", "a");
		while (fgets(totalLine, sizeof(totalLine), fp1)) {
			char *token, copy[30];
			char user[50], pass[10];
			char vnum[20], pi[20];
			int vt, f, s, nd;
			
			int i = 0;
			token = strtok(totalLine, ",");
			strcpy(user, token);
			token = strtok(NULL, ",");
			strcpy(pass, token);
			
			token = strtok(NULL, ",");
			strcpy(pi, token);
			do {
				token++;
				copy[i] = *token;
				i += 1;
			}while (*token != '\0');
			
			Sleep(3000);
			int result = strcmp(parkingID, copy);
			if (result != 0) {
				token = strtok(NULL, ",");
				strcpy(vnum, token);
				token = strtok(NULL, ",");
				vt = atoi(token);
				token = strtok(NULL, ",");
				f = atoi(token);
				token = strtok(NULL, ",");
				s = atoi(token);
				token = strtok(NULL, ",");
				nd = atoi(token);
				
				fprintf(fp3, "%s,%s,%s,%s,%d,%d,%d,%d\n", user, pass, pi, vnum, vt, f, s, nd);
			}
			else {
				printf("Your vehicle has been successfully departured\n");
				Sleep(3000);
				finalValue = 0;
			}
		}
		fclose(fp1);
		fclose(fp3);
		remove("GuestFourWheeler_Repository.csv");
		rename(oldName1, newName1);
	}
	
	if (finalValue == 0) {
		if (fp2 != NULL) {
			fclose(fp2);
		}
		return;
	}
	
	char oldName2[] = "GuestCopyTwoWheeler.csv";
	char newName2[] = "GuestTwoWheeler_Repository.csv";
	if (fp2 != NULL) {
		fp3 = fopen("GuestCopyTwoWheeler.csv", "a");
		while (fgets(totalLine, sizeof(totalLine), fp2)) {
			char *token, copy[30];
			char user[50], pass[10];
			char vnum[20], pi[20];
			int vt, f, s, nd;
			
			int i = 0;
			token = strtok(totalLine, ",");
			strcpy(user, token);
			token = strtok(NULL, ",");
			strcpy(pass, token);
			
			token = strtok(NULL, ",");
			strcpy(pi, token);
			do {
				token++;
				copy[i] = *token;
				i += 1;
			}while (*token != '\0');
			
			int result = strcmp(parkingID, copy);
			if (result != 0) {
				token = strtok(NULL, ",");
				strcpy(vnum, token);
				token = strtok(NULL, ",");
				vt = atoi(token);
				token = strtok(NULL, ",");
				f = atoi(token);
				token = strtok(NULL, ",");
				s = atoi(token);
				token = strtok(NULL, ",");
				nd = atoi(token);
				
				fprintf(fp3, "%s,%s,%s,%s,%d,%d,%d,%d\n", user, pass, pi, vnum, vt, f, s, nd);
			}
			else {
				printf("Your vehicle has been successfully departured\n");
				Sleep(3000);
				finalValue = 0;
			}
		}
		fclose(fp2);
		fclose(fp3);
		remove("GuestTwoWheeler_Repository.csv");
		rename(oldName2, newName2);
	}
}