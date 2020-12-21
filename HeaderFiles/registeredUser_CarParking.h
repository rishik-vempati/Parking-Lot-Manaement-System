#ifndef REGISTEREDUSER_CARPARKING_H
#define REGISTEREDUSER_CARPARKING_H

//Creating structure for an slot
struct Slot {
	char vehicleNumber[20];
	int vehicleType;
	int floor, slotNumber;
	int numberOfDays;
};

struct Date {
    int date;
	int month;
	int year;
};

struct Time {
   int hours;
   int minutes;
   int seconds;
};

//Functions Prototypes
void getBookedSlots();

void SlotBooking(char** userDetails);
void isSlotFree(int type, int *arr);
int checkVehicleNumber(char* vehicleNumber);
char* generateParkingID(int row, int col);
struct Slot* addVehicleToParkingLot(int type, int days, char* vehicleNumber, int floor, int slotNumber);

void VehicleDeparture(char** userDetails);
void getVehiclePosition(char* parkingID, int* arr);
void deleteVehicle(int row, int col);
void deleteDetails(char* vehicleNumber);
void parkingCost(int noOfDays, int type);
int checkParkingID(char** userDetails, char* parkingID);
char* getVehicleNumber(char* parkingID);

void checkStatus(char** userDetails);

void storeDetails(struct Slot* newSlot, char** userDetails, char* idNumber);

void differenceBetweenTimePeriod(struct Time time1, struct Time time2, struct Time *difference);

int countLeapYears(struct Date date);
int getDifference(struct Date date1, struct Date date2);

int isLeap(int y);
int offsetDays(int d, int m, int y);
void revoffsetDays(int offset, int y);
struct Date addDays(int d1, int m1, int y1, int x);

void updatePassword(char** userDetails);
void changePassword(char** userDetails);
int unregister(char** userDetails);
#endif