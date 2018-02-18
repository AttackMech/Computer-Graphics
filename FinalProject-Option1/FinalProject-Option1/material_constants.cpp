/*  Athabasca University

	Comp390 - Introduction to Computer Graphics

	Final Project Option 1


	@author: Jason Bishop

	@student#: 3042012

	@date: May 16, 2015


	Purpose:  The purpose of this routine is to set the materials properties in OpenGL using the constants
		defined in the .h file.

	Routines:

		setMaterial - Sets the materials properties based on the passed value.


*/



#include "material_constants.h"



// sets the material paramaters based on the passed value

void setMaterial(int selection) {

	switch (selection) {

		// black dull

		case 0:
			
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black_specular);

			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, black_diffuse);

			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, black_shininess);
			
			break;


		// black shiny

		case 1:
			
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black_specular);

			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, black_diffuse);

			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 99.0);
			
			break;


		// white shiny

		case 2:
			
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white_specular);

			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white_diffuse);

			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, white_shininess);
			
			break;


		// off-white dull

		case 3:
			
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, bank1_specular);

			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, bank1_diffuse);

			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, bank1_shininess);
			
			break;


		// caucasian skin

		case 4:
			
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, skin1_specular);

			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, skin1_diffuse);

			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, skin1_shininess);
			
			break;


		// african-american skin

		case 5:
			
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, skin2_specular);

			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, skin2_diffuse);

			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, skin2_shininess);
			
			break;


		// windows

		case 6:
			
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, window_specular);

			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, window_diffuse);

			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, window_shininess);
			
			break;


		// blue shirt

		case 7:
			
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, shirt_specular);

			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, shirt_diffuse);

			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shirt_shininess);
			
			break;


		// navy pants

		case 8:
			
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, pants_specular);

			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, pants_diffuse);

			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, pants_shininess);
			
			break;


		// blue light

		case 9:
			
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, blue_specular);

			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blue_diffuse);

			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, blue_shininess);
			
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, blue_emissive);

			break;


		// red light

		case 10:
			
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, red_specular);

			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red_diffuse);

			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, red_shininess);

			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, red_emissive);

			break;


		// brown dull

		case 12:
			
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, belt_specular);

			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, belt_diffuse);

			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, belt_shininess);

			break;

			
		// red blood

		case 13:
			
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, blood_specular);

			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blood_diffuse);

			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, blood_shininess);
			
			break;


		// green grass

		case 14:
			
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, grass_specular);

			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, grass_diffuse);

			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, grass_shininess);
			
			break;


		// off-white 2

		case 15:
			
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, bank2_specular);

			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, bank2_diffuse);

			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, bank2_shininess);
			
			break;

		
		// road black

		case 16:

			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, road_specular);

			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, road_diffuse);

			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, road_shininess);
			
			break;


		// lane marker yellow

		case 17:

			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, lane_specular);

			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, lane_diffuse);

			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, lane_shininess);
			
			break;
	}

	// set emission properties for all but the red/blue lights

	if (selection != 9 || selection != 10)
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black_emissive);

}
