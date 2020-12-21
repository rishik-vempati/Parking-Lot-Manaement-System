#include <stdio.h>
#include <string.h>

#include "guestUser_VehicleParking.h"

void parkingLotManager_deleteGuestRecord(char* vehicleNumber) {
	char fileName[20];
	strcpy(fileName, vehicleNumber);
	strcat(fileName, ".txt");
	remove(fileName);
}