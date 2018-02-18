#include <iostream>

#include <math.h>

#include "plane.h"



using namespace std;



vector3 plane :: intersect(vector3 v1, vector3 v2) {

	// find parametric form

	float dx = v1.x;

	float dy = v1.y;

	float dz = v1.z;



	float tx = (v2.x - v1.x);

	float ty = (v2.y - v1.y);

	float tz = (v2.z - v1.z);



	// resolve t

	float constant = (a * dx) + (b * dy) + (c * dz);

	float tcoef = (a * tx) + (b * ty) + (c * tz);

	float t     = (-d - constant) / tcoef;



	// resolve

	float x_int = dx + (tx * t);

	float y_int = dy + (ty * t);

	float z_int = dz + (tz * t);



	return vector3(x_int, y_int, z_int);

}



void plane :: setP1 (vector3 v) {

	p1x = v.x; p1y = v.y; p1z = v.z;

}



void plane :: setP2 (vector3 v) {

	p2x = v.x; p2y = v.y; p2z = v.z;

}



void plane :: setP3 (vector3 v) {

	p3x = v.x; p3y = v.y; p3z = v.z;

}



void plane :: setP4 (vector3 v) {

	p4x = v.x; p4y = v.y; p4z = v.z;

}



vector3 plane :: getP1() {

	return vector3(p1x, p1y, p1z);

}



vector3 plane :: getP2() {

	return vector3(p2x, p2y, p2z);

}



vector3 plane :: getP3() {

	return vector3(p3x, p3y, p3z);

}



vector3 plane :: getP4() {

	return vector3(p4x, p4y, p4z);

}