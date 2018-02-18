/* Athabasca University

   Comp390 - Introduction to Computer Graphics
   
   TME 1 Program 1


   @author: Jason Bishop

   @student: 3042012

   @date: May 1, 2015


   Program: The purpose of this program is to demonstrate the use of OpenGL drawing features including
		the antialiasing functions available.  Two houses are drawn, the top one without antialiasing and
		the second lower one with antialiasing enabled.

   Routines:
		main - Initializes the GLUT library and creates and positions the display window.  It also calls
			several routines to display the content within the window.
		
		initialize - Sets the background colour of the display window to white.

		reshape - Sets the viewing projection properties of the scene.

		display - Sets the viewing properties of the scene.

		render - Creates the 2D content for display in the window.

		noAlias - Draws a house with a triangle and square in the normal manner.

		withAlias - Draws a house with a triangle and a square with antialiasing functions enabled.

*/


#include "gl/glut.h"


// initialize

void initialize() {

	// set background color

	glClearColor(1.0, 1.0, 1.0, 0.0);

}



// draw the first (top) house with no antialiasing

void noAlias() {
	
	// points for square bottom of house

	float sqPts [4][2] = {{0,2}, {1,3}, {0,4}, {-1,3}};
	
	// points for triangle top of house

	float triPts [3][2] = {{0 + 0.25 ,4 + 0.25}, {-1 - 0.25, 3 - 0.25}, {-1.0, 4.0}};
	
	// disable any active antialiasing functions

	glDisable(GL_LINE_SMOOTH);

	glDisable(GL_BLEND);	

	// draw bottom

	glBegin(GL_QUADS);

		glVertex2f(sqPts[0][0], sqPts[0][1]);

		glVertex2f(sqPts[1][0], sqPts[1][1]);

		glVertex2f(sqPts[2][0], sqPts[2][1]);

		glVertex2f(sqPts[3][0], sqPts[3][1]);

	glEnd();

	// draw top

	glBegin(GL_TRIANGLES);

		glVertex2f(triPts[0][0], triPts[0][1]);

		glVertex2f(triPts[1][0], triPts[1][1]);

		glVertex2f(triPts[2][0], triPts[2][1]);
	
	glEnd();

}



// draw second (lower) house with antialiasing

void withAlias() {

	// points for square bottom of house

	float sqPts [4][2] = {{0.0, -2.0}, {1.0, -1.0}, {0.0, 0.0}, {-1.0, -1.0}};
	
	// points for triangle top of house

	float triPts [3][2] = {{0.0 + 0.25 , 0.0 + 0.25}, {-1.0 - 0.25, -1.0 - 0.25}, {-1.0, 0.0}};

	// enable the antialising functions

	glEnable(GL_LINE_SMOOTH);

	glEnable(GL_BLEND);	

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// draw bottom

	glBegin(GL_QUADS);
	
		glVertex2f(sqPts[0][0], sqPts[0][1]);

		glVertex2f(sqPts[1][0], sqPts[1][1]);

		glVertex2f(sqPts[2][0], sqPts[2][1]);

		glVertex2f(sqPts[3][0], sqPts[3][1]);

	glEnd();

	// draw top

	glBegin(GL_TRIANGLES);

		glVertex2f(triPts[0][0], triPts[0][1]);

		glVertex2f(triPts[1][0], triPts[1][1]);

		glVertex2f(triPts[2][0], triPts[2][1]);

    glEnd();

}



// render

void render() {

	// points color

	glColor3f(0.0, 0.0, 0.0);
	
	// set mode to draw polygons without fill
	
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	// call drawing functions

	noAlias();

	withAlias();	

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

void main(int argc, char **argv) {

	glutInit( &argc, argv );

	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH) ;

	glutInitWindowSize(500, 500);

  	glutInitWindowPosition(100, 100);


	int windowHandle = glutCreateWindow("Comp 390 - TME 1 Program 1");

	glutSetWindow(windowHandle);


	glutDisplayFunc( display );

	glutReshapeFunc( reshape );


	initialize();


    glutMainLoop();

}