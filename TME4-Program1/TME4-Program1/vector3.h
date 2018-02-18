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