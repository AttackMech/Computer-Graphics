/* Athabasca University

   Comp390 - Introduction to Computer Graphics
   
   TME 3 Program 2


   @author: Jason Bishop

   @student: 3042012

   @date: May 10, 2015


   Program: The purpose of this program is to add a specular contribution to a lighting model that already
			includes both ambient and diffuse values.  The program renders a red square made of many
			smaller scares.  The complete square appears with a specular highlight in the top-right area.

   Routines:
		main - Initializes the GLUT library and creates and positions the display window.  It also calls
			several routines to display the content within the window.
		
		initialize - Sets the background colour of the display window.

		reshape - Sets the viewing projection properties of the scene.

		display - Sets the viewing properties of the scene.

		render - Creates the series of squares that make up the total square.

		localColor - Calculates the colour of an individual small square based on it's position in
				relation to the light source.  The colour is a sum of the ambient, diffuse, and specular
				contributing values.


*/



#include <iostream>

#include <math.h>

#include "gl/glut.h"

#include "vector3.h"


using namespace std;



// viewer

vector3 viewer(0.0, 0.0, 100.0);


// square

vector3 wallNormal(0.0, 0.0, 1.0);


// colors

vector3 grey(0.75, 0.75, 0.75);

vector3 lightRed(0.75, 0.1, 0.1);
	

// lighting position

vector3 lightPosition(10, 10, 10);


// lighting elements

float ambient_coef = 0.3;

float diffuse_coef = 0.7;


// additional specular variables

// specular coeffient

float specular_coef = 0.6;

// specular exponent
// set to resemble a dull surface so the specular highlight is larger (more visible)

float specular_exp = 20.0;


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



	// calculate dot product for diffuse lighting

	float diffuseDotProd = unitVec.dot(normal);

	
	// addtional specular calculations
	
	// reflection vector

	vector3 reflect = (normal.scalar((normal.scalar(2.0)).dot(unitVec))).subtract(unitVec);
	
	// dot product of reflection and view vectors for specular lighting

	float specDotProd = reflect.dot(viewer.normalize());


	// calculate intensity

	float ambientContr = ambient_coef;

	float diffuseContr = diffuse_coef * diffuseDotProd;

	// additional specular intensity contribution

	float specularContr = specular_coef * powf(specDotProd, specular_exp);  // specular addition


	// total intensity now includes specular contribution

	float intensity = ambientContr + diffuseContr + specularContr;



	if (intensity > 1.0) intensity = 1.0;



	float r = intensity * baseColor.x;

	float g = intensity * baseColor.y;

	float b = intensity * baseColor.z;



	return vector3(r,g,b);

}



// render

void render() {

	// render the square

	for (int m=-25; m<25; m++) {

		for(int n=-25; n<25; n++) {

			vector3 color = localColor(vector3(m,n,0), lightRed, wallNormal);

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



	int windowHandle = glutCreateWindow("Comp390 - TME 3 Program 2");

	glutSetWindow(windowHandle);



	glutDisplayFunc( display );

	glutReshapeFunc( reshape );



	initialize();



    glutMainLoop();

}