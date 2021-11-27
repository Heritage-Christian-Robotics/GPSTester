#include "main.h"

pros::GPS gps(1);
double gpsOffset;
int pastGPS;
int currentGPS;
double elasped_rotation;

void updateFilters(){
	pastGPS = currentGPS;
	currentGPS = gps.get_heading();
	if(pastGPS % 360 > 350 && currentGPS % 360 < 10) gpsOffset += 360;
	if(pastGPS % 360 < 10 && currentGPS % 360 > 350) gpsOffset -= 360;
	elasped_rotation = gps.get_rotation();
}

double getFilteredGPS(){
	return gps.get_heading() + gpsOffset;
}

void opcontrol() {
	pros::lcd::initialize();
	pros::lcd::print(0, "GPS Tester");
	pros::lcd::print(1, "------------------------");
	gps.initialize_full(0, 0, 0, 0, 0);
	gps.set_data_rate(5);

	while (true) {
		updateFilters();
		// Render data
		pros::lcd::print(2, "rot:%4.2f", gps.get_heading());
		pros::lcd::print(3, "locx:%4.2f", gps.get_status().x);
		pros::lcd::print(4, "locy:%4.2f", gps.get_status().y);
		pros::lcd::print(5, "error:%4.2f", gps.get_error());
		pros::lcd::print(6, "rot:%4.2f", getFilteredGPS());
		pros::lcd::print(7, "rotation:%4.2f", elasped_rotation);
		pros::delay(10);
	}
}
