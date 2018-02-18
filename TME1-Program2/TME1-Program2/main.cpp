/* Athabasca University

   Comp390 - Introduction to Computer Graphics

   TME 1 Program 2


   @author: Jason Bishop
   
   @student: 3042012
   
   @date: May 2, 2015


   Program: The purpose of this program is to demonstrate the use of OpenGL transformation features.
		A total of 5 houses are drawn, each rotated by the same angle about the z-axis.

   Routines:
		main - Initializes the GLUT library and creates and positions the display window.  It also calls
			several routines to display the content within the window.
		
		initialize - Sets the background colour of the display window to white.

		reshape - Sets the viewing projection properties of the scene.

		display - Sets the viewing properties of the scene.

		render - Creates the 2D content for display in the window.  It calls the function to draw each
			house after applying the necessary transformations to position it.

		drawHouse - Draws a basic black house centered on the origin.

*/


#include "gl/glut.h"


// store 2D points

typedef float vert2D [2];

// initialize

void initialize() {

	// set background color

	glClearColor(1.0, 1.0, 1.0, 0.0);

}


// draw a house with a square base and triangle roof

void drawHouse(vert2D *sq, vert2D *tri) {
	
	// points color

	glColor3f(0.0, 0.0, 0.0);

	// draw the square base of the house

	glBegin(GL_QUADS);

		glVertex2fv(sq[0]);

		glVertex2fv(sq[1]);

		glVertex2fv(sq[2]);

		glVertex2fv(sq[3]);

	glEnd();

	// draw the triangle roof of the house

	glBegin(GL_TRIANGLES);

		glVertex2fv(tri[0]);

		glVertex2fv(tri[1]);

		glVertex2fv(tri[2]);

	glEnd();

}



// render

void render() {

	// pts for bottom square of house

	vert2D sqPts [4] = {{-0.5,2}, {0.5,2}, {0.5,3}, {-0.5,3}};
	
	// points for triangle top of house

	vert2D triPts [3] = {{-0.5 - 0.2, 3}, {0.5 + 0.2, 3}, {0, 3.5}};
	
	// set mode to draw polygons without fill
	
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	// set the matrix mode for transforming the houses

	glMatrixMode(GL_MODELVIEW);


	// draw the first house in the center

	drawHouse(sqPts, triPts);


	glPushMatrix();

		// draw the second house rotated 30 degrees to the right

		glTranslatef(1.0, 0.0, 0.0);

		glRotatef(-30.0, 0.0, 0.0, 1.0);
	
		drawHouse(sqPts, triPts);
	

		// draw the third house rotated 30 more degrees (total 60) to the right

		glTranslatef(1.0, 0.0, 0.0);
		
		glRotatef(-30.0, 0.0, 0.0, 1.0);
	
		drawHouse(sqPts, triPts);

	glPopMatrix();

	
	glPushMatrix();
		
		// draw the 4th house rotated 30 degrees to the left (from center)

		glTranslatef(-1.0, 0.0, 0.0);

		glRotatef(30.0, 0.0, 0.0, 1.0);

		drawHouse(sqPts, triPts);

		
		// draw the 5th house rotated 30 more degrees (total 60) to the left

		glTranslatef(-1.0, 0.0, 0.0);

		glRotatef(30.0, 0.0, 0.0, 1.0);

		drawHouse(sqPts, triPts);

	glPopMatrix();

}





// display registry

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	// viewing

	gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

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

	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB) ;

	glutInitWindowSize(500, 500);

  	glutInitWindowPosition(50, 50);

	int windowHandle = glutCreateWindow("Comp390 TME 1 Program 2");

	glutSetWindow(windowHandle);

	
	initialize();

	
	glutDisplayFunc( display );

	glutReshapeFunc( reshape );

    
	glutMainLoop();

}