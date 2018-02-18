/* Athabasca University

   Comp390 - Introduction to Computer Graphics

   TME 3 Program 1


   @author: Jason Bishop

   @student#: 3042012

   @date: May 6, 2015


   Program: The purpose of this program is to demonstrate the use of the lighting model available in
			OpenGL.  A sphere is displayed and lit with three lights.  The user can access a menu with the
			mouse that allows changes to the colours of the lights, the lighting elements used, and the
			material properties of the sphere.

   Routines:

		main - Initializes the GLUT library and creates and positions the display window.  It also calls
			several routines to display the content within the window.
		
		initialize - Sets the background colour of the display window to white and enables depth testing.
			It also sets the lighting paramaters for 3 lights and enables them for display in the scene.

		reshape - Sets the viewing projection properties of the scene.

		display - Sets the viewing properties of the scene.

		render - Creates the sphere.

		mainMenu - A menu callback function to handle the main menu functions.  It allows the user to exit
			the program.

		l0SubMenu - A menu callback function to allow the user to change the colour of GL_LIGHT0 or
			turn it off.

		l1SubMenu - A menu callback function to allow the user to change the colour of GL_LIGHT1 or
			turn it off.

		l2SubMenu - A menu callback function to allow the user to change the colour of GL_LIGHT2 or
			turn it off.

		matSubMenu - A menu callback function to allow the user to change the material properties of the
			displayed sphere.

		getColor - Returns a pointer to an array that represents the colour state of a light.  This is used
			because the lighting elements change the colour of the displayed light.

		elemSubMenu - A menu callback function to allow the user to manipulate the lighting elements used
			in the scene.

		createMenuSys - Creates the menu hierarchy and assigns access to the right mouse button.

*/



#include "gl/glut.h"


// define color value integers

#define WHITE 0

#define RED 1

#define BLUE 2

#define GREEN 3


// menus

GLint light0Menu, light1Menu, light2Menu, matMenu, elemMenu;


// array to store color state of light
// 0 = white, 1 = red, 2 = blue, 3 = green

GLint light_state[] = { WHITE, RED, BLUE };


// light positions

static const GLfloat light_position0[] = { -10.0, 10.0, 10.0, 0.0 };  // top left

static const GLfloat light_position1[] = { 10.0, 10.0, 10.0, 0.0 };  // top right

static const GLfloat light_position2[] = { 0.0, 0.0, 5.0, 0.0 };  // behind viewer postion (0.0, 0.0, 4.0)


// light color values

static const GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };

static const GLfloat red_light[] = { 1.0, 0.0, 0.0, 1.0 };

static const GLfloat blue_light[] = { 0.0, 0.0, 1.0, 1.0 };

static const GLfloat green_light[] = { 0.0, 1.0, 1.0, 1.0 };

static const GLfloat black_light[] = { 0.0, 0.0, 0.0, 1.0 };

static const GLfloat lmodel_ambient[] = { 0.5, 0.5, 0.5, 1.0 };


// materials

// gold

static const GLfloat gold_ambient[] = { 0.24725, 0.1995, 0.0745, 1.0 };

static const GLfloat gold_diffuse[] = { 0.75164, 0.60648, 0.22658, 1.0 };

static const GLfloat gold_specular[] = { 0.628281, 0.555802, 0.366065, 1.0 };

static const GLfloat gold_shininess[] = { 51.2 };

// silver

static const GLfloat silver_ambient[] = { 0.19225, 0.19225, 0.19225, 1.0 };

static const GLfloat silver_diffuse[] = { 0.50754, 0.50754, 0.50754, 1.0 };

static const GLfloat silver_specular[] = { 0.508273, 0.508273, 0.508273, 1.0 };

static const GLfloat silver_shininess[] = { 51.2 };

// copper

static const GLfloat copper_ambient[] = { 0.2295, 0.08825, 0.0275, 1.0 };

static const GLfloat copper_diffuse[] = { 0.5508, 0.2118, 0.066, 1.0 };

static const GLfloat copper_specular[] = { 0.580594, 0.223257, 0.0695701, 1.0 };

static const GLfloat copper_shininess[] = { 51.2 };



// initialize

void initialize() {

	// set background color

	glClearColor(0.5, 0.7, 0.5, 0.0);


	// enable depth test

	glEnable(GL_DEPTH_TEST);


	// enable lighting

	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0);

	glEnable(GL_LIGHT1);

	glEnable(GL_LIGHT2);


	// set lights

	// light 0

	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);

	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);


	// light 1

	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, red_light);

	glLightfv(GL_LIGHT1, GL_SPECULAR, red_light);


	// light 2

	glLightfv(GL_LIGHT2, GL_POSITION, light_position2);

	glLightfv(GL_LIGHT2, GL_DIFFUSE, blue_light);

	glLightfv(GL_LIGHT2, GL_SPECULAR, blue_light);


	// set global ambient light

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

}



// render

void render() {

	// create grey sphere

	glColor3f(0.5, 0.5, 0.5);

	glPushMatrix();

		glutSolidSphere(1.0, 64, 10);

	glPopMatrix();

}



// display registry

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	
	gluLookAt(0.0, 0.0, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	

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


// main menu execution

void mainMenu(GLint selection)
{
	// exit the program

	if (selection == 0)

		exit(0);
	
}



// change color of GL_LIGHT0 or turn off

void l0SubMenu(GLint selection) {

	switch (selection) {


		// turn light off

		case 0:

			glDisable(GL_LIGHT0);

			break;


		// change light to white

		case 1:

			glEnable(GL_LIGHT0);

			light_state[0] = WHITE;

			glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);

			glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);

			break;


		// change light to red

		case 2:

			glEnable(GL_LIGHT0); 
			
			light_state[0] = RED;

			glLightfv(GL_LIGHT0, GL_DIFFUSE, red_light);

			glLightfv(GL_LIGHT0, GL_SPECULAR, red_light);

			break;


		// change light to blue

		case 3:

			glEnable(GL_LIGHT0); 
			
			light_state[0] = BLUE;

			glLightfv(GL_LIGHT0, GL_DIFFUSE, blue_light);

			glLightfv(GL_LIGHT0, GL_SPECULAR, blue_light);

			break;


		// change light to green

		case 4:

			glEnable(GL_LIGHT0);
			
			light_state[0] = GREEN;

			glLightfv(GL_LIGHT0, GL_DIFFUSE, green_light);

			glLightfv(GL_LIGHT0, GL_SPECULAR, green_light);

			break;

	}

}



// change color of GL_LIGHT1 or turn off

void l1SubMenu(GLint selection) {

	switch (selection) {


		// turn light off

		case 0:

			glDisable(GL_LIGHT1);

			break;


		// change light to white

		case 1:

			glEnable(GL_LIGHT1);

			light_state[1] = WHITE;

			glLightfv(GL_LIGHT1, GL_DIFFUSE, white_light);

			glLightfv(GL_LIGHT1, GL_SPECULAR, white_light);

			break;


		// change light to red

		case 2:

			glEnable(GL_LIGHT1); 
			
			light_state[1] = RED;

			glLightfv(GL_LIGHT1, GL_DIFFUSE, red_light);

			glLightfv(GL_LIGHT1, GL_SPECULAR, red_light);

			break;


		// change light to blue

		case 3:

			glEnable(GL_LIGHT1); 
			
			light_state[1] = BLUE;

			glLightfv(GL_LIGHT1, GL_DIFFUSE, blue_light);

			glLightfv(GL_LIGHT1, GL_SPECULAR, blue_light);

			break;


		// change light to green

		case 4:

			glEnable(GL_LIGHT1);
			
			light_state[1] = GREEN;

			glLightfv(GL_LIGHT1, GL_DIFFUSE, green_light);

			glLightfv(GL_LIGHT1, GL_SPECULAR, green_light);

			break;

	}

}



// change color of GL_LIGHT2 or turn off

void l2SubMenu(GLint selection) {

	switch (selection) {


		// turn light off

		case 0:

			glDisable(GL_LIGHT2);

			break;


		// change light to white

		case 1:

			glEnable(GL_LIGHT2);

			light_state[2] = WHITE;

			glLightfv(GL_LIGHT2, GL_DIFFUSE, white_light);

			glLightfv(GL_LIGHT2, GL_SPECULAR, white_light);

			break;


		// change light to red

		case 2:

			glEnable(GL_LIGHT2); 
			
			light_state[2] = RED;

			glLightfv(GL_LIGHT2, GL_DIFFUSE, red_light);

			glLightfv(GL_LIGHT2, GL_SPECULAR, red_light);

			break;


		// change light to blue

		case 3:

			glEnable(GL_LIGHT2); 
			
			light_state[2] = BLUE;

			glLightfv(GL_LIGHT2, GL_DIFFUSE, blue_light);

			glLightfv(GL_LIGHT2, GL_SPECULAR, blue_light);

			break;


		// change light to green

		case 4:

			glEnable(GL_LIGHT2);
			
			light_state[2] = GREEN;

			glLightfv(GL_LIGHT2, GL_DIFFUSE, green_light);

			glLightfv(GL_LIGHT2, GL_SPECULAR, green_light);

			break;

	}

}


// changes the material properties of the sphere based on the user selection

void matSubMenu(GLint selection) {
	
	switch (selection) {


		// set material properties to gold

		case 1:
			
			glMaterialfv(GL_FRONT, GL_SPECULAR, gold_specular);

			glMaterialfv(GL_FRONT, GL_DIFFUSE, gold_diffuse);

			glMaterialfv(GL_FRONT, GL_AMBIENT, gold_ambient);

			glMaterialfv(GL_FRONT, GL_SHININESS, gold_shininess); 

			break;


		// set material properties to silver

		case 2:

			glMaterialfv(GL_FRONT, GL_SPECULAR, silver_specular);

			glMaterialfv(GL_FRONT, GL_DIFFUSE, silver_diffuse);

			glMaterialfv(GL_FRONT, GL_AMBIENT, silver_ambient);

			glMaterialfv(GL_FRONT, GL_SHININESS, silver_shininess);

			break;

		
		// set material properties to copper

		case 3:
			
			glMaterialfv(GL_FRONT, GL_SPECULAR, copper_specular);

			glMaterialfv(GL_FRONT, GL_DIFFUSE, copper_diffuse);

			glMaterialfv(GL_FRONT, GL_AMBIENT, copper_ambient);

			glMaterialfv(GL_FRONT, GL_SHININESS, copper_shininess);

			break;

	}

}


// returns color of light

const GLfloat* getColor(GLint light) {

	switch (light) {

	case WHITE:

		return white_light;

	case RED:

		return red_light;

	case BLUE:

		return blue_light;

	case GREEN:

		return green_light;
	}

}


// allows user to change the lighting effects in use

void elemSubMenu(GLint selection) {

	switch (selection) {

		// set lighting to ambient only
		// disabling lights allows global ambient lighting only
		
		case 0:

			glDisable(GL_LIGHT0);

			glDisable(GL_LIGHT1);

			glDisable(GL_LIGHT2);

			break;


		// set lighting to ambient and diffuse

		case 1:

			glEnable(GL_LIGHT0);

			glEnable(GL_LIGHT1);

			glEnable(GL_LIGHT2);

			
			glLightfv(GL_LIGHT0, GL_SPECULAR, black_light);

			glLightfv(GL_LIGHT1, GL_SPECULAR, black_light);

			glLightfv(GL_LIGHT2, GL_SPECULAR, black_light);
			
			break;


		// set lighting to ambient, diffuse, and specular

		case 2:

			glEnable(GL_LIGHT0);

			glEnable(GL_LIGHT1);

			glEnable(GL_LIGHT2);


			glLightfv(GL_LIGHT0, GL_SPECULAR, getColor(light_state[0]));

			glLightfv(GL_LIGHT1, GL_SPECULAR, getColor(light_state[1]));

			glLightfv(GL_LIGHT2, GL_SPECULAR, getColor(light_state[2]));

			break;

	}

}



// create the menu system to manipulate the display

void createMenuSys() {
	
	// create light1 submenu

	light0Menu = glutCreateMenu(l0SubMenu);
		
		glutAddMenuEntry("Off", 0);
		
		glutAddMenuEntry("White Light", 1);
		
		glutAddMenuEntry("Red Light", 2);
		
		glutAddMenuEntry("Blue Light", 3);
		
		glutAddMenuEntry("Green Light", 4);


	// create light 2 submenu

	light1Menu = glutCreateMenu(l1SubMenu);
		
		glutAddMenuEntry("Off", 0);

		glutAddMenuEntry("White Light", 1);

		glutAddMenuEntry("Red Light", 2);

		glutAddMenuEntry("Blue Light", 3);

		glutAddMenuEntry("Green Light", 4);


	// create light3 submenu

	light2Menu = glutCreateMenu(l2SubMenu);

		glutAddMenuEntry("Off", 0);

		glutAddMenuEntry("White Light", 1);

		glutAddMenuEntry("Red Light", 2);

		glutAddMenuEntry("Blue Light", 3);

		glutAddMenuEntry("Green Light", 4);


	// create materials submenu

	matMenu = glutCreateMenu(matSubMenu);

		glutAddMenuEntry("Gold", 1);

		glutAddMenuEntry("Silver", 2);

		glutAddMenuEntry("Copper", 3);


	// create elements submenu

	elemMenu = glutCreateMenu(elemSubMenu);

		glutAddMenuEntry("Ambient only", 0);

		glutAddMenuEntry("Ambient and Diffuse", 1);

		glutAddMenuEntry("Ambient, Diffuse and Specular", 2);


	// create main menu

	glutCreateMenu(mainMenu);		
		
		glutAddSubMenu("Light0", light0Menu);
		
		glutAddSubMenu("Light1", light1Menu);
		
		glutAddSubMenu("Light2", light2Menu);
		
		glutAddSubMenu("Material Properties", matMenu);
		
		glutAddSubMenu("Light Elements", elemMenu);
		
		glutAddMenuEntry("Quit", 0);


	// set menu to activate with right mouse click

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}




// main program

void main(int argc, char **argv) {

	glutInit( &argc, argv );

	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH) ;

	glutInitWindowSize(500, 500);

  	glutInitWindowPosition(50, 50);



	int windowHandle = glutCreateWindow("Comp 390 - TME 3 Program 1");

	glutSetWindow(windowHandle);


	glutDisplayFunc( display );


	initialize();

	
	// create right click menu to change lighting options

	createMenuSys();
	

	glutReshapeFunc( reshape );

    glutMainLoop();

}