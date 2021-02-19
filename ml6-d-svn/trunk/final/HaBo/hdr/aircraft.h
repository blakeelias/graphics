#ifndef _AIRCRAFT_H
#define _AIRCRAFT_H

#include "globals.h"
#include <time.h>


typedef struct _aircraft_fields {
	
	double thrust; // 0 to 1
	double pitch_ctrl; // -1 to 1
	double yaw_ctrl; // -1 to 1
	double roll_ctrl; // -1 to 1

	double mass;
	double area; // reference area for calculating aerodynamic force (wing area is good enough)
	double dihedral;
	double lc_0; // lift coefficient when angle of attack = 0
	double dc_0; // drag coefficient when angle of attack = 0
	double aoa_c; // critical angle of attack
	double cg_x; // Center of gravity
	double cg_z;
	double mi_pitch; // Moment of inertia
	double mi_yaw;
	double mi_roll;
	double thrust_max;
		// more constants

	double pos[3];
	double d_pos[3]; // In aircraft's frame
	double dd_pos[3]; // In aircraft's frame
	double rot[3];
	double d_rot[3];
	double dd_rot[3];
	
	double airspeed;
	double vertspeed;

} aircraft_fields;

void *aircraft_fields_init();
void aircraft_fields_free(void *f);

void aircraft_user_control();
void aircraft_get_kinematics(node *a); // Fills up aircraft_fields with data from relevant kinematics node
void aircraft_update(node *a);

double aircraft_airspeed(aircraft_fields *f);
double aircraft_airspeed_squared(aircraft_fields *f);

double aircraft_lift(aircraft_fields *f);
double aircraft_lift_coeff(aircraft_fields *f);
double aircraft_drag(aircraft_fields *f);
double aircraft_drag_coeff(aircraft_fields *f);
double aircraft_gravity(aircraft_fields *f);
double aircraft_thrust(aircraft_fields *f);

#endif
