/* Athabasca University

   Comp390 - Introduction to Computer Graphics

   Final Project Option 1


   @author: Jason Bishop

   @student#: 3042012

   @date: May 16, 2015


   Program: The purpose of this program is to draw a scene with a textured background, including an
			atmospheric attenuation effect, 3 different colored lights, and 5 3D composite objects, made of
			5 or more geometric shapes.  The scene drawn here is a bank building with a police officer, his
			car, and 2 bank robbers.  The police officer is pointing his gun at one robber, while the other
			lies on the ground apparently dead.  The scene is lit with a directional source to represent
			the sun, and the police car lights are directional spotlights which alternate red and blue.
			The scene is surrounded by 4 quads textured with a city background, and the floor of the scene
			is a rectangle of green (for grass) crossed by a road with yellow lane lines.  The entire
			scene has a slight gray fog applied.  Additionally, the view around the scene can be rotated
			by accessing a menu using the right mouse button.


   Routines:

		main - Initializes the GLUT library and creates and positions the display window.  It also calls
			several routines to display the content within the window and creates a right mouse menu.
		
		initialize - Sets the background colour of the display window, enables depth testing, sets lighting
			paramaters, enables fog in the scene, stores the current time.

		reshape - Sets the viewing projection properties of the scene.

		display - Sets the viewing properties of the scene.

		render - Creates and displays the background scene objects, including textured walls.

		drawScene - Creates and displays composite objects in the scene.

		makeImage - Loads an image file and stores the colour values for use in texturing.

		flash - Based on the passage of time, lights will be enabled/disabled to simulate flashing police
			lights.

		rotMenu - A menu callback function that allows the user to rotate the view of the scene about the
		y-axis in either a clockwise or anti-clockwise rotation.


*/



#include <iostream>

#include <math.h>

#include "gl/glut.h"

#include "objects.h"

#include "material_constants.h"

#include <time.h>

#include "vector3.h"



// value of pi

#define PI 3.14159265


using namespace std;



// set initial values for view position

float rotVal = (PI / 3);

float viewRadius = 27.0;

vector3 viewer(viewRadius * cosf(rotVal), 20, viewRadius * sinf(rotVal));
	

// lighting constants

static const GLfloat lightPosition0[] = { 30.0, 100.0, 20.0, 0.0 };

static const GLfloat lightPosition1[] = { 10.5, 3.0, -7.0, 1.0 };

static const GLfloat lightPosition2[] = { 9.5, 3.0, -9.0, 1.0 };

static const GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };

static const GLfloat red_light[] = { 1.0, 0.0, 0.0, 1.0 };

static const GLfloat blue_light[] = { 0.0, 0.0, 1.0, 1.0 };

static const GLfloat red_direction[] = { 0.0, 0.0, -1.0 };

static const GLfloat blue_direction[] = { 0.0, 0.0, -1.0 };

static const GLfloat spot_cutoff = 45.0;

static const GLfloat spot_exp = 2.5;

static const GLfloat lmodel_ambient[] = { 0.7, 0.7, 0.7, 1.0 };


// image variables

GLubyte *image;

//unsigned char * l_texture;

GLubyte * l_texture;

BITMAPFILEHEADER fileheader; 

BITMAPINFOHEADER infoheader;

RGBTRIPLE rgb;

GLuint texName;


// create object to access scene elemets

objects obs;


// time storage variables

clock_t start_time, time_now;


// load texture file and store values

void makeImage() {

	int i, j=0;

	FILE *l_file;



	string fn = "city256.bmp";

	const char * filename = fn.c_str();



	// open image file, return if error

	fopen_s(&l_file, filename, "rb");

	if (l_file == NULL) return;



	// read file header and header info

	fread(&fileheader, sizeof(fileheader), 1, l_file);

	fseek(l_file, sizeof(fileheader), SEEK_SET);

	fread(&infoheader, sizeof(infoheader), 1, l_file);



	// allocate space for the image file

	l_texture = (GLubyte *) malloc(infoheader.biWidth * infoheader.biHeight * 4);

	memset(l_texture, 0, infoheader.biWidth * infoheader.biHeight * 4);



	// read data

	j = 0;

	for (i=0; i < infoheader.biWidth*infoheader.biHeight; i++)

	{ 

		fread(&rgb, sizeof(rgb), 1, l_file); 



		l_texture[j+0] = (GLubyte) rgb.rgbtRed; // Red component

		l_texture[j+1] = (GLubyte) rgb.rgbtGreen; // Green component

		l_texture[j+2] = (GLubyte) rgb.rgbtBlue; // Blue component

		l_texture[j+3] = (GLubyte) 255; // Alpha value

		j += 4; // Go to the next position

	}


	fclose(l_file); // Closes the file stream

}
	


// initialize

void initialize() {

	// set background color
	
	glClearColor(0.5, 0.5, 0.5, 0.0);


	// allow depth checking
	
	glEnable(GL_DEPTH_TEST);


	// enable lighting and set properties
	
	// sunlight

	glEnable(GL_LIGHTING);
	
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);

	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);

	// red light

	glEnable(GL_LIGHT1);

	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);

	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, red_direction);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, red_light);

	glLightfv(GL_LIGHT1, GL_SPECULAR, red_light);

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spot_cutoff);

	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spot_exp);

	// blue light (currently disabled, will be enabled in later subroutine)

	//glEnable(GL_LIGHT2);

	glLightfv(GL_LIGHT2, GL_POSITION, lightPosition2);

	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, blue_direction);
	
	glLightfv(GL_LIGHT2, GL_DIFFUSE, blue_light);

	glLightfv(GL_LIGHT2, GL_SPECULAR, blue_light);

	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, spot_cutoff);

	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, spot_exp);

	// set global ambient lighting paramaters

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);


	// create fog in scene

	GLfloat fogColor[4] = { 0.5, 0.5, 0.5, 1.0 };

	glFogfv(GL_FOG_COLOR, fogColor);
	
	glFogf(GL_FOG_DENSITY, 0.02);
	
	glFogf(GL_FOG_START, -45.0);
	
	glFogf(GL_FOG_END, 45.0);

	glEnable(GL_FOG);


	// enable texture
	
	makeImage();
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


	glGenTextures(1, &texName);

	glBindTexture(GL_TEXTURE_2D, texName);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 

		infoheader.biWidth, infoheader.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,

		l_texture);

	
	// store current time	
	
	start_time = clock();

}



// place all elements of scene in proper positions

void drawScene() {

	glShadeModel(GL_SMOOTH);
	
	glMatrixMode(GL_MODELVIEW);


	// draw the bank
	
	glPushMatrix();
		
		glTranslatef(-20.0, 0.0, 0.0);
		
		glRotatef(90.0, 0.0, 1.0, 0.0);
		
		glScalef(0.75, 0.75, 0.75);
		
		obs.drawBank();

	glPopMatrix();

	
	// draw the cop car
	
	glPushMatrix();
	
		glTranslatef(10.0, 0.0, -8.0);
		
		glRotatef(-60.0, 0.0, 1.0, 0.0);
		
		glScalef(0.5, 0.5, 0.5);
		
		obs.drawCopCar();
	
	glPopMatrix();

	
	// draw the cop

	glPushMatrix();
		
		glTranslatef(10.0, 0.0, 5.0);
		
		glRotatef(-90.0, 0.0, 1.0, 0.0);
		
		glScalef(0.5, 0.5, 0.5);
		
		obs.drawCop();

	glPopMatrix();


	// draw the 1st robber
	
	glPushMatrix();
		
		glTranslatef(2.0, 0.0, 5.0);
		
		glRotatef(90.0, 0.0, 1.0, 0.0);
		
		glScalef(0.5, 0.5, 0.5);
		
		obs.drawRobber1();

	glPopMatrix();


	// draw the dead robber
	
	glPushMatrix();
		
		glTranslatef(3.0, 0.0, 10.0);
		
		glRotatef(-60.0, 0.0, 1.0, 0.0);
		
		glScalef(0.5, 0.5, 0.5);
		
		obs.drawRobber2();

	glPopMatrix();
	
}


// render

void render() {
		
	// draw backgound details
	
	glBegin(GL_QUADS);
		
		// grass floor

		setMaterial(14);

		glVertex3f(-30.0, -0.02, -30.0);

		glVertex3f(-30.0, -0.02, 30.0);
		
		glVertex3f(30.0, -0.02, 30.0);
		
		glVertex3f(30.0, -0.02, -30.0);


		// road
		
		setMaterial(16);
		
		glColor3f(0.1, 0.1, 0.1);
		
		glVertex3f(12.0, -0.01, -30.0);

		glVertex3f(12.0, -0.01, 30.0);
		
		glVertex3f(-8.0, -0.01, 30.0);
		
		glVertex3f(-8.0, -0.01, -30.0);

		
	glEnd();


	// draw textured walls

	glEnable(GL_TEXTURE_2D);
	
	glBegin(GL_QUADS);
		
		glTexCoord2d(0.0, 0.0); glVertex3f(-30.0, -0.01, -30.0);
		
		glTexCoord2d(1.0, 0.0); glVertex3f(30.0, -0.01, -30.0);
		
		glTexCoord2d(1.0, 1.0); glVertex3f(30.0, 30.0, -30.0);
		
		glTexCoord2d(0.0, 1.0); glVertex3f(-30.0, 30.0, -30.0);
		
		
		glTexCoord2d(0.0, 0.0); glVertex3f(-30.0, -0.01, 30.0);
		
		glTexCoord2d(1.0, 0.0); glVertex3f(-30.0, -0.01, -30.0);
		
		glTexCoord2d(1.0, 1.0); glVertex3f(-30.0, 30.0, -30.0);
		
		glTexCoord2d(0.0, 1.0); glVertex3f(-30.0, 30.0, 30.0);
		
		
		glTexCoord2d(0.0, 0.0); glVertex3f(30.0, -0.01, -30.0);
		
		glTexCoord2d(1.0, 0.0); glVertex3f(30.0, -0.01, 30.0);
		
		glTexCoord2d(1.0, 1.0); glVertex3f(30.0, 30.0, 30.0);
		
		glTexCoord2d(0.0, 1.0); glVertex3f(30.0, 30.0, -30.0);
		
		
		glTexCoord2d(0.0, 0.0); glVertex3f(30.0, -0.01, 30.0);
		
		glTexCoord2d(1.0, 0.0); glVertex3f(-30.0, -0.01, 30.0);
		
		glTexCoord2d(1.0, 1.0); glVertex3f(-30.0, 30.0, 30.0);
		
		glTexCoord2d(0.0, 1.0); glVertex3f(30.0, 30.0, 30.0);

	glEnd();

	glDisable(GL_TEXTURE_2D);
	

	// draw road line
	
	setMaterial(17);
	
	// set line properties
	
	glLineWidth(10.0);
	
	glLineStipple(3, 0x00FF);
	
	glEnable(GL_LINE_STIPPLE);
	
	glBegin(GL_LINES);
		
		glVertex3f(2.0, 0.0, 29.99);
		
		glVertex3f(2.0, 0.0, -29.99);
	
	glEnd();
	
	glDisable(GL_LINE_STIPPLE);
	
	glLineWidth(1.0);
	

	// create scene objects (translated slightly to avoid collision with the rest of the scene)
	
	glPushMatrix();
	
	glTranslatef(0.0 , 0.01, 0.0);
	
		drawScene();
	
	glPopMatrix();
	
}



// display registry

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();


	// set initial view
	
	gluLookAt(viewer.x, viewer.y, viewer.z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	
	render();

	
	glutSwapBuffers();

}



// alternate lights to simulate flashing police lights

void flash() {
	
	time_now = clock();

	if (((time_now - start_time) / CLOCKS_PER_SEC) >= 1.0) {

		if (glIsEnabled(GL_LIGHT1)) {

			glDisable(GL_LIGHT1);

			glEnable(GL_LIGHT2);

		}

		else {

			glDisable(GL_LIGHT2);

			glEnable(GL_LIGHT1);

		}

		start_time = time_now;

		display();

	}
	
}



// reshape registry

void reshape(int w, int h) {

	glViewport(0, 0, (GLsizei) w, (GLsizei) h);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	// create perspective projection
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 200.0);

	glMatrixMode(GL_MODELVIEW);

}



// rotates the view based on the user selection from the menu

void rotMenu(GLint selection) {
	
	// rotate scene clockwise (anticlockwise view)
	if (selection == 0) {
		
		rotVal += PI / 6;

		if (rotVal >= ((2 * PI) - (PI / 180)))
			rotVal = 0.0;

	}

	// rotate scene anticlockwise (clockwise view)
	else {
		
		rotVal -= 3.14159 / 6;

		if (rotVal <= (-(2 * PI) + (PI / 180)))
			rotVal = 0.0;

	}

	// set new view coords
	viewer.x = viewRadius * cosf(rotVal);
	viewer.z = viewRadius * sinf(rotVal);
	
}



// main program

void main(int argc, char **argv) {

	glutInit( &argc, argv );

	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH) ;

	glutInitWindowSize(500, 500);

  	glutInitWindowPosition(50, 50);


	int windowHandle = glutCreateWindow("Athabasca University - Final Project - Option 1");

	glutSetWindow(windowHandle);


	glutDisplayFunc( display );

	glutReshapeFunc( reshape );

	glutIdleFunc( flash );


	initialize();

	
	// add menu to allow rotation of scene

	glutCreateMenu(rotMenu);

		glutAddMenuEntry("Rotate Clockwise", 0);
	
		glutAddMenuEntry("Rotate Anticlockwise", 1);

	// attach menu to right mouse button

	glutAttachMenu(GLUT_RIGHT_BUTTON);


    glutMainLoop();

}