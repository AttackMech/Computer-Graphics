Computer Graphics

Here are 4 assignments and a final project that I completed for the COMP390 - Computer Graphics course for Athabasca University. I programmed these in C++ using Visual Studio using modern graphics techniques, models and algorithms to solve the problems.

I used the freeglut library for the openGL libraries.  Note that if you decide to run each program, you will need to change the location of the included and linked files in the project properties to match the location of the freeglut files.  You will also need to place the freeglut.h file in the project directory or include it from some other location.


Projects

Each project can be run in Visual Studio using the solution file.  Each directory also contains an image of the expected output.
(TME stands for Tutor Marked Exercise)

TME 1 - 2D Graphics

	Program 1 - Anti-aliasing

		This program creates two images of a house, built from a triange and a square, the second house uses an anti-aliasing technique to smooth the "jaggies" seen in the first image.

	Program 2 - 2D Graphics Transformation

		This program creates a series of houses using triangles and squares, the same as in Program 1. The middle house is the standard house, and each house to the left or right of the middle house is placed in position using a transformation process (translation and rotation).

	Program 3 - Colouring and Shading

		This program creates a simple 2D square. Each vertex is set to a different colour. In clockwise order from the top left it should be green, blue, yellow, red.


TME 2 - 3D Graphics

	Program 1 - Object Modeling

		This program creates a 3D version of the house seen in TME 1. The "ground" is a simple rectangle, the "body" is a cube made of 6 squares, and the "roof" a pyramid consisting of 4 triangles (without a base). The model is rendered as a wireframe.

	Program 2 - Transformation and Projection

		Based on the model in Program 1, a scene of 8 houses is created using translation, scaling, and rotation to transform the houses.


TME 3 - Lighting and Surface Textures
	
	Program 1 - Lightinge Elements and Surface Materials

		This program creates a sphere with OpenGL lighing features. There are 3 light sources top left, top right, and directly behind the viewer. Each light source can emit white, red, blue, or green light. Each light can also be turned off. There are also 3 different surface materials available: gold, silver, and copper. The lighting effects can also be changed to display different values: ambient, ambient and diffuse, and ambient, diffuse and specular. There is a menu available to choose each value using a right click on the mouse. If the value does not change with the selection, simply left click on the image and the changes should be noticeable.

	Program 2 - Calculating Specular Contribution

		This program shows the specular contribution to the lighting model. It displays a simple square and you can see the specular reflection in the top right corner.

	Program 3 - Textures

		This program takes the same housing models from TME 2 - Program 2 and adds a texture to simulate a background image. The texture image is mapped to the sides of the cube surrounding the "ground" in the image.


TME 4 - Ray Tracing

	Program 1 - Recursive Reflection

		This program implements a recrursive ray tracing algorithm that casts a ray from the source to the scene. If the ray hits the red wall, the ray terminates returning the colour of the wall.. If the ray hits the reflective ground surface, the method recursively invokes itself with the reflection ray, and returns a mixed colour. In this way, the reflection on the floor is created.

	Program 2 - Shadows

		Based on Program 1, this program creates a reflective surface but the object now also casts a shadow. This is done to by checking to see if the intersection point on the floor can see the light source or not.  If not, the shadow colour is displayed by mixing with the floor's local colour.


Final Project

	The final project applies the techniques learned in the previous assignments. There were 3 options to choose from, and I chose option 1. This option was to create a scene consisting of a textured background, at least 5 composite objects made up of at least 5 geometric shapes, 2 light sources of different colours, and an atmospheric attenuation effect.

	My project scene is supposed to be a bank robbery.  There are 2 bank robbers, one standing with his hands up and one lying on the floor dead. There is a police officer pointing his gun at the robbers. There is the bank building, and finally, there is a police car with flashing red and blue lights. The background is textured with a city scene, and the atmospheric attenuation makes the scene seem a little foggy.

	Note that when running the program, you can use the mouse right-click to bring up a menu to rotate the scene.




*** ALL CODE CREATED BY JASON BISHOP. IF YOU WISH TO COPY OR USE THESE FILES IN ANY WAY, PLEAS ASK PERMISSION ***