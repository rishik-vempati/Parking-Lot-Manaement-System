#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>

#include "Test.h"
#include "registeredUser_CarParking.h"

//Global Variable
int m2, d2;
int checkParkingSlots[4][10]; //To store the total number of vehicles parked
int numberOfDaysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
char parkingID[10];
char resultant[11];
char** vehicleNumbers;

//Linking C programs
void parkingLotManager_addRecord(struct Slot* newSlot, char** userDetails);
void parkingLotManager_deleteRecord(char* vehicleNumber);

void registeredUser_CarParking(char** userName_password) {
	int option, finish;
	char** userDetails = userName_password;
	system("cls");
	getBookedSlots();
	finish = 1;
	while (finish) {
		Sleep(3000);
		system("cls");
		gotoxy(50, 12);
		printf("\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb  VEHICLE PARKING  \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb");
		gotoxy(60, 15);
		printf("\t\tPress '1' for Slot Booking");
		gotoxy(60, 16);
		printf("\t\tPress '2' for Vehicle Departure");
		gotoxy(60, 17);
		printf("\t\tPress '3' for Change Password");
		gotoxy(60, 18);
		printf("\t\tPress '4' for Check Status");
		gotoxy(60, 19);
		printf("\t\tPress '5' for Unregister");
		gotoxy(60, 20);
		printf("\t\tPress '6' to EXIT");
		gotoxy(60, 23);
		printf("\t\tPress your action: ");
		scanf("%d", &option);
		if (option == 1) {
			getchar();
			SlotBooking(userDetails);
		}
		
		else if (option == 2) {
			getchar();
			VehicleDeparture(userDetails);
		}
		
		else if (option == 3) {
			getchar();
			updatePassword(userDetails);
		}
		
		else if (option == 4) {
			getchar();
			checkStatus(userDetails);
		}
		
		else if (option == 5) {
			getchar();
			int r = unregister(userDetails);
			if (r != 0) 
				finish = 0;
		}
		
		else if (option == 6) 
			finish = 0;
	}
	Sleep(3000);
}

//Functions Implementation
void getBookedSlots() {
	FILE *fp1, *fp2;
	fp1 = fopen("FourWheeler_Repository.csv", "r");
	fp2 = fopen("TwoWheeler_Repository.csv", "r");
	
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
			if (floorNumber == 1) {
				checkParkingSlots[floorNumber - 1][slotNumber - 1] = 1;
			}
			else if (floorNumber == 2) {
				checkParkingSlots[floorNumber - 1][slotNumber - 11] = 1;
			}
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
			if (floorNumber == 3) {
				checkParkingSlots[floorNumber - 1][slotNumber - 21] = 1;
			}
			else if (floorNumber == 4) {
				checkParkingSlots[floorNumber - 1][slotNumber - 31] = 1;
			}
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
			if (floorNumber == 1) {
				checkParkingSlots[floorNumber - 1][slotNumber - 1] = 1;
			}
			else if (floorNumber == 2) {
				checkParkingSlots[floorNumber - 1][slotNumber - 11] = 1;
			}
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
			if (floorNumber == 3) {
				checkParkingSlots[floorNumber - 1][slotNumber - 21] = 1;
			}
			else if (floorNumber == 4) {
				checkParkingSlots[floorNumber - 1][slotNumber - 31] = 1;
			}
		}
		
		fclose(fp2);
		
		return;
	}
}

void SlotBooking(char** userDetails) {
	system("cls");
	printf("\n\nINFORMATION TO BOOK A SLOT\n\n");
	//Creating Slot For Normal Booking Customer
	//Creating a structure variable for a customer
	struct Slot* newSlot;
	
	int arr[2], type, check, days;
	int vehicleLength = 10;
	int vehicleCount = 0;
	char firstName[50], lastName[50];
	char vehicleNumber[50];

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
				
				isSlotFree(type, arr);
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
					printf("\n\nFOUR WHEELER VEHICLES - 20 SLOTS\n\n");
					printf("------------------------------------------------------------------\n");
					printf("Floor    |\t\t\t         Slot Numbers\n");
					printf("------------------------------------------------------------------\n");
					printf("1st Floor|\t\t  1   2   3   4   5   6   7   8   9  10\n"); 
					printf("------------------------------------------------------------------\n");
					printf("2nd Floor|\t\t 11  12  13  14  15  16  17  18  19  20\n");
					printf("------------------------------------------------------------------\n");
					char* idNumber = generateParkingID(arr[0], arr[1]);
					newSlot = addVehicleToParkingLot(type, days, vehicleNumber, arr[0], arr[1]);
					printf("Parking ID: %s\n", idNumber);
					if (arr[0] == 0) 
						printf("Your vehicle has been parked at %d floor, %d slot number\n", arr[0] + 1, arr[1] + 1);
					else if (arr[0] == 1) 
						printf("Your vehicle has been parked at %d floor, %d slot number\n", arr[0] + 1, arr[1] + 11);
					//As we have the details of the customer, now this information to his file with name of his vehicleNumber
					storeDetails(newSlot, userDetails, idNumber);
					parkingLotManager_addRecord(newSlot, userDetails);
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
				
				isSlotFree(type, arr);
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
					printf("\n\nTWO WHEELER VEHICLES - 20 SLOTS\n\n");
					printf("----------------------------------------------------------------------\n");
					printf("Floor    |\t\t\t         Slot Numbers\n");
					printf("----------------------------------------------------------------------\n");
					printf("3rd Floor|\t\t21   22   23   24   25   26   27   28   29  30\n"); 
					printf("----------------------------------------------------------------------\n");
					printf("4th Floor|\t\t31   32   33   34   35   36   37   38   39  40\n");
					printf("----------------------------------------------------------------------\n");
					char* idNumber = generateParkingID(arr[0], arr[1]);
					newSlot = addVehicleToParkingLot(type, days, vehicleNumber, arr[0], arr[1]);
					printf("Parking ID: %s\n", idNumber);
					if (arr[0] == 2) 
						printf("Your vehicle has been parked at %d floor, %d slot number\n", arr[0] + 1, arr[1] + 21);
					else if (arr[0] == 3) 
						printf("Your vehicle has been parked at %d floor, %d slot number\n", arr[0] + 1, arr[1] + 31);
					//As we have the details of the customer, now this information to his file with name of his vehicleNumber
					storeDetails(newSlot, userDetails, idNumber);
					parkingLotManager_addRecord(newSlot, userDetails);
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

void VehicleDeparture(char** userDetails) {
	system("cls");
	printf("\n\nINFORMATION TO DEPARTURE A VEHICLE\n\n");
	
	char idNumber[20];
	int arr[2];
	printf("Enter your Parking ID: ");
	gets(idNumber);
	int finalValue = checkParkingID(userDetails, idNumber);
	if ((finalValue == 1) || (finalValue == -1)){
		printf("\n\nParking ID is Invalid\n");
		printf("Press any key to continue..");
		getch();
		return;
	}
	
	char* vehicleNumber = getVehicleNumber(idNumber);
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
					getVehiclePosition(idNumber, arr);
					if ((arr[0] != -1) && (arr[1] != -1)) {
						int row, col;
						row = arr[0];
						col = arr[1];
						deleteVehicle(row, col);
						deleteDetails(idNumber);
					}
					parkingLotManager_deleteRecord(vehicleNumber);
					int type;
					if ((arr[0] == 0) || (arr[0] == 1)) {
						type = 4;
					}
					else if ((arr[0] == 2) || (arr[0] == 3)) {
						type = 2;
					}
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
					getVehiclePosition(idNumber, arr);
					if ((arr[0] != -1) && (arr[1] != -1)) {
						int row, col;
						row = arr[0];
						col = arr[1];
						deleteVehicle(row, col);
						deleteDetails(idNumber);
						Sleep(3000);
					}
					system("cls");
					int s = (ad - remainingDays);
					int type;
					if ((arr[0] == 0) || (arr[0] == 1)) {
						type = 4;
					}
					else if ((arr[0] == 2) || (arr[0] == 3)) {
						type = 2;
					}
					parkingCost(s, type);
					parkingLotManager_deleteRecord(vehicleNumber);
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
	
	else if (remainingDays < 0) {
		int store = (-1 * remainingDays);
		printf("\nYou have parked %d days more than you said\n", store);
		arr[0] = arr[1] = -1;
		getVehiclePosition(idNumber, arr);
		if ((arr[0] != -1) && (arr[1] != -1)) {
			int row, col;
			row = arr[0];
			col = arr[1];
			deleteVehicle(row, col);
			deleteDetails(idNumber);
		}
		int type;
		if ((arr[0] == 0) || (arr[0] == 1)) {
			type = 4;
		}
		else if ((arr[0] == 2) || (arr[0] == 3)) {
			type = 2;
		}
		int s = store + ad;
		parkingCost(s, type);
		parkingLotManager_deleteRecord(vehicleNumber);
		printf("Press any key to continue..");
		getch();
	}
}	

void checkStatus(char** userDetails) {
	system("cls");
	char idNumber[20];
	printf("\n\nINFORMATION FOR CHECKING THE STATUS OF VEHICLE\n");
	printf("Enter your Parking ID: ");
	gets(idNumber);
	int finalValue = checkParkingID(userDetails, idNumber);
	if ((finalValue == 1) || (finalValue == -1)){
		printf("\n\nParking ID is Invalid\n");
		printf("Press any key to continue..");
		getch();
		return;
	}
	
	char* vehicleNumber = getVehicleNumber(idNumber);
	Sleep(5000);
	char fileName[20];
	char ch;
	strcpy(fileName, vehicleNumber);
	strcat(fileName, ".txt");
	
	int d, mo, y, ad;
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
		}
		fclose(fp);
	}
	int day, month, year;
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
	
	if (remainingDays == 0) {
		system("cls");
		createRectangularBox(45, 10, 115, 25);
		int l = 12;
		FILE *fp;
		fp = fopen(fileName, "r");
		char totalLine[100];
		while (fgets(totalLine, sizeof(totalLine), fp)) {
			gotoxy(60, l); 
			puts(totalLine);
			l += 1;
		}
		fclose(fp);
		
		gotoxy(60, 20);
		printf("You have to departure your vehicle today..");
		Sleep(5000);
		gotoxy(60, 22);
		printf("Press any key to continue..");
		getch();
	}
	
	else if (remainingDays > 0) {
		system("cls");
		createRectangularBox(45, 10, 115, 25);
		int l = 12;
		FILE *fp;
		fp = fopen(fileName, "r");
		char totalLine[100];
		while (fgets(totalLine, sizeof(totalLine), fp)) {
			gotoxy(60, l); 
			puts(totalLine);
			l += 1;
		}
		fclose(fp);
		
		gotoxy(60, 20);
		printf("There are %d days to departure..", remainingDays);
		Sleep(5000);
		gotoxy(60, 22);
		printf("Press any key to continue..");
		getch();
	}
	
	else if (remainingDays < 0) {
		system("cls");
		createRectangularBox(45, 10, 115, 25);
		int l = 12;
		FILE *fp;
		fp = fopen(fileName, "r");
		char totalLine[100];
		while (fgets(totalLine, sizeof(totalLine), fp)) {
			gotoxy(60, l); 
			puts(totalLine);
			l += 1;
		}
		fclose(fp);
		
		int store = (-1 * remainingDays);
		gotoxy(60, 20);
		printf("WARNING!!");
		gotoxy(60, 21);
		printf("You have parked %d days more than you said.\n", store);
		gotoxy(60, 22);
		printf("You have to departure your vehicle as soon as possible..\n\n\n");
		Sleep(5000);
		gotoxy(60, 24);
		printf("Press any key to continue..");
		getch();
	}
}

void storeDetails(struct Slot* newSlot, char** userDetails, char* idNumber) {
	FILE *fp;
	if (newSlot->vehicleType == 2) {
		fp = fopen("TwoWheeler_Repository.csv", "a");
	}
	else if (newSlot->vehicleType == 4) {
		fp = fopen("FourWheeler_Repository.csv", "a");
	}
	
	if (fp == NULL) {
		return;
	}
	
	fprintf(fp, "%s, %s, %s, %s, %d, %d, %d, %d\n", userDetails[0], userDetails[1], idNumber, newSlot->vehicleNumber, newSlot->vehicleType, newSlot->floor, newSlot->slotNumber, newSlot->numberOfDays);
	fclose(fp);
}

struct Slot* addVehicleToParkingLot(int type, int days, char* vehicleNumber, int floor, int slotNumber) {
	struct Slot* newSlot = (struct Slot*)malloc(sizeof(struct Slot));
	newSlot->vehicleType = type;
	newSlot->floor = floor + 1;
	if (newSlot->vehicleType == 4) {
		if (newSlot->floor == 1) {
			newSlot->slotNumber = slotNumber + 1;
		}
		else if (newSlot->floor == 2) {
			newSlot->slotNumber = slotNumber + 11;
		}
	}
	else if (newSlot->vehicleType == 2) {
		if (newSlot->floor == 3) {
			newSlot->slotNumber = slotNumber + 21;
		}
		else if (newSlot->floor == 4) {
			newSlot->slotNumber = slotNumber + 31;
		}
	}
	newSlot->numberOfDays = days;
	strcpy(newSlot->vehicleNumber, vehicleNumber);
	
	checkParkingSlots[floor][slotNumber] = 1;
	return newSlot;
}
	
	
void isSlotFree(int type, int *arr) {
	int floor, slotNumber;
	int fromFloor = 0, toFloor = 2;
	if (type == 2) {
		fromFloor += 2;
		toFloor += 2;
	}
	
	for (floor = fromFloor; floor < toFloor; floor++) {
		for (slotNumber = 0; slotNumber < 10; slotNumber++) {
			if (checkParkingSlots[floor][slotNumber] == 0) {
				arr[0] = floor;
				arr[1] = slotNumber;
				return;
			}
		}
	}
	
	if ((floor == 2) || (floor == 4)) {
		arr[0] = -1;
		arr[1] = -1;
	}
}

int checkVehicleNumber(char* vehicleNumber) {
	FILE *fp1, *fp2, *fp3, *fp4;
	
	fp1 = fopen("FourWheeler_Repository.csv", "r");
	fp2 = fopen("TwoWheeler_Repository.csv", "r");
	fp3 = fopen("GuestFourWheeler_Repository.csv", "r");
	fp4 = fopen("GuestTwoWheeler_Repository.csv", "r");
	
	int finalValue = 1;
	if ((fp1 == NULL) && (fp2 == NULL) && (fp3 == NULL) && (fp4 == NULL)) {
		return -1;
	}
	
	char totalLine[100];
	if (fp1 != NULL) {
		while (fgets(totalLine, sizeof(totalLine), fp1)) {
			char *token, copy[30];
			int i = 0;
			token = strtok(totalLine, ",");
			token = strtok(NULL, ",");
			token = strtok(NULL, ",");
			token = strtok(NULL, ",");
			do {
				token++;
				copy[i] = *token;
				i += 1;
			}while (*token != '\0');
			int result = strcmp(vehicleNumber, copy);
			if (result == 0) {
				finalValue = 0;
				break;
			}
		}
		fclose(fp1);
		if (finalValue == 0) {
			if (fp2 != NULL) {
				fclose(fp2);
			}
			if (fp3 != NULL) {
				fclose(fp3);
			}
			if (fp4 != NULL) {
				fclose(fp4);
			}
			return finalValue;
		}
	}
	
	if (fp2 != NULL) {
		while (fgets(totalLine, sizeof(totalLine), fp2)) {
			char *token, copy[30];
			int i = 0;
			token = strtok(totalLine, ",");
			token = strtok(NULL, ",");
			token = strtok(NULL, ",");
			token = strtok(NULL, ",");
			do {
				token++;
				copy[i] = *token;
				i += 1;
			}while (*token != '\0');
			int result = strcmp(vehicleNumber, copy);
			if (result == 0) {
				finalValue = 0;
				break;
			}
		}
		fclose(fp2);
		if (finalValue == 0) {
			if (fp3 != NULL) {
				fclose(fp3);
			}
			if (fp4 != NULL) {
				fclose(fp4);
			}
			return finalValue;
		}
	}	

	if (fp3 != NULL) {
		while (fgets(totalLine, sizeof(totalLine), fp3)) {
			char *token, copy[30];
			int i = 0;
			token = strtok(totalLine, ",");
			token = strtok(NULL, ",");
			token = strtok(NULL, ",");
			token = strtok(NULL, ",");
			do {
				token++;
				copy[i] = *token;
				i += 1;
			}while (*token != '\0');
			int result = strcmp(vehicleNumber, copy);
			if (result == 0) {
				finalValue = 0;
				break;
			}
		}
		fclose(fp3);
		if (finalValue == 0) {
			if (fp4 != NULL) {
				fclose(fp4);
			}
			return finalValue;
		}
	}
	
	if (fp4 != NULL) {
		while (fgets(totalLine, sizeof(totalLine), fp4)) {
			char *token, copy[30];
			int i = 0;
			token = strtok(totalLine, ",");
			token = strtok(NULL, ",");
			token = strtok(NULL, ",");
			token = strtok(NULL, ",");
			do {
				token++;
				copy[i] = *token;
				i += 1;
			}while (*token != '\0');
			int result = strcmp(vehicleNumber, copy);
			if (result == 0) {
				finalValue = 0;
				break;
			}
		}
		fclose(fp4);
		if (finalValue == 0) {
			return finalValue;
		}
	}
	
	return finalValue;
}

char* generateParkingID(int row, int col) {
	for (int i = 0; i < 10; i++) {
		parkingID[i] = '\0';
	}
	strcat(parkingID, "PC-");
	if (row == 0) {
		strcat(parkingID, "1F-");
		if ((col >= 0) && (col < 9)) {
			strcat(parkingID, "00");
			char str[2];
			sprintf(str, "%d", (col + 1));
			strcat(parkingID, str);
		}
		else {
			strcat(parkingID, "010");
		}
	}
	else if (row == 1) {
		strcat(parkingID, "2F-");
		if ((col >= 0) && (col < 9)) {
			strcat(parkingID, "0");
			char str[3];
			sprintf(str, "%d", (col + 11));
			strcat(parkingID, str);
		}
		else {
			strcat(parkingID, "020");
		}
	}
	else if (row == 2) {
		strcat(parkingID, "3F-");
		if ((col >= 0) && (col < 9)) {
			strcat(parkingID, "0");
			char str[3];
			sprintf(str, "%d", (col + 21));
			strcat(parkingID, str);
		}
		else {
			strcat(parkingID, "030");
		}
	}
	else if (row == 3) {
		strcat(parkingID, "4F-");
		if ((col >= 0) && (col < 9)) {
			strcat(parkingID, "0");
			char str[3];
			sprintf(str, "%d", (col + 31));
			strcat(parkingID, str);
		}
		else {
			strcat(parkingID, "040");
		}
	}
	
	return parkingID;
}

void getVehiclePosition(char* parkingID, int* arr) {
	FILE *fp1, *fp2;
	
	int finalValue1 = 1;
	fp1 = fopen("FourWheeler_Repository.csv", "r");
	fp2 = fopen("TwoWheeler_Repository.csv", "r");
	
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
				
				if (floor == 1) {
					arr[0] = floor - 1;
					arr[1] = slot - 1;
				}
				else if (slot == 2) {
					arr[0] = floor - 1;
					arr[1] = slot - 11;
				}
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
					
				if (floor == 3) {
					arr[0] = floor - 1;
					arr[1] = slot - 21;
				}
				else if (slot == 4) {
					arr[0] = floor - 1;
					arr[1] = slot - 31;
				}
			}
		}
		fclose(fp2);
	}
}
	
int checkParkingID(char** userDetails, char* parkingID) {
	FILE *fp1, *fp2;
	
	int finalValue = 1;
	fp1 = fopen("FourWheeler_Repository.csv", "r");
	fp2 = fopen("TwoWheeler_Repository.csv", "r");
	if ((fp1 == NULL) && (fp2 == NULL)) {
		return -1;
	}
	
	char totalLine[100];
	if (fp1 != NULL) {
		while (fgets(totalLine, sizeof(totalLine), fp1)) {
			char *token, copy[30];
			int i = 0;
			token = strtok(totalLine, ",");
			if (strcmp(token, userDetails[0]) == 0) {
				token = strtok(NULL, ",");
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
			int i = 0;
			token = strtok(totalLine, ",");
			if (strcmp(token, userDetails[0]) == 0) {
				token = strtok(NULL, ",");
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
		fclose(fp2);
		if (finalValue == 0) {
			return finalValue;
		}
	}
	
	return finalValue;
}

char* getVehicleNumber(char* parkingID) {
	for (int j = 0; j < 11; j++) {
		resultant[j] = '\0';
	}
	FILE *fp1, *fp2;
	
	fp1 = fopen("FourWheeler_Repository.csv", "r");
	fp2 = fopen("TwoWheeler_Repository.csv", "r");
	
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
				fclose(fp1);
				if (fp2 != NULL) {
					fclose(fp2);
				}
				return resultant;
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

void deleteVehicle(int row, int col) {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 10; j++) {
			if (i == row) {
				if (j == col) {
					checkParkingSlots[i][j] = 0;
					return;
				}
			}
		}
	}
}

void deleteDetails(char* parkingID) {
	FILE *fp1, *fp2, *fp3;
	fp1 = fopen("FourWheeler_Repository.csv", "r");
	fp2 = fopen("TwoWheeler_Repository.csv", "r");
	
	if ((fp1 == NULL) && (fp2 == NULL)) {
		return;
	}
	
	int finalValue = 1;
	char totalLine[100];
	
	char oldName1[] = "CopyFourWheeler.csv";
	char newName1[] = "FourWheeler_Repository.csv";
	if (fp1 != NULL) {
		fp3 = fopen("CopyFourWheeler.csv", "a");
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
				finalValue = 0;
			}
		}
		fclose(fp1);
		fclose(fp3);
		remove("FourWheeler_Repository.csv");
		rename(oldName1, newName1);
	}
	
	if (finalValue == 0) {
		if (fp2 != NULL) {
			fclose(fp2);
		}
		return;
	}
	
	char oldName2[] = "CopyTwoWheeler.csv";
	char newName2[] = "TwoWheeler_Repository.csv";
	if (fp2 != NULL) {
		fp3 = fopen("CopyTwoWheeler.csv", "a");
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
				finalValue = 0;
			}
		}
		fclose(fp2);
		fclose(fp3);
		remove("TwoWheeler_Repository.csv");
		rename(oldName2, newName2);
	}
}

int countLeapYears(struct Date d)
{
    int years = d.year;
    if (d.month <= 2)
		years--;
    return years / 4 
           - years / 100
           + years / 400;
}

int getDifference(struct Date dt1, struct Date dt2)
{
    long int n1 = dt1.year * 365 + dt1.date;
 
    for (int i = 0; i < dt1.month - 1; i++)
        n1 += numberOfDaysInMonth[i];

    n1 += countLeapYears(dt1);
 
    long int n2 = dt2.year * 365 + dt2.date;
    for (int i = 0; i < dt2.month - 1; i++)
        n2 += numberOfDaysInMonth[i];
    n2 += countLeapYears(dt2);
	
    return (n2 - n1);
}

void differenceBetweenTimePeriod(struct Time start, struct Time stop, struct Time *diff) {
   while (stop.seconds > start.seconds) {
	   --start.minutes;
       start.seconds += 60;
   }
   diff->seconds = start.seconds - stop.seconds;
   while (stop.minutes > start.minutes) {
	   --start.hours;
       start.minutes += 60;
   }
   diff->minutes = start.minutes - stop.minutes;
   diff->hours = start.hours - stop.hours;
}

int isLeap(int y)  
{  
    if (y % 100 != 0 && y % 4 == 0 || y % 400 == 0)  
        return 1;  
		
    return 0;  
}

int offsetDays(int d, int m, int y)  
{  
    int offset = d;  
  
    if(m - 1 == 11)  
        offset += 335; 
    if(m - 1 == 10) 
        offset += 304; 
    if(m - 1 == 9) 
        offset += 273; 
    if(m - 1 == 8) 
        offset += 243; 
    if(m - 1 == 7) 
        offset += 212; 
    if(m - 1 == 6) 
        offset += 181; 
    if(m - 1 == 5) 
        offset += 151; 
    if(m - 1 == 4) 
        offset += 120; 
    if(m - 1 == 3) 
        offset += 90; 
    if(m - 1 == 2) 
        offset += 59; 
    if(m - 1 == 1) 
        offset += 31;  
  
    if (isLeap(y) && m > 2)  
        offset += 1;  
 
    return offset;  
}

void revoffsetDays(int offset, int y)  
{  
    int month[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };  
  
    if (isLeap(y))  
        month[2] = 29;  
    int i;  
    for (i = 1; i <= 12; i++)  
    {  
        if (offset <= month[i])  
            break;  
        offset = offset - month[i];  
    }  
  
    d2 = offset;  
    m2 = i;  
}

struct Date addDays(int d1, int m1, int y1, int x)  
{  
    int offset1 = offsetDays(d1, m1, y1);  
    int remDays = isLeap(y1) ? (366 - offset1) : (365 - offset1);  
  
    int y2, offset2 = 0;  
    if (x <= remDays)  
    {  
        y2 = y1;  
        offset2 =offset1 + x;  
    }  
  
    else
    {    
        x -= remDays;  
        y2 = y1 + 1;  
        int y2days = isLeap(y2) ? 366 : 365;  
        while (x >= y2days)  
        {  
            x -= y2days;  
            y2++;  
            y2days = isLeap(y2) ? 366 : 365;  
        }  
        offset2 = x;  
    }  
    revoffsetDays(offset2, y2);
	
	//Creating Of Date variable
	struct Date d;
	d.date = d2;
	d.month = m2;
	d.year = y2;
	return d;
}

void updatePassword(char** userDetails) {
	FILE *fp1, *fp2, *fp3, *fp4;
	
	system("cls");
	char oldName[] = "CopyAccount_Details.csv";
	char newName[] = "Account_Details.csv";
	
	fp1 = fopen("Account_Details.csv", "r");
	if (fp1 != NULL) {
		fp2 = fopen("CopyAccount_Details.csv", "a");
		char totalLine[100];
		while (fgets(totalLine, sizeof(totalLine), fp1)) {
			char* token;
			token = strtok(totalLine, ",");
			int r = strcmp(token, userDetails[0]);
			if (r == 0) {
				changePassword(userDetails);
				fprintf(fp2, "%s, %s,\n", userDetails[0], userDetails[1]);
			}
			else {
				char user[30], pass[20];
				strcpy(user, token);
				token = strtok(NULL, ",");
				strcpy(pass, token);
				fprintf(fp2, "%s,%s,\n", user, pass);
			}
		}
		fclose(fp1);
		fclose(fp2);
		remove("Account_Details.csv");
		rename(oldName, newName);
	}
	
	char oldName1[] = "CopyFourWheeler.csv";
	char newName1[] = "FourWheeler_Repository.csv";
	
	fp3 = fopen("FourWheeler_Repository.csv", "r");
	
	if (fp3 != NULL) {
		fp2 = fopen("CopyFourWheeler.csv", "a");
		char totalLine[100];
		while (fgets(totalLine, sizeof(totalLine), fp3)) {
			char* token;
			token = strtok(totalLine, ",");
			int r = strcmp(token, userDetails[0]);
			if (r == 0) {
				char vnum[20], pi[20];
				int vt, f, s, nd;
				
				token = strtok(NULL, ",");
				token = strtok(NULL, ",");
				strcpy(pi, token);
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
				fprintf(fp2, "%s, %s,%s,%s,%d,%d,%d,%d\n", userDetails[0], userDetails[1], pi, vnum, vt, f, s, nd);
			}
			else {
				char user[30], pass[50];
				char vnum[20], pi[20];
				int vt, f, s, nd;
				
				strcpy(user, token);
				token = strtok(NULL, ",");
				strcpy(pass, token);
				token = strtok(NULL, ",");
				strcpy(pi, token);
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
					
				fprintf(fp2, "%s,%s,%s,%s,%d,%d,%d,%d\n", user, pass, pi, vnum, vt, f, s, nd);
			}
		}
		fclose(fp3);
		fclose(fp2);
		remove("FourWheeler_Repository.csv");
		rename(oldName1, newName1);
	}
	
	char oldName2[] = "CopyTwoWheeler.csv";
	char newName2[] = "TwoWheeler_Repository.csv";
	
	fp4 = fopen("TwoWheeler_Repository.csv", "r");
	if (fp4 != NULL) {
		fp2 = fopen("CopyTwoWheeler.csv", "a");
		char totalLine[100];
		while (fgets(totalLine, sizeof(totalLine), fp4)) {
			char* token;
			token = strtok(totalLine, ",");
			int r = strcmp(token, userDetails[0]);
			if (r == 0) {
				char vnum[20], pi[20];
				int vt, f, s, nd;
				
				token = strtok(NULL, ",");
				token = strtok(NULL, ",");
				strcpy(pi, token);
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
					
				fprintf(fp2, "%s, %s,%s,%s,%d,%d,%d,%d\n", userDetails[0], userDetails[1], pi, vnum, vt, f, s, nd);
			}
			else {
				char user[30], pass[50];
				char vnum[20], pi[20];
				int vt, f, s, nd;
				
				strcpy(user, token);
				token = strtok(NULL, ",");
				strcpy(pass, token);
				token = strtok(NULL, ",");
				strcpy(pi, token);
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
					
				fprintf(fp2, "%s,%s,%s,%s,%d,%d,%d,%d\n", user, pass, pi, vnum, vt, f, s, nd);
			}
		}
		
		fclose(fp4);
		fclose(fp2);
		remove("TwoWheeler_Repository.csv");
		rename(oldName2, newName2);
	}
}

void changePassword(char** userDetails) {
	system("cls");
	printf("\n\n");
	printf("THE PASSWORD SHOULD BE A 8 CHARACTER PASSWORD\n");
	printf("THE PASSWORD SHOULD CONTAIN ATLEAST 1 UPPER CASE LETTER\n");
	printf("THE PASSWORD SHOULD CONTAIN ATLEAST 1 LOWER CASE LETTER\n");
	printf("THE PASSWORD SHOULD CONTAIN ATLEAST 1 DIGIT\n");
				
	int countLower, countUpper, countDigit, counter, c;
	countLower = countUpper = countDigit = counter = c = 0;

	char temp1[9];
	char temp2[9];
				
	printf("Enter your new password: ");
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
		printf("\nSTRONG PASSWORD!!\n");
		printf("Enter your password again: ");
					
		while (c < 8) {
			temp2[c] = getch();
			putchar('*');
			c += 1;
		}
		temp2[c] = '\0';

		printf("\nRechecking your password....\n");
		if (strcmp(temp1, temp2) == 0) {
			printf("\nPassword MATCHED!!\n");
			printf("New Password is updated successfully\n\n");
			strcpy(userDetails[1], temp2);
			printf("\nPress any key to continue..");
			getch();
			return;
		}
		else {
			printf("\nOOPS!! On rechecking.. your have entered another password\n");
			Sleep(3000);
			changePassword(userDetails);
		}
	}
	else {
		printf("\nThe conditions in the password didn't met\n");
		Sleep(3000);
		changePassword(userDetails);
	}
}

int unregister(char** userDetails) {
	system("cls");
	FILE *fp1, *fp2, *fp3;
	
	int counter = 0;
	fp1 = fopen("FourWheeler_Repository.csv", "r");
	if (fp1 != NULL) {
		char totalLine[100];
		while (fgets(totalLine, sizeof(totalLine), fp1)) {
			char* token;
			token = strtok(totalLine, ",");
			int r = strcmp(token, userDetails[0]);
			if (r == 0) {
				counter += 1;
			}
		}
		fclose(fp1);
		
		if (counter != 0) {
			printf("\n\nYou can't unregister your account now, Your vehicle is still in the parking lot\n");
			printf("You have to departure your vehicle first\n\n");
			printf("Press any key to continue..");
			getch();
			return 0;
		}
	}
	
	counter = 0;
	fp3 = fopen("TwoWheeler_Repository.csv", "r");
	if (fp3 != NULL) {
		char totalLine[100];
		while (fgets(totalLine, sizeof(totalLine), fp3)) {
			char* token;
			token = strtok(totalLine, ",");
			int r = strcmp(token, userDetails[0]);
			if (r == 0) {
				counter += 1;
			}
		}
		fclose(fp3);
		
		if (counter != 0) {
			printf("\n\nYou can't unregister your account now, Your vehicle is still in the parking lot\n");
			printf("You have to departure your vehicle first\n\n");
			printf("Press any key to continue..");
			getch();
			return 0;
		}
	}

	int r;
	counter = 0;
	fp1 = fopen("Account_Details.csv", "r");
	if (fp1 != NULL) {
		fp2 = fopen("CopyAccount_Details.csv", "a");
		char totalLine[100];
		while (fgets(totalLine, sizeof(totalLine), fp1)) {
			char* token;
			token = strtok(totalLine, ",");
			int r = strcmp(token, userDetails[0]);
			if (r != 0) {
				char user[50], pass[20];
				strcpy(user, token);
				token = strtok(NULL, ",");
				strcpy(pass, token);
				fprintf(fp2, "%s,%s,\n", user, pass);
			}
		}
		fclose(fp1);
		fclose(fp2);
	}
	
	remove("Account_Details.csv");
	rename("CopyAccount_Details.csv", "Account_Details.csv");
	printf("\n\nUsername: %s\n", userDetails[0]);
	printf("Your account has been successfully unregistered\n\n");
	return 1;
}

void parkingCost(int noOfDays, int type) {
	createRectangularBox(55, 11, 115, 22);
	int cost;
	if ((noOfDays >= 0) && (noOfDays < 10)) {
		gotoxy(70, 13);
		printf("Total parking days are %d.\n", noOfDays);
		if (type == 2) 
			cost = (noOfDays * 10);
		else if (type == 4) {
			cost = (noOfDays * 20);
		}
		gotoxy(70, 15);
		printf("Total parking cost is Rs. %d\n", cost);
	}
	else if ((noOfDays >= 10) && (noOfDays < 20)) {
		gotoxy(70, 13);
		printf("Total parking days are %d.\n", noOfDays);
		if (type == 2) 
			cost = (noOfDays * 20);
		else if (type == 4)
			cost = (noOfDays * 40);
		gotoxy(70, 15);
		printf("Total parking cost is Rs. %d\n", cost);
	}
	else if ((noOfDays >= 20) && (noOfDays <= 30)) {
		gotoxy(70, 13);
		printf("Total parking days are %d.\n", noOfDays);
		if (type == 2) 
			cost = (noOfDays * 30);
		else if (type == 4)
			cost = (noOfDays * 60);
		gotoxy(70, 15);
		printf("Total parking cost is Rs. %d\n", cost);
	}
	int day, month, year;
	int hours, minutes, seconds;
	time_t currentTime;
	
	time(&currentTime); //Obtains Current Time
	
	struct tm *localTime = localtime(&currentTime);
	day = localTime->tm_mday;
	month = localTime->tm_mon + 1;
	year = localTime->tm_year + 1900;
	hours = localTime->tm_hour;
	minutes = localTime->tm_min;
	seconds = localTime->tm_sec;
	
	gotoxy(70, 18);
	printf("Vehicle is departured at: %02d/%02d/%d.", day, month, year);
	gotoxy(70, 20);
	if (hours < 12) {
		printf("Departured time is: %02d:%02d:%02d am.", hours, minutes, seconds);
	}
	else {
		printf("Departured time is: %02d:%02d:%02d pm.", hours - 12, minutes, seconds);
	}
	Sleep(5000);
}