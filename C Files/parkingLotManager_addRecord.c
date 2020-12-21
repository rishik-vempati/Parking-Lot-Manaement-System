#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#include "Test.h"
#include "registeredUser_CarParking.h"

void parkingLotManager_addRecord(struct Slot* newSlot, char** userDetails) {
	FILE *fp;
	char fileName[30];
	strcpy(fileName, newSlot->vehicleNumber);
	strcat(fileName, ".txt");
	
	int day, month, year;
	int hours, minutes, seconds;
	time_t currentTime;
	
	time(&currentTime); //Obtains Current Time
	
	struct tm *localTime = localtime(&currentTime);
	hours = localTime->tm_hour;
	minutes = localTime->tm_min;
	seconds = localTime->tm_sec;
	day = localTime->tm_mday;
	month = localTime->tm_mon + 1;
	year = localTime->tm_year + 1900;
	
	fp = fopen(fileName, "w");
	fprintf(fp, "User Name of the Customer: %s.\n", userDetails[0]);
	fprintf(fp, "Type of the vehicle: %d wheeler.\n", newSlot->vehicleType);
	fprintf(fp, "Vehicle is parked at %d floor, %d slot number.\n", newSlot->floor, newSlot->slotNumber);
	fprintf(fp, "Total number of days for parking: %d.\n", newSlot->numberOfDays);
	fprintf(fp, "Vehicle is parked at: %02d/%02d/%d.\n", day, month, year);
	if (hours < 12) {
		fprintf(fp, "Parking time is: %02d:%02d:%02d am.\n", hours, minutes, seconds);
	}
	else {
		fprintf(fp, "Parking time is: %02d:%02d:%02d pm.\n", hours - 12, minutes, seconds);
	}
	
	fclose(fp);
	return;
}