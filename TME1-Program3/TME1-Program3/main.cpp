/* Athabasca University

   Comp390 - Introduction to Computer Graphics

   TME 1 Program 3


   @author: Jason Bishop

   @student: 3042012

   @date: May 1, 2015


   Program: The purpose of this program is to demonstrate the colouring and shading features present in
		OpenGL.  A basic square is drawn with different colours for each of the vertices (red, green, 
		blue, yellow).  The colour within the square is interpolated between the vertices.

   Routines:
		main - Initializes the GLUT library and creates and positions the display window.  It also calls
			several routines to display the content within the window.
		
		initialize - Sets the background colour of the display window to white.

		reshape - Sets the viewing projection properties of the scene.

		display - Sets the viewing properties of the scene.

		render - Creates the 2D content for display in the window.  Draws a square with different colours
			for each of the vertices.

*/



#include "gl/glut.h"



// initialize

void initialize() {

	// set background color

	glClearColor(1.0, 1.0, 1.0, 0.0);

}



// render

void render() {

	// draw a basic square

	glBegin(GL_QUADS);

		// colour the bottom left corner of the square (red)
		
		glColor3f(1.0, 0.0, 0.0);

		glVertex2f(-2.0, -2.0);

		
		// colour the top left corner of the square (green)
		
		glColor3f(0.0, 1.0, 0.0);

		glVertex2f(-2.0, 2.0);


		// color the top right corner of the square (blue)

		glColor3f(0.0, 0.0, 1.0);

		glVertex2f(2.0, 2.0);


		// colour the bottom right corner of the square (yellow)

		glColor3f(1.0, 1.0, 0.0);

		glVertex2f(2.0, -2.0);

	glEnd();

}



// display registry

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();



	// viewing

	gluLookAt(0.0, 0.0, 8.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);



	render();



	glutSwapBuffers();

}



// reshape registry

void reshape(int w, int h) {

	glViewport(0, 0, (GLsizei) w, (GLsizei) h);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 40.0);

	glMatrixMode(GL_MODELVIEW);

}



// main program

void main(int argc, char **argv)

{

	glutInit( &argc, argv );

	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH) ;

	glutInitWindowSize(500, 500);

  	glutInitWindowPosition(100, 100);



	int windowHandle = glutCreateWindow("Athabasca University - Comp390 U5 S2 O2");

	glutSetWindow(windowHandle);



	glutDisplayFunc( display );

	glutReshapeFunc( reshape );



	initialize();



    glutMainLoop();

}