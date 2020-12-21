#include <stdio.h>
#include <string.h>

#include "registeredUser_CarParking.h"

void parkingLotManager_deleteRecord(char* vehicleNumber) {
	char fileName[20];
	strcpy(fileName, vehicleNumber);
	strcat(fileName, ".txt");
	remove(fileName);
}