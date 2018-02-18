/* Athabasca University

   Comp390 - Introduction to Computer Graphics

   TME 4 Program 2

   
   @author: Jason Bishop

   @student: 3042012

   @date: May 16, 2015


   Program: The purpose of this program is to demonstrate the continued use of a recursive ray tracing
			algorithm to calculate lighting and shadows in an OpenGL program.  The scene is of a red square
			casting a shadow on a reflective gray surface.  The scene is made up of individual rectangles.
			Each rectangle uses a ray cast from	the viewer to determine the local colour of the individual
			rectangle.

   Routines:

		main - Initializes the GLUT library and creates and positions the display window.  It also calls
			several routines to display the content within the window.
		
		initialize - Sets the background colour of the display window.

		reshape - Sets the viewing projection properties of the scene.

		display - Sets the viewing properties of the scene.

		render - Renders the objects in the scene and determines colours by calling the recursive ray
				tracing algorithm.

		rayTrace - A recursive function that returns the colour values of an idividual rectangle.  The 
			algorithm calculates the ray from the viewer into the scene and calculates the colour depending
			on the intersection of the ray with an object in the scene.  The function recursively calls
			itself to calculate values based on a reflection vector when the original ray hits the
			reflective surface.  If it hits the non-reflective wall, or the reflection ray hits nothing,
			the recursion will terminate.  Shadows are calculated by creating a shadow ray to the light
			source, if the ray intersects the wall on the way to the light source, shadowing calcuations
			are used in the local colour determination.

		localColor - Calculates the local colour of a rectangle by using the ambient and diffuse intensity
			values.  No specular calculation is done as it was not specified in the program requirements.

*/



#include <iostream>

#include <math.h>

#include "gl/glut.h"

#include "plane.h"


using namespace std;


// viewer

vector3 viewer(-40.0, 80.0, 160.0);


// floor

vector3 floorNormal(0.0, 1.0, 0.0);

plane   floorDef(0.0, 4.0, 0.0, 0.0);

vector3 floorLimit1(-75.0, 0, -75.0);

vector3 floorLimit2(-75.0, 0, 75.0);

vector3 floorLimit3(75.0, 0, 75.0);

vector3 floorLimit4(75.0, 0, -75.0);
	

// wall

vector3 wallNormal(0.0, 0.0, 1.0);

plane   wall(0.0, 0.0, 4.0, 0.0);

vector3 wallLimit1(-25.0, 0.0, 0.0);

vector3 wallLimit2(-25.0, 50.0, 0.0);

vector3 wallLimit3(25.0, 50.0, 0.0);

vector3 wallLimit4(25.0, 0.0, 0.0);


// colors

vector3 grey(0.75, 0.75, 0.75);

vector3 lightRed(0.75, 0.1, 0.1);

	
// lighting position

vector3 lightPosition(50, 50, 100.0);


// lighting elements

float ambient_coef = 0.3;

float diffuse_coef = 0.7;

float reflect_coef = 0.4;

float local_coef   = 0.6;



// initialize

void initialize() {

	// set background color

	glClearColor(0.5, 0.7, 0.5, 0.0);

}



// calculate local color

// local color is intensity * base color

vector3 localColor(vector3 intersect, vector3 baseColor, vector3 normal) {

	// calculate unit vector

	vector3 origin = lightPosition.subtract(intersect);

	vector3 unitVec = origin.normalize();



	// calculate dot product

	float dotProd = unitVec.dot(normal);



	// calculate intensity

	float ambientContr = ambient_coef;

	float diffuseContr = diffuse_coef * dotProd;

	float intensity = ambientContr + diffuseContr;



	if (intensity > 1.0) intensity = 1.0;



	float r = intensity * baseColor.x;

	float g = intensity * baseColor.y;

	float b = intensity * baseColor.z;



	return vector3(r,g,b);

}


// recursive ray tracing algorithm

vector3 rayTrace(vector3 i1, vector3 i2, int numCalls) {

	// calculate intersection with objects in the scene

	vector3 wallIntersect = wall.intersect(i1, i2);
	
	vector3 floorIntersect = floorDef.intersect(i1, i2);
	

	// terminate recursion if ray hits non-reflective wall

	if ((wallIntersect.x >= -25.0) && (wallIntersect.x <= 25.0) && (wallIntersect.y >= 0.0)
		&& (wallIntersect.y <= 50.0)) {
			
			return localColor(wallIntersect, lightRed, wallNormal);

	}

	// use shadow ray from point to light source to determine shadows

	else if ((floorIntersect.x >= -75.0) && (floorIntersect.x <= 75.0) && (floorIntersect.z >= -75.0)
		&& (floorIntersect.z <= 75.0)) {
		
			vector3 shadowIntersect = wall.intersect(i1, lightPosition);

		if ((shadowIntersect.x >= -25.0) && (shadowIntersect.x <= 25.0) && (shadowIntersect.y >= 0.0)
			&& (shadowIntersect.y <= 50.0)) {

				return grey.scalar(ambient_coef);

		}
		
		else {
			
			// calculate reflection ray 

			vector3 reflectRay = i2.subtract(i1);
			
			reflectRay = reflectRay.reflect(floorNormal);
			
			reflectRay = reflectRay.add(i1);
			
			// recursion point if ray hits reflective surface

			return ((localColor(i1, grey, floorNormal)).scalar(local_coef)).add(
				(rayTrace(reflectRay, i1, ++numCalls).scalar(reflect_coef)));

		}

	}

	else {
		
		// return grey colour of reflective surface if ray hits nothing

		return localColor(floorIntersect, grey, floorNormal);

	}

}



// render

void render() {

	// render the floor

	for (int i=-75; i < 75; i++) {

		for (int j=-75; j < 75; j++) {

			vector3 intersect = vector3(i,0,j);
			vector3 mixedColor = rayTrace(intersect, viewer, 0);


			glColor3f(mixedColor.x, mixedColor.y, mixedColor.z);


			// use the small rectangles method

			glBegin(GL_POLYGON);

				glVertex3i(i, 0, j);

				glVertex3i(i+1, 0, j);

				glVertex3i(i+1, 0, j+1);

				glVertex3i(i, 0, j+1);

			glEnd();

		}

	}


	// render the wall - non-reflective surface

	for (int m=-25; m<25; m++) {

		for(int n=0; n<50; n++) {
			vector3 intersect(m, n, 0.0);
			vector3 color = rayTrace(intersect, viewer, 0);


			glColor3f(color.x, color.y, color.z);

			glRecti(m, n, m+1, n+1);

		}

	}

}



// display registry

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();


	gluLookAt(viewer.x, viewer.y, viewer.z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);


	render();


	glutSwapBuffers();

}



// reshape registry

void reshape(int w, int h) {

	glViewport(0, 0, (GLsizei) w, (GLsizei) h);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 250.0);

	glMatrixMode(GL_MODELVIEW);

}



// main program

void main(int argc, char **argv) {

	glutInit( &argc, argv );

	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH) ;

	glutInitWindowSize(500, 500);

  	glutInitWindowPosition(50, 50);


	int windowHandle = glutCreateWindow("Comp390 - TME 4 Program 2");

	glutSetWindow(windowHandle);


	glutDisplayFunc( display );

	glutReshapeFunc( reshape );


	initialize();


    glutMainLoop();

}
