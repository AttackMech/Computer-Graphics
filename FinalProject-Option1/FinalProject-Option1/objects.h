#ifndef _OBJECTS_H_

#define _OBJECTS_H_



#include "gl/glut.h"



class objects {

private:

	GLuint sphere, cylinder, arm;
	
	float radius, stepRad, stepDeg;
	
	float uCircle[22][3];
	
	float uCylinder[42][3];
	
	void drawCircle();
	
	void drawSquare();
	
	void drawCube();
	
	void drawCylinder();
	
	void drawLimb(int base, int extend, int appendage);
	
	void drawBody(int bottom, int belt, int torso, int head);
	
	void drawGun();

public:

	objects();
	
	void drawCop();

	void drawCopCar();

	void drawRobber1();

	void drawRobber2();

	void drawBank();

};


#endif  // _OBJECTS_H_
