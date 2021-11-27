#include "main.h"
void opcontrol() {
	pros::GPS gps(1);
	pros::lcd::initialize();
	pros::lcd::print(0, "GPS Tester");
	pros::lcd::print(1, "------------------------");
	gps.initialize_full(0, 0, 0, 0, 0);

	while (true) {
		// Render data
		pros::lcd::print(2, "rot:%4.2f", gps.get_heading());
		pros::lcd::print(3, "locx:%4.2f", gps.get_status().x);
		pros::lcd::print(4, "locy:%4.2f", gps.get_status().y);
		pros::lcd::print(5, "error:%4.2f", gps.get_error());
		pros::delay(10);
	}
}
