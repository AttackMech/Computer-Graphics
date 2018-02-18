#ifndef _VECTOR3_H_
#define _VECTOR3_H_

class vector3 {

public: 

	// constructors

	vector3();

	vector3(float x1, float y1, float z1): x(x1), y(y1), z(z1) {}



	// methods - vector

	vector3 normalize();

	vector3 add(vector3 v);

	vector3 subtract(vector3 v);

	vector3 scalar(float f);

	float dot(vector3 v);

	vector3 cross(vector3 v);

	vector3 reflect(vector3 norm);



	// method - geometry

	float distance(vector3 v);



	// data elements

	float x;

	float y;

	float z;

};

class vector4 {

	public: 

		// constructors
		vector4();

		vector4(float r1, float g1, float b1, float a1): r(r1), g(g1), b(b1), a(a1) {}


		// data elements
		float r;

		float g;

		float b;

		float a;

};

#endif  // _VECTOR3_H_
