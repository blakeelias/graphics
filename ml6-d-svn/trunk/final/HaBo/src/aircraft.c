#include <stdlib.h>
#include <math.h>
#include "aircraft.h"
#include "environment.h"
#include "macros.h"
#include "signal.h"


void *aircraft_fields_init() {

	aircraft_fields *f = (aircraft_fields *) malloc(sizeof(aircraft_fields));
	
	/*
	f->thrust = 0;
	f->pitch_ctrl = 0;
	f->yaw_ctrl = 0;
	f->roll_ctrl = 0;
	f->mass = 30000;
	f->area = 80;
	f->dihedral = 0;
	f->lc_0 = 0.5;
	f->dc_0 = 0.03;
	f->aoa_c = 20;
	f->cg_x = 0;
	f->cg_z = 0;
	f->mi_pitch = .35;
	f->mi_yaw = .4;
	f->mi_roll = .2;
	f->thrust_max = 200000;
	*/
	
	return (void *) f;
}

void aircraft_fields_free(void *f) {
	free((aircraft_fields *) f);
}




void aircraft_user_control() {

	///*
	obj_kinematics *k = usrctl_node->parent->n.k;
	aircraft_fields *f = (aircraft_fields *) usrctl_node->n.o->f;
	
	int v = 10, w = 45; // temporary
	
	k->dd_pos[0] = 0;
	k->dd_pos[1] = 0;
	k->dd_pos[2] = 0;
	//matrix_make_ident(k->d_rot);
	
	double dd_rot_v[3];
	dd_rot_v[0] = 0;
	dd_rot_v[1] = 0;
	dd_rot_v[2] = 0;
	double dd_rot_a = 0;

	// Move forward
	if (keys[SDLK_SPACE]) { // Spacebar 32
		k->dd_pos[0] += v * k->rot->m[0][0];
		k->dd_pos[1] += v * k->rot->m[0][1];
		k->dd_pos[2] += v * k->rot->m[0][2];
	}

	// Move backward
	if (keys[SDLK_LSHIFT]) { // Left shift 304
		k->dd_pos[0] -= v * k->rot->m[0][0];
		k->dd_pos[1] -= v * k->rot->m[0][1];
		k->dd_pos[2] -= v * k->rot->m[0][2];
	}
	
	// Strafe right
	if (keys[SDLK_RIGHT]) { // Right arrow 275
		k->dd_pos[0] += v * k->rot->m[1][0];
		k->dd_pos[1] += v * k->rot->m[1][1];
		k->dd_pos[2] += v * k->rot->m[1][2];
	}

	// Strafe left
	if (keys[SDLK_LEFT]) { // Left arrow 276
		k->dd_pos[0] -= v * k->rot->m[1][0];
		k->dd_pos[1] -= v * k->rot->m[1][1];
		k->dd_pos[2] -= v * k->rot->m[1][2];
	}
	
	// Strafe down
	if (keys[SDLK_DOWN]) { // Down arrow 274
		k->dd_pos[0] += v * k->rot->m[2][0];
		k->dd_pos[1] += v * k->rot->m[2][1];
		k->dd_pos[2] += v * k->rot->m[2][2];
	}

	// Strafe up
	if (keys[SDLK_UP]) { // Up arrow 273
		k->dd_pos[0] -= v * k->rot->m[2][0];
		k->dd_pos[1] -= v * k->rot->m[2][1];
		k->dd_pos[2] -= v * k->rot->m[2][2];
	}
	
	
	
	// Roll right e
	if (keys[SDLK_e]) {
		dd_rot_v[0] = k->rot->m[0][0];
		dd_rot_v[1] = k->rot->m[0][1];
		dd_rot_v[2] = k->rot->m[0][2];
		dd_rot_a = w;
	}
	
	// Roll left q
	if (keys[SDLK_q]) {
		dd_rot_v[0] = k->rot->m[0][0];
		dd_rot_v[1] = k->rot->m[0][1];
		dd_rot_v[2] = k->rot->m[0][2];
		dd_rot_a = -w;
	}
	
	// Pitch up s
	if (keys[SDLK_s]) {
		dd_rot_v[0] = k->rot->m[1][0];
		dd_rot_v[1] = k->rot->m[1][1];
		dd_rot_v[2] = k->rot->m[1][2];
		dd_rot_a = w;
	}

	// Pitch down w
	if (keys[SDLK_w]) {
		dd_rot_v[0] = k->rot->m[1][0];
		dd_rot_v[1] = k->rot->m[1][1];
		dd_rot_v[2] = k->rot->m[1][2];
		dd_rot_a = -w;
	}
	
	// Yaw right d
	if (keys[SDLK_d]) {
		dd_rot_v[0] = k->rot->m[2][0];
		dd_rot_v[1] = k->rot->m[2][1];
		dd_rot_v[2] = k->rot->m[2][2];
		dd_rot_a = w;
	}
	
	// Yaw left a
	if (keys[SDLK_a]) {
		dd_rot_v[0] = k->rot->m[2][0];
		dd_rot_v[1] = k->rot->m[2][1];
		dd_rot_v[2] = k->rot->m[2][2];
		dd_rot_a = -w;
	}
	
	matrix_make_rot_aa(k->dd_rot, dd_rot_v[0], dd_rot_v[1], dd_rot_v[2], dd_rot_a);
	
	//debug_w("%lf", dd_rot_a *M_PI/180);
	//matrix_print(k->dd_rot);
	//*/
	
	/*
	aircraft_fields *f = (aircraft_fields *) usrctl_node->n.o->f;
	
	f->thrust = 1;
	f->pitch_ctrl = 0;
	f->yaw_ctrl = 0;
	f->roll_ctrl = 0;
	
	// Pitch up s
	if (keys[SDLK_s]) {
		f->pitch_ctrl = .2;
	}

	// Pitch down w
	if (keys[SDLK_w]) {
		f->pitch_ctrl = -.2;
	}
	
	// Yaw right e
	if (keys[SDLK_e]) {
		f->yaw_ctrl = .2;
	}
	
	// Yaw left q
	if (keys[SDLK_q]) {
		f->yaw_ctrl = -.2;
	}
	
	// Roll right d
	if (keys[SDLK_d]) {
		f->roll_ctrl = .2;
	}
	
	// Roll left a
	if (keys[SDLK_a]) {
		f->roll_ctrl = -.2;
	}
	
	
	printf("\
Pitch control:  %d%\n\
Yaw control:    %d%\n\
Roll control:   %d%\n\
Airspeed:       %d m/s\n\
Altitude:       %d m\n\
Vertical speed: %d m/s\n\
	        \n",
	        //(int) f->thrust * 100 / f->thrust_max,
	        (int) (f->pitch_ctrl * 100),
	        (int) (f->yaw_ctrl * 100),
	        (int) (f->roll_ctrl * 100),
	        (int) aircraft_airspeed(f),
	        (int) (-1 * f->pos[2]),
	        (int) f->vertspeed
	        );

*/
}

/*
void aircraft_get_kinematics(node *a) {

	obj_kinematics *k = a->parent->n.k;
	aircraft_fields *f = (aircraft_fields *) a->n.o->f;
	
	f->pos[0] = k->pos[0];
	f->pos[1] = k->pos[1];
	f->pos[2] = k->pos[2];
	
	f->d_pos[0] = dot(k->d_pos, k->rot->m[0]);
	f->d_pos[1] = dot(k->d_pos, k->rot->m[1]);
	f->d_pos[2] = dot(k->d_pos, k->rot->m[2]);
	
	f->dd_pos[0] = dot(k->dd_pos, k->rot->m[0]);
	f->dd_pos[1] = dot(k->dd_pos, k->rot->m[1]);
	f->dd_pos[2] = dot(k->dd_pos, k->rot->m[2]);
	
	f->rot[2] = atan2(k->rot->m[0][1], k->rot->m[0][0]);
	f->rot[1] = asin(k->rot->m[0][2]);
	f->rot[0] = atan2(k->rot->m[1][2], k->rot->m[2][2]);
	
	f->d_rot[2] = atan2(k->d_rot->m[0][1], k->d_rot->m[0][0]);
	f->d_rot[1] = asin(-k->d_rot->m[0][2]);
	f->d_rot[0] = atan2(k->d_rot->m[1][2], k->d_rot->m[2][2]);
	
	f->dd_rot[2] = atan2(k->dd_rot->m[0][1], k->dd_rot->m[0][0]);
	f->dd_rot[1] = asin(-k->dd_rot->m[0][2]);
	f->dd_rot[0] = atan2(k->dd_rot->m[1][2], k->dd_rot->m[2][2]);
	
	f->airspeed = aircraft_airspeed(f);
	f->vertspeed = -1 * k->d_pos[2];
	
	//debug_w("%lf %lf %lf", f->pos[0], f->pos[1], f->pos[2]);
	//debug_w("%lf %lf %lf", f->d_pos[0], f->d_pos[1], f->d_pos[2]);
	//debug_w("%lf %lf %lf", f->dd_pos[0], f->dd_pos[1], f->dd_pos[2]);
	//debug_w("%lf %lf %lf", f->rot[0], f->rot[1], f->rot[2]);
	//debug_w("%lf %lf %lf", f->d_rot[0], f->d_rot[1], f->d_rot[2]);
	//debug_w("%lf %lf %lf", f->dd_rot[0], f->dd_rot[1], f->dd_rot[2]);
	
	
}
*/

void aircraft_update(node *n) {
	/*

	//debug_n("Updating aircraft fields");
	aircraft_get_kinematics(n);
	aircraft_fields *f = (aircraft_fields *) n->n.o->f;
	obj_kinematics *k = n->parent->n.k;
	
	
	double l = aircraft_lift(f);
	double d = aircraft_drag(f);
	double g = aircraft_gravity(f);
	double t = aircraft_thrust(f);
	double a = aircraft_airspeed(f);
	if (a == 0) a = 1; // to prevent division by zero
	
	debug_w("%lf, %lf, %lf, %lf, %lf", l, d, g, t, a);
	
	debug_w("%lf. %lf, %lf", f->d_pos[0], f->d_pos[1], -f->d_pos[2]);
	debug_w("%lf. %lf, %lf", f->dd_pos[0], f->dd_pos[1], -f->dd_pos[2]);
	
	double theta = atan2(-f->d_pos[0], f->d_pos[2]); // used for lift
	
	//debug_w("%lf", cos(theta)*((f->d_pos[0] / a) * d) + sin(theta)*((f->d_pos[2] / a) * d));
	
	double acc_x = (t + cos(theta) * l - (f->d_pos[0] / a) * d) / f->mass;
	double acc_y = -(f->d_pos[1] / a) * d / f->mass;
	double acc_z = (-l + sin(theta) * l - (f->d_pos[2] / a) * d) / f->mass;
	// Gravity gets applied later, when it is more convenient (after switching from the plane's to the world's reference frame)
	
	//debug_w("(%lf + %lf - %lf) / %lf = %lf", t, cos(theta)*l, (f->d_pos[0] / a) * d, f->mass, acc_x);
	
	//debug_w("%lf, %lf, %lf", acc_x, acc_y, acc_z);
	
	// Update acceleration fields in obj_kinematics
	k->dd_pos[0] = acc_x * k->rot->m[2][2] + acc_y * k->rot->m[2][1] + acc_z * k->rot->m[2][0];
	k->dd_pos[1] = acc_x * k->rot->m[1][2] + acc_y * k->rot->m[1][1] + acc_z * k->rot->m[1][0];
	k->dd_pos[2] = acc_x * k->rot->m[0][2] + acc_y * k->rot->m[0][1] + acc_z * k->rot->m[0][0] + g/f->mass;
	
	//debug_w("%lf, %lf, %lf", k->dd_pos[0], k->dd_pos[1], k->dd_pos[2]);
	
	//raise(SIGABRT);
	*/
	
}





/*
double aircraft_airspeed_squared(aircraft_fields *f) {
	return SQR(f->d_pos[0]) + SQR(f->d_pos[1]) + SQR(f->d_pos[2]);
}

double aircraft_airspeed(aircraft_fields *f) {
	return sqrt(aircraft_airspeed_squared(f));
}

double aircraft_lift(aircraft_fields *f) {
	return 0.5 * env_get_air_density(f->pos[0], f->pos[1], f->pos[2])
	       * f->area * aircraft_lift_coeff(f) * aircraft_airspeed_squared(f);
}

double aircraft_lift_coeff(aircraft_fields *f) {
	// need to take angle of attack into account
	return f->lc_0;
}

double aircraft_drag(aircraft_fields *f) {
	return 0.5 * env_get_air_density(f->pos[0], f->pos[1], f->pos[2])
	       * f->area * aircraft_drag_coeff(f) * aircraft_airspeed_squared(f);
}

double aircraft_drag_coeff(aircraft_fields *f) {
	// need to take angle of attack into account
	return f->dc_0;
}

double aircraft_gravity(aircraft_fields *f) {
	return f->mass * env_get_grav_accel(f->pos[0], f->pos[1], f->pos[2]);
}

double aircraft_thrust(aircraft_fields *f) {
	return f->thrust * f->thrust_max;
}
*/
