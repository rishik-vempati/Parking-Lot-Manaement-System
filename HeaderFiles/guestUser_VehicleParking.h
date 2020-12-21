#ifndef GUESTUSER_VEHICLEPARKING_H
#define GUESTUSER_VEHICLEPARKING_H

//Creation Of Account Structure
struct GuestSlot {
	char firstName[50];
	char lastName[50];
	char vehicleNumber[50];
	int vehicleType;
	int floor, slotNumber;
	int numberOfDays;
};

//Functions Prototype
void getAllSlots();

void slotBooking(char** userDetails);
void storeGuestDetails(struct GuestSlot* newSlot, char** userDetails, char* idNumber);
void checkEmptySlot(int type, int *arr);
char* getParkingID(int row, int col);
struct GuestSlot* addGuestVehicleToParkingLot(int type, int days, char* vehicleNumber, int floor, int slotNumber, char* firstName, char* lastName);

void vehicleDeparture(char** userDetails);
char* getVNum(char* parkingID);
int checkID(char** userDetails, char* parkingID);
void getVehiclePos(char* parkingID, int* arr);
void DeleteVehicle(int row, int col);
void DeleteDetails(char* parkingID);
#endif