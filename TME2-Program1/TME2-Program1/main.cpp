/* Athabasca University

   Comp390 - Introduction to Computer Graphics

   TME 2 Program 1

   
   @author: Jason Bishop

   @student: 3042012

   @date: May 4, 2015 - Happy Star Wars Day!


   Program: The purpose of this program is to use OpenGL to model an object using a hierarchical structure.
   		The hierarchy is created through the use of lists.  At the bottom of the hierarchy, an individual
   		list is made for each basic 2D shape.  The next level of the hierarchy builds 3D objects using the
   		lower level 2D shapes.  The highest level constructs the scene by calling from the lower levels.

   Routines:
		main - Initializes the GLUT library and creates and positions the display window.  It also calls
			several routines to display the content within the window.
		
		initialize - Sets the background colour of the display window to white and enables depth testing.

		reshape - Sets the viewing projection properties of the scene.

		display - Sets the viewing properties of the scene.

		render - Implements the hierarchical structure to model objects in the scene.

*/



#include "gl/glut.h"



// initialize

void initialize() {

	// set background color

	glClearColor(1.0, 1.0, 1.0, 0.0);

	// enable depth test

	glEnable(GL_DEPTH_TEST);

}



// render

void render() {

	// create and initialize variables for list IDs

	GLuint triangle, square, ground, pyramid, cube, scene;

	triangle = glGenLists(1);

	square = glGenLists(1);

	ground = glGenLists(1);

	pyramid = glGenLists(1);

	cube = glGenLists(1);

	scene = glGenLists(1);

	
	// set mode to draw polygons without fill
	
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	
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





// display registry

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();



	// viewing

	gluLookAt(3.0, 3.0, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);


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

  	glutInitWindowPosition(50, 50);



	int windowHandle = glutCreateWindow("Comp390 - TME 2 Program 1");

	glutSetWindow(windowHandle);



	glutDisplayFunc( display );

	glutReshapeFunc( reshape );


	initialize();


    glutMainLoop();

}