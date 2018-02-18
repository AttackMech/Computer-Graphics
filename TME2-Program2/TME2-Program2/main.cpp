/* Athabasca University

   Comp390 - Introduction to Computer Graphics

   TME 2 Program 2

   
   @author: Jason Bishop

   @student: 3042012

   @date: May 4, 2015 - Happy Star Wars Day!


   Program: The purpose of this program is to use the 3D transformation and projection functions of OpenGL.
   		The program creates a scene using the house structure from TME 2 Program 1.  8 different versions
   		of the house are placed into the scene, each individually scaled, translated, and rotated.

   Routines:
		main - Initializes the GLUT library and creates and positions the display window.  It also calls
			several routines to display the content within the window.
		
		initialize - Sets the background colour of the display window to white and enables depth testing.

		reshape - Sets the viewing projection properties of the scene.

		display - Sets the viewing properties of the scene.

		render - Uses various transform operations to place each house into the scene.

		drawHouse - Implements the hierarchical structure to model house objects in the scene.

*/



#include "gl/glut.h"



// initialize

void initialize() {

	// set background color

	glClearColor(1.0, 1.0, 1.0, 0.0);

	// enable depth test

	glEnable(GL_DEPTH_TEST);

}


void drawHouse() {
	
	// create and initialize variables for list IDs

	GLuint triangle, square, ground, pyramid, cube, scene;

	triangle = glGenLists(1);

	square = glGenLists(1);

	ground = glGenLists(1);

	pyramid = glGenLists(1);

	cube = glGenLists(1);

	scene = glGenLists(1);

	
	// set vertices for each 2D shape

	float tri [3][3] = {{0.5, 1.5, 0.5}, {1.2, 1.0, 1.2}, {-0.2, 1.0, 1.2}};

	float sq [4][3] = {{1.0, 1.0, 1.0}, {1.0, 0.0, 1.0}, {0.0, 0.0, 1.0}, {0.0, 1.0, 1.0}};

	float rect [4][3] = {{-1.0, 0.0, -0.5}, {2.0, 0.0, -0.5}, {2.0, 0.0, 2.5}, {-1.0, 0.0, 2.5}};
	

	// list for single blue triangle 
	
	glNewList(triangle, GL_COMPILE);
		
		glColor3f(0.0, 0.0, 1.0);

		glBegin(GL_TRIANGLES);

			glVertex3fv(tri[0]);

			glVertex3fv(tri[1]);

			glVertex3fv(tri[2]);

		glEnd();

	glEndList();


	// list for single red square
	
	glNewList(square, GL_COMPILE);
	
		glColor3f(1.0, 0.0, 0.0);
	
		glBegin(GL_QUADS);
		
			glVertex3fv(sq[0]);
			
			glVertex3fv(sq[1]);
			
			glVertex3fv(sq[2]);
			
			glVertex3fv(sq[3]);

		glEnd();

	glEndList();


	// list for single green rectangle
	
	glNewList(ground, GL_COMPILE);
	
		glColor3f(0.0, 1.0, 0.0);
	
		glBegin(GL_QUADS);
		
			glVertex3fv(rect[0]);
			
			glVertex3fv(rect[1]);
			
			glVertex3fv(rect[2]);
			
			glVertex3fv(rect[3]);

		glEnd();

	glEndList();


	// list for pyramid roof

	glNewList(pyramid, GL_COMPILE);

		// draw front triangle

		glCallList(triangle);

		// set matrix mode

		glMatrixMode(GL_MODELVIEW);


		// draw right triangle

		glPushMatrix();
			
			glTranslatef(0.5, 0.0, 0.5);

			glRotatef(90.0, 0.0, 1.0, 0.0);

			glTranslatef(-0.5, 0.0, -0.5);

			glCallList(triangle);

		glPopMatrix();


		// draw back triangle

		glPushMatrix();

			glTranslatef(0.5, 0.0, 0.5);

			glRotatef(180.0, 0.0, 1.0, 0.0);

			glTranslatef(-0.5, 0.0, -0.5);
			
			glCallList(triangle);

		glPopMatrix();


		// draw left triangle

		glPushMatrix();

			glTranslatef(0.5, 0.0, 0.5);

			glRotatef(-90.0, 0.0, 1.0, 0.0);

			glTranslatef(-0.5, 0.0, -0.5);

			glCallList(triangle);

		glPopMatrix();

	glEndList();


	// create cube body

	glNewList(cube, GL_COMPILE);
	
		// draw front square

		glCallList(square);

		// set matrix mode

		glMatrixMode(GL_MODELVIEW);

		
		// draw left square

		glPushMatrix();
			
			glTranslatef(0.5, 0.0, 0.5);
			
			glRotatef(90.0, 0.0, 1.0, 0.0);
			
			glTranslatef(-0.5, 0.0, -0.5);
			
			glCallList(square);

		glPopMatrix();


		// draw back square

		glPushMatrix();
		
			glTranslatef(0.5, 0.0, 0.5);
			
			glRotatef(180.0, 0.0, 1.0, 0.0);
			
			glTranslatef(-0.5, 0.0, -0.5);
			
			glCallList(square);

		glPopMatrix();


		// draw left square

		glPushMatrix();

			glTranslatef(0.5, 0.0, 0.5);
			
			glRotatef(-90.0, 0.0, 1.0, 0.0);
			
			glTranslatef(-0.5, 0.0, -0.5);
			
			glCallList(square);
		
		glPopMatrix();

	glEndList();

	
	// create complete scene

	glNewList(scene, GL_COMPILE_AND_EXECUTE);
		
		// draw the ground
		
		glCallList(ground);

		// draw the pyramid

		glCallList(pyramid);

		// draw the cube

		glCallList(cube);
		
	glEndList();

}

// render

void render() {

	
	// draw grey ground

	glColor3f(0.7, 0.7, 0.7);
	
	glBegin(GL_QUADS);
		
		glVertex3f(-8.0, -0.1, -8.0);
		
		glVertex3f(8.0, -0.1, -8.0);
		
		glVertex3f(8.0, -0.1, 8.0);
		
		glVertex3f(-8.0, -0.1, 8.0);
	
	glEnd();


	glPushMatrix();

		// translate and rotate house to proper orientation about origin

		glRotatef(-90.0, 0.0, 1.0, 0.0);
	
		glTranslatef(-0.5, 0.0, -0.5);
	

		/* In the following code, houses are numbered based on their position within the scene.  The house
			at the farthest back and left position is numbered 1.  The houses are numbered in order moving
			to the right.  The next row is toward the user, continuing the sequential numbering.  The 
			closest row to the user has the left and right houses numbered 7 and 8 respectively. */

		// Draw house 1

		glPushMatrix();
			
			glTranslatef(-5.0, 0.0, -5.0);
			
			glRotatef(45.0, 0.0, 1.0, 0.0);
			
			glScalef(1.0, 1.5, 1.0);
			
			drawHouse();
		
		glPopMatrix();

		
		// Draw house 2

		glPushMatrix();
		
			glTranslatef(0.0, 0.0, -5.0);
		
			glScalef(1.5, 0.75, 1.5);
		
			drawHouse();
		
		glPopMatrix();
		

		// Draw house 3

		glPushMatrix();
		
			glTranslatef(5.0, 0.0, -5.0);
		
			glScalef(1.0, 1.5, 1.0);
		
			drawHouse();
		
		glPopMatrix();

		
		// Draw house 4

		glPushMatrix();
		
			glTranslatef(-5.0, 0.0, 0.0);
		
			glScalef(1.0, 1.5, 2.0);
		
			drawHouse();
		
		glPopMatrix();

		
		// Draw house 5

		drawHouse();

		
		// Draw house 6

		glPushMatrix();
		
			glTranslatef(5.0, 0.0, 0.0);
		
			glScalef(1.0, 1.0, 1.5);
		
			drawHouse();
		
		glPopMatrix();

		
		// Draw house 7

		glPushMatrix();
		
			glTranslatef(-1.0, 0.0, 5.0);
		
			glScalef(1.5, 1.0, 1.0);
		
			drawHouse();
		
		glPopMatrix();

		
		// Draw house 8

		glPushMatrix();
		
			glTranslatef(4.0, 0.0, 5.0);
		
			glScalef(1.75, 0.5, 1.0);
		
			drawHouse();
		
		glPopMatrix();
		
	glPopMatrix();

}



// display registry

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();



	// viewing

	gluLookAt(-12.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);


	render();


	glutSwapBuffers();

}



// reshape registry

void reshape(int w, int h) {

	glViewport(0, 0, (GLsizei) w, (GLsizei) h);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 90.0);

	glMatrixMode(GL_MODELVIEW);

}



// main program

void main(int argc, char **argv) {

	glutInit( &argc, argv );

	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH) ;

	glutInitWindowSize(500, 500);

  	glutInitWindowPosition(50, 50);



	int windowHandle = glutCreateWindow("Comp390 - TME 2 Program 2");

	glutSetWindow(windowHandle);



	glutDisplayFunc( display );

	glutReshapeFunc( reshape );


	initialize();


    glutMainLoop();

}