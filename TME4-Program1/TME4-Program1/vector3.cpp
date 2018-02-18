#include <math.h>

#include "vector3.h"



vector3 vector3 :: normalize() {

	float length = sqrt( (x * x) + (y * y) + (z * z) );

	if ( (length > -0.01) && (length < 0.01) )

		return vector3(0.0, 0.0, 0.0);

	else

		return vector3( (x / length), (y / length), (z / length) );	

}



vector3 vector3 :: add(vector3 v) {

	return vector3(x + v.x, y + v.y, z + v.z);

}



vector3 vector3 :: subtract(vector3 v) {

	return vector3(x - v.x, y - v.y, z - v.z);

}



vector3 vector3 :: scalar(float f) {

	return vector3(x * f, y * f, z * f);

}



float vector3 :: dot(vector3 v) {

	return ( (x * v.x) + (y * v.y) + (z * v.z) );

}



vector3 vector3 :: cross(vector3 v) {

	float x1 = (y * v.z) - (z * v.y);

	float y1 = (z * v.x) - (x * v.z);

	float z1 = (x * v.y) - (y * v.x);



	return vector3(x1, y1, z1);

}



vector3 vector3 :: reflect(vector3 norm) {

	// u = v - 2 * |Inc * Norm| * Norm

	vector3 n_inc    = normalize();

	float   term1    = 2 * n_inc.dot(norm);

	vector3 term2    = norm.scalar(term1);

	

	return vector3(n_inc.subtract(term2));

}



float vector3 :: distance(vector3 v) {

	float dx = v.x - x;

	float dy = v.y - y;

	float dz = v.z - z;

	return sqrt((dx * dx) + (dy * dy) + (dz * dz));

}