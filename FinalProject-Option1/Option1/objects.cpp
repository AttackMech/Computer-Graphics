/*	Athabasca University

	Comp390 - Introduction to Computer Graphics

	Final Project Option 1


	@author: Jason Bishop

	@student#: 3042012

	@date: May 16, 2015


	Purpose:  The purpose of the class "objects" defined here is to create a series of basic 2D and 3D
		shapes that can be geometrically transformed to represent real world objects placed into a scene.

	Routines:

		objects - Initializes variables needed to make a circle and cylinder

		drawCircle - Draws a circle, radius of 1, centered at the origin in the xy plane.  The circle is
			made up of 20 individual triangle slices.

		drawSquare - Draws a unit square in the xy plane, centered at the origin.

		drawCube - Draws a series of squares to form a unit cube with the bottom face as the square above.

		drawCylinder - Draws a cylinder of height 1, radius 1, by connecting 2 of the circles above with
			a series of rectangles.

		drawLimb - Draws a small and large cylinder side by side to represent a limb, such as an arm, and
			places a sphere at the end of the longer cylinder to act as an appendage, such as a hand.

		drawBody - Draws 3 cylinders of different sizes, stacked on top of one another to represent a
			lower body, waist, and torso.  A sphere is placed on top to represent the head.

		drawGun - Transforms a series of cubes to represent a gun.  1 for the barrel, 1 for the handle, and
			3 small cubes for the sights.

		drawCop - Positions the body and limbs above into a shape representing a person standing with their
			gun drawn and pointed in front of them.

		drawCopCar - Uses a series of cubes, rectangles and triangles to simulate the body of a police car
			with lights on top.  The wheels are represented with cylinders.

		drawRobber1 - Arranges the body parts mentioned above to represent a man holding his hands in the
			air.  A gun is placed in front of this figure, as if it is dropped on the ground.

		drawRobber2 - Arranges the body parts mentioned above to represent a person lying dead in an
			awkward position.  2 red circles are positioned near the body to represent a blood stain, and
			a sphere is placed near the body to represent a shoe that came off.

		drawBank - Uses a series of cubes, rectangles, triangles, and cylinders to represent a rectangular
			building with a triangular roof and columns along the front face.  The idea is to represent a
			bank.


*/



#include "objects.h"

#include "gl/glut.h"

#include "material_constants.h"

#include <math.h>



#define PI 3.14159265

#define SLICES 20



objects::objects() {

	// set initial circle values

	radius = 1.0;

	stepRad = (2 * PI) / SLICES;

	stepDeg = 360.0 / SLICES;

	
	// unit circle initial points
	
	uCircle [0][0] = 0.0;
	
	uCircle [0][1] = 0.0;
	
	uCircle [0][2] = 0.0;

	
	// set points for circles and cylinders

	for (int i = 0; i <= SLICES; ++i) {
		
		uCircle[i+1][0] = radius * cosf(stepRad * i);
		
		uCircle[i+1][1] = 0.0;
		
		uCircle[i+1][2] = radius * sinf(stepRad * i);
		
		
		uCylinder[2*i][0] = uCircle[i+1][0];
		
		uCylinder[2*i][1] = uCircle[i+1][1];
		
		uCylinder[2*i][2] = uCircle[i+1][2];

		
		uCylinder[2*i+1][0] = uCircle[i+1][0];
		
		uCylinder[2*i+1][1] = uCircle[i+1][1] + radius;
		
		uCylinder[2*i+1][2] = uCircle[i+1][2];

	}
		
}



// draw a circle

void objects::drawCircle() {

	glBegin(GL_TRIANGLE_FAN);
		
		for(int i = 0; i < SLICES + 2; i++) {

			glVertex3fv(uCircle[i]);

		}

	glEnd();
}



// draw a unit square

void objects::drawSquare() {

	glBegin(GL_QUADS);
	
		glVertex3f(-0.5, 0.0, 0.5);

		glVertex3f(0.5, 0.0, 0.5);

		glVertex3f(0.5, 0.0, -0.5);

		glVertex3f(-0.5, 0.0, -0.5);
	
	glEnd();

}



// draw a unit cube

void objects::drawCube() {
	
	glMatrixMode(GL_MODELVIEW);

	drawSquare();
	
	
	glPushMatrix();
		
		glTranslatef(0.0, 1.0, 0.0);
		
		drawSquare();
	
	glPopMatrix();
	
	glPushMatrix();
		
		glTranslatef(0.5, 0.5, 0.0);
		
		glRotatef(90.0, 0.0, 0.0, 1.0);
		
		drawSquare();

	glPopMatrix();
	
	glPushMatrix();
		
		glTranslatef(-0.5, 0.5, 0.0);
		
		glRotatef(90.0, 0.0, 0.0, 1.0);
		
		drawSquare();

	glPopMatrix();
	
	glPushMatrix();
		
		glTranslatef(0.0, 0.5, 0.5);
		
		glRotatef(90.0, 1.0, 0.0, 0.0);
		
		drawSquare();

	glPopMatrix();
	
	glPushMatrix();
		
		glTranslatef(0.0, 0.5, -0.5);
		
		glRotatef(90.0, 1.0, 0.0, 0.0);
		
		drawSquare();

	glPopMatrix();

}



// draw a unit cylinder

void objects::drawCylinder() {

	glMatrixMode(GL_MODELVIEW);

	drawCircle();
	
	glPushMatrix();
		
		glTranslatef(0.0, radius, 0.0);
		
		drawCircle();

	glPopMatrix();
	
	glBegin(GL_QUADS);
		
		for(int i = 0; i < SLICES; ++i) {
		
			glVertex3fv(uCylinder[2*i+2]);
			
			glVertex3fv(uCylinder[2*i+3]);
			
			glVertex3fv(uCylinder[2*i+1]);
			
			glVertex3fv(uCylinder[2*i]);

		}

	glEnd();

}



// draw a limb of 2 cylinders for the arm/leg, a sphere for the hand/foot

void objects::drawLimb(int base, int forelimb, int appendage) {

	glMatrixMode(GL_MODELVIEW);

	
	setMaterial(base);
	
	glPushMatrix();
		
		glScalef(0.5, 0.5, 0.5);
		
		drawCylinder();

	glPopMatrix();
	
	
	setMaterial(forelimb);
	
	glPushMatrix();
		
		glTranslatef(0.0, 0.5, 0.0);
		
		glScalef(0.5, 1.5, 0.5);
		
		drawCylinder();

	glPopMatrix();
	
	
	setMaterial(appendage);
	
	glPushMatrix();
		
		glTranslatef(0.0, 2.5, 0.0);
		
		glutSolidSphere(0.5, 20, 20);

	glPopMatrix();

}



// draw a body consisting of 3 cylinders for the trunk, and a sphere for the head

void objects::drawBody(int bottom, int belt, int torso, int head) {
	
	glMatrixMode(GL_MODELVIEW);
	
	setMaterial(bottom);
	
	glPushMatrix();
		
		glScalef(1.0, 0.4, 1.0);
		
		drawCylinder();

	glPopMatrix();


	setMaterial(belt);
	
	glPushMatrix();
	
		glTranslatef(0.0, 0.4, 0.0);
	
		glScalef(1.0, 0.1, 1.0);
		
		drawCylinder();
		
	glPopMatrix();


	setMaterial(torso);
	
	glPushMatrix();
		
		glTranslatef(0.0, 0.5, .0);
		
		glScalef(1.0, 1.5, 1.0);
		
		drawCylinder();

	glPopMatrix();


	setMaterial(head);
	
	glPushMatrix();
		
		glTranslatef(0.0, 3.0, 0.0);
		
		glutSolidSphere(1.0, 20, 20);
	
	glPopMatrix();

}



// draw a gun made of cubes and a circle

void objects::drawGun() {

	glMatrixMode(GL_MODELVIEW);

	
	// barrel

	setMaterial(1);

	glPushMatrix();
		
		glScalef(3.0, 1.0, 1.0);
		
		drawCube();
	
	glPopMatrix();
	

	// handle
	
	glPushMatrix();
		
		glTranslatef(1.0, -1.0, 0.0);
		
		drawCube();
	
	glPopMatrix();
	
	
	// sights
	
	glPushMatrix();
	
		glTranslatef(1.0, 1.0, 0.25);
	
		glScalef(0.25, 0.25, 0.25);
		
		drawCube();

	glPopMatrix();

	glPushMatrix();

		glTranslatef(1.0, 1.0, -0.25);
		
		glScalef(0.25, 0.25, 0.25);
		
		drawCube();

	glPopMatrix();

	glPushMatrix();
		
		glTranslatef(-1.25, 1.0, 0.0);
		
		glScalef(0.25, 0.25, 0.25);
		
		drawCube();

	glPopMatrix();


	// inside barrel
	
	setMaterial(0);
	
	glPushMatrix();
	
		glTranslatef(-1.01, 0.25, 0.0);
	
		glRotatef(90.0, 0.0, 1.0, 0.0);
		
		glRotatef(90.0, 1.0, 0.0, 0.0);
		
		glScalef(0.5, 1.0, 0.5);
		
		drawCircle();

	glPopMatrix();

}



// draw a police officer pointing a gun using body part routines above

void objects::drawCop() {
	
	glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix();
	
		glTranslatef(0.0, 3.0, 0.0);
	
		drawBody(8, 12, 7, 4);


		// arms
		
		glPushMatrix();
			
			glTranslatef(1.0, 1.5, 0.0);
			
			glRotatef(-90.0, 0.0, 1.0, 0.0);
			
			glRotatef(-90.0, 0.0, 0.0, 1.0);
			
			drawLimb(7, 4, 4);

		glPopMatrix();

		glPushMatrix();
			
			glTranslatef(-1.0, 1.9, 0.0);
			
			glRotatef(-150.0, 1.0, 0.0, 0.0); //chg x --> z
			
			drawLimb(7, 4, 4);

		glPopMatrix();


		// legs

		glPushMatrix();
			
			glTranslatef(-0.5, 0.0, 0.0);
			
			glRotatef(160.0, 1.0, 0.0, 0.0);
			
			drawLimb(8, 8, 1);

		glPopMatrix();

		glPushMatrix();
			
			glTranslatef(0.5, 0.0, 0.0);
			
			glRotatef(-160.0, 1.0, 0.0, 0.0);
			
			drawLimb(8, 8, 1);

		glPopMatrix();


		// gun
		
		glPushMatrix();
		
			glTranslatef(1.0, 2.0, 3.0);
			
			glRotatef(90.0, 0.0, 1.0, 0.0);
			
			glScalef(0.5, 0.5, 0.5);
			
			drawGun();

		glPopMatrix();

	glPopMatrix();

}



// draw a police car with cubes, rectangles and triangles

void objects::drawCopCar(){
	
	glMatrixMode(GL_MODELVIEW);
	
	
	glPushMatrix();
	
		glTranslatef(0.0, 1.0, 0.0);
	
	
		// draw lower body
	
		setMaterial(2);
		
		glPushMatrix();
		
			glScalef(5.0, 2.0, 8.0);
			
			drawCube();

		glPopMatrix();

		glBegin(GL_QUADS);
			
			glVertex3f(-2.5, 0.0, 4.0);
			
			glVertex3f(-2.5, 0.0, 6.0);
			
			glVertex3f(2.5, 0.0, 6.0);
			
			glVertex3f(2.5, 0.0, 4.0);


			glVertex3f(-2.5, 0.0, 6.0);
			
			glVertex3f(2.5, 0.0, 6.0);
			
			glVertex3f(2.5, 1.0, 6.0);
			
			glVertex3f(-2.5, 1.0, 6.0);


			glVertex3f(-2.5, 1.0, 6.0);
			
			glVertex3f(2.5, 1.0, 6.0);
			
			glVertex3f(2.5, 2.0, 4.0);
			
			glVertex3f(-2.5, 2.0, 4.0);

			
			glVertex3f(-2.5, 0.0, 4.0);
			
			glVertex3f(-2.5, 0.0, 6.0);
			
			glVertex3f(-2.5, 1.0, 6.0);
			
			glVertex3f(-2.5, 2.0, 4.0);

			
			glVertex3f(2.5, 0.0, 4.0);
			
			glVertex3f(2.5, 2.0, 4.0);
			
			glVertex3f(2.5, 1.0, 6.0);
			
			glVertex3f(2.5, 0.0, 6.0);
		
		glEnd();
	

		// draw upper body
		
		setMaterial(1);
		
		glPushMatrix();
		
			glTranslatef(0.0, 2.0, 0.0);
			
			glScalef(5.0, 2.0, 5.0);
			
			drawCube();

		glPopMatrix();


		// draw lights
		
		setMaterial(10);  // red
		
		glPushMatrix();
		
			glTranslatef(1.25, 4.0, 0.0);
			
			glScalef(2.5, 1.0, 1.0);
			
			drawCube();

		glPopMatrix();


		setMaterial(9);  // blue

		glPushMatrix();
		
			glTranslatef(-1.25, 4.0, 0.0);
			
			glScalef(2.5, 1.0, 1.0);
			
			drawCube();

		glPopMatrix();


		// draw windshields
		
		setMaterial(6);
		
		glBegin(GL_QUADS);
		
			glVertex3f(-2.5, 2.0, 4.0);
			
			glVertex3f(2.5, 2.0, 4.0);
			
			glVertex3f(2.5, 4.0, 2.5);
			
			glVertex3f(-2.5, 4.0, 2.5);

			
			glVertex3f(-2.5, 2.0, -3.5);
			
			glVertex3f(2.5, 2.0, -3.5);
			
			glVertex3f(2.5, 4.0, -2.5);
			
			glVertex3f(-2.5, 4.0, -2.5);

		glEnd();

		glBegin(GL_TRIANGLES);

			glVertex3f(-2.5, 2.0, 4.0);
			
			glVertex3f(-2.5, 4.0, 2.5);
			
			glVertex3f(-2.5, 2.0, 2.5);


			glVertex3f(2.5, 2.0, 4.0);
			
			glVertex3f(2.5, 4.0, 2.5);
			
			glVertex3f(2.5, 2.0, 2.5);


			glVertex3f(-2.5, 2.0, -3.5);
			
			glVertex3f(-2.5, 2.0, -2.5);
			
			glVertex3f(-2.5, 4.0, -2.5);

			
			glVertex3f(2.5, 2.0, -3.5);
			
			glVertex3f(2.5, 2.0, -2.5);
			
			glVertex3f(2.5, 4.0, -2.5);

		glEnd();
	

		// draw windows
		
		//glPushMatrix();
	
			glPushMatrix();
		
				glTranslatef(-2.51, 2.75, 1.25);
				
				glRotatef(90.0, 0.0, 1.0, 0.0);
				
				glRotatef(90.0, 1.0, 0.0, 0.0);
				
				glScalef(1.5, 1.0, 1.25);
				
				drawSquare();

			glPopMatrix();

			glPushMatrix();
				
				glTranslatef(-2.51, 2.75, -1.25);
				
				glRotatef(90.0, 0.0, 1.0, 0.0);
				
				glRotatef(90.0, 1.0, 0.0, 0.0);
				
				glScalef(1.5, 1.0, 1.25);
				
				drawSquare();

				
				glRotatef(180.0, 0.0, 1.0, 0.0);
				
				drawSquare();

			glPopMatrix();

			glRotatef(180.0, 0.0, 1.0, 0.0);

			glPushMatrix();
			
				glTranslatef(-2.51, 2.75, 1.25);
				
				glRotatef(90.0, 0.0, 1.0, 0.0);
				
				glRotatef(90.0, 1.0, 0.0, 0.0);
				
				glScalef(1.5, 1.0, 1.25);
				
				drawSquare();

			glPopMatrix();

			glPushMatrix();

				glTranslatef(-2.51, 2.75, -1.25);
			
				glRotatef(90.0, 0.0, 1.0, 0.0);
				
				glRotatef(90.0, 1.0, 0.0, 0.0);
				
				glScalef(1.5, 1.0, 1.25);
				
				drawSquare();
				
				glRotatef(180.0, 0.0, 1.0, 0.0);
				
				drawSquare();

			glPopMatrix();

		//glPopMatrix();


		// draw wheels

		setMaterial(0);
		
		glPushMatrix();
		
			glTranslatef(-2.5, 0.0, 4.0);
			
			glRotatef(90.0, 0.0, 0.0, 1.0);
			
			glScalef(1.0, 0.5, 1.0);
			
			drawCylinder();

		glPopMatrix();

		glPushMatrix();
			
			glTranslatef(2.5, 0.0, 4.0);
			
			glRotatef(-90.0, 0.0, 0.0, 1.0);
			
			glScalef(1.0, 0.5, 1.0);
			
			drawCylinder();
		
		glPopMatrix();

		glPushMatrix();
		
			glTranslatef(-2.5, 0.0, -2.5);
			
			glRotatef(90.0, 0.0, 0.0, 1.0);
			
			glScalef(1.0, 0.5, 1.0);
			
			drawCylinder();

		glPopMatrix();

		glPushMatrix();
			
			glTranslatef(2.5, 0.0, -2.5);
			
			glRotatef(-90.0, 0.0, 0.0, 1.0);
			
			glScalef(1.0, 0.5, 1.0);
			
			drawCylinder();

		glPopMatrix();

	glPopMatrix();

}



// draw a robber with hands raised using the body parts routines above

void objects::drawRobber1(){
	
	glPushMatrix();
		
		glTranslatef(0.0, 3.0, 0.0);
		
		drawBody(0, 0, 0, 4);

		//arms
		
		glPushMatrix();
			
			glTranslatef(1.0, 1.5, 0.0);
			
			glRotatef(-20.0, 0.0, 0.0, 1.0);
			
			drawLimb(0, 0, 4);

		glPopMatrix();

		glPushMatrix();
			
			glTranslatef(-1.0, 1.5, 0.0);
			
			glRotatef(20.0, 0.0, 0.0, 1.0);
			
			drawLimb(0, 0, 4);

		glPopMatrix();


		//legs
		
		glPushMatrix();
		
			glTranslatef(-0.5, 0.0, 0.0);
			
			glRotatef(180.0, 1.0, 0.0, 0.0);
			
			drawLimb(0, 0, 0);

		glPopMatrix();

		glPushMatrix();
			
			glTranslatef(0.5, 0.0, 0.0);
			
			glRotatef(180.0, 1.0, 0.0, 0.0);
			
			drawLimb(0, 0, 0);

		glPopMatrix();

	glPopMatrix();


	// gun
	
	glPushMatrix();
	
		glTranslatef(0.0, 0.0, 3.0);
	
		glRotatef(45.0, 0.0, 1.0, 0.0);
		
		glRotatef(90.0, 1.0, 0.0, 0.0);
		
		glScalef(0.5, 0.5, 0.5);
		
		drawGun();

	glPopMatrix();

}



// draw a dead robber with blood using the body part routines above

void objects::drawRobber2() {
	
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
		
		glTranslatef(0.0, 1.0, 0.0);
		
		glRotatef(90.0, 1.0, 0.0, 0.0);
		
		drawBody(0, 0, 0, 5);

		
		//arms
		
		glPushMatrix();
		
			glTranslatef(0.8, 1.6, 0.0);
			
			glRotatef(-140.0, 0.0, 0.0, 1.0);
			
			drawLimb(0, 0, 5);

		glPopMatrix();

		glPushMatrix();
			
			glTranslatef(-0.8, 1.5, 0.0);
			
			glRotatef(40.0, 0.0, 0.0, 1.0);
			
			drawLimb(0, 0, 5);

		glPopMatrix();


		//legs
		
		glPushMatrix();
		
			glTranslatef(-0.5, 0.0, 0.0);
			
			glRotatef(180.0, 1.0, 0.0, 0.0);
			
			drawLimb(0, 0, 0);

		glPopMatrix();

		glPushMatrix();
			
			glTranslatef(0.5, 0.0, 0.0);
			
			glRotatef(40.0, 0.0, 0.0, 1.0);
			
			glRotatef(180.0, 1.0, 0.0, 0.0);
			
			drawLimb(0, 0, 5);

		glPopMatrix();

	glPopMatrix();

	
	// draw a missing shoe

	setMaterial(1);
	
	glPushMatrix();
	
		glTranslatef(3.0, 0.5, -5.0);
	
		glutSolidSphere(0.5, 20, 20);

	glPopMatrix();
		

	// draw a blood stain

	setMaterial(13);
	
	glPushMatrix();
	
		glTranslatef(1.0, 0.01, 2.5);
	
		drawCircle();

		glPushMatrix();
		
			glTranslatef(0.5, 0.00, 1.0);
			
			glScalef(1.0, 0.0, 0.5);
			
			drawCircle();

		glPopMatrix();

	glPopMatrix();

}



// draw a bank building with cylinders, triangles, squares and cubes

void objects::drawBank() {

	glMatrixMode(GL_MODELVIEW);

	
	//draw main building

	setMaterial(3);
	
	glPushMatrix();
	
		glScalef(20.0, 10.0, 20.0);
	
		drawCube();

	glPopMatrix();

	
	// draw steps

	setMaterial(15);

	glPushMatrix();
	
		glTranslatef(0.0, 0.0, 11.5);
	
		glScalef(20.0, 3.0, 3.0);
		
		drawCube();

		glPushMatrix();

			glTranslatef(0.0, 0.0, 0.66);
			
			glScalef(1.0, 0.66, 0.33);
			
			drawCube();
			
			glPushMatrix();
			
				glTranslatef(0.0, 0.0, 1.0);
				
				glScalef(1.0, 0.5, 1.0);
				
				drawCube();

			glPopMatrix();

		glPopMatrix();

	glPopMatrix();
	

	// draw columns

	setMaterial(3);

	glPushMatrix();
	
		glTranslatef(-9.0, 3.0, 12.0);
	
		glScalef(0.5, 7.0, 0.5);
		
		drawCylinder();

		glPushMatrix();

			glTranslatef(4.0, 0.0, 0.0);
			
			drawCylinder();

		glPopMatrix();

		glPushMatrix();
			
			glTranslatef(8.0, 0.0, 0.0);
			
			drawCylinder();

		glPopMatrix();

		glPushMatrix();
			
			glTranslatef(28.0, 0.0, 0.0);
			
			drawCylinder();

		glPopMatrix();

		glPushMatrix();
			
			glTranslatef(32.0, 0.0, 0.0);
			
			drawCylinder();

		glPopMatrix();

		glPushMatrix();
			
			glTranslatef(36.0, 0.0, 0.0);
			
			drawCylinder();

		glPopMatrix();

	glPopMatrix();

		
	// draw roof
	
	setMaterial(15);

	glBegin(GL_QUAD_STRIP);
	
		glVertex3f(-10.0, 10.0, -10.0);
	
		glVertex3f(-10.0, 10.0, 13.0);
		
		glVertex3f(10.0, 10.0, -10.0);
		
		glVertex3f(10.0, 10.0, 13.0);
		
		glVertex3f(0.0, 15.0, -10.0);
		
		glVertex3f(0.0, 15.0, 13.0);
		
		glVertex3f(-10.0, 10.0, -10.0);
		
		glVertex3f(-10.0, 10.0, 13.0);

	glEnd();

	glBegin(GL_TRIANGLES);
		
		glVertex3f(-10.0, 10.0, 13.0);
		
		glVertex3f(10.0, 10.0, 13.0);
		
		glVertex3f(0.0, 15.0, 13.0);
		
		glVertex3f(-10.0, 10.0, -10.0);
		
		glVertex3f(10.0, 10.0, -10.0);
		
		glVertex3f(0.0, 15.0, -10.0);

	glEnd();

	setMaterial(3);

	glBegin(GL_TRIANGLES);

		glVertex3f(-8.0, 11.0, 13.01);
		
		glVertex3f(8.0, 11.0, 13.01);
		
		glVertex3f(0.0, 14.0, 13.01);

	glEnd();


	// draw doors
	
	setMaterial(12);
	
	glBegin(GL_QUADS);
	
		glVertex3f(-3.0, 3.0, 10.01);
	
		glVertex3f(0.0, 3.0, 10.01);
		
		glVertex3f(0.0, 8.0, 10.01);
		
		glVertex3f(-3.0, 8.0, 10.01);


		glVertex3f(0.0, 3.0, 10.01);
		
		glVertex3f(3.0, 3.0, 10.01);
		
		glVertex3f(3.0, 8.0, 10.01);
		
		glVertex3f(0.0, 8.0, 10.01);

	glEnd();
		
}
