#ifndef _LIGHT_CONSTANTS_H_

#define _LIGHT_CONSTANTS_H_	



#include "gl/glut.h"


static const GLfloat black_diffuse[] = { 0.01, 0.01, 0.01, 1.0 };

static const GLfloat black_specular[] = { 0.01, 0.01, 0.01, 1.0 };

static const GLfloat black_shininess[] = { 0.0 };

static const GLfloat black_emissive[] = { 0.0, 0.0, 0.0, 1.0};


static const GLfloat white_diffuse[] = { 0.95, 0.95, 0.95, 1.0 };

static const GLfloat white_specular[] = { 1.0, 1.0, 1.0, 1.0 };

static const GLfloat white_shininess[] = { 40.0 };


static const GLfloat window_diffuse[] = { 0.0, 0.9, 0.9, 1.0 };

static const GLfloat window_specular[] = { 0.0, 1.0, 1.0, 1.0 };

static const GLfloat window_shininess[] = { 70.0 };


static const GLfloat red_diffuse[] = { 0.9, 0.0, 0.0, 1.0 };

static const GLfloat red_specular[] = { 1.0, 1.0, 1.0, 1.0 };

static const GLfloat red_shininess[] = { 70.0 };

static const GLfloat red_emissive[] = { 1.0, 0.0, 0.0, 1.0};


static const GLfloat blue_diffuse[] = { 0.0, 0.0, 0.9, 1.0 };

static const GLfloat blue_specular[] = { 1.0, 1.0, 1.0, 1.0 };

static const GLfloat blue_shininess[] = { 70.0 };

static const GLfloat blue_emissive[] = { 0.0, 0.0, 1.0, 1.0};


static const GLfloat skin1_diffuse[] = { 0.761, 0.565, 0.451, 1.0 };

static const GLfloat skin1_specular[] = { 0.761, 0.565, 0.451, 1.0 };

static const GLfloat skin1_shininess[] = { 0.0 };


static const GLfloat skin2_diffuse[] = { 0.431, 0.294, 0.118, 1.0 };

static const GLfloat skin2_specular[] = { 0.231, 0.094, 0.0, 1.0 };

static const GLfloat skin2_shininess[] = { 10.0 };


static const GLfloat shirt_diffuse[] = { 0.451, 0.757, 0.961, 1.0 };

static const GLfloat shirt_specular[] = { 0.5, 0.8, 1.0 };

static const GLfloat shirt_shininess[] = { 15.0 };


static const GLfloat belt_diffuse[] = { 0.4, 0.161, 0.059, 1.0 };

static const GLfloat belt_specular[] = { 0.45, 0.2, 0.1 };

static const GLfloat belt_shininess[] = { 10.0 };


static const GLfloat pants_diffuse[] = { 0.02, 0.004, 0.212, 1.0 };

static const GLfloat pants_specular[] = { 0.07, 0.054, 0.262 };

static const GLfloat pants_shininess[] = { 10.0 };


static const GLfloat bank1_diffuse[] = { 0.9, 0.9, 0.8, 1.0 };

static const GLfloat bank1_specular[] = { 0.95, 0.95, 0.85 };

static const GLfloat bank1_shininess[] = { 5.0 };


static const GLfloat bank2_diffuse[] = { 0.8, 0.8, 0.7, 1.0 };

static const GLfloat bank2_specular[] = { 0.85, 0.85, 0.75 };

static const GLfloat bank2_shininess[] = { 5.0 };


static const GLfloat blood_diffuse[] = { 0.95, 0.0, 0.0, 1.0 };

static const GLfloat blood_specular[] = { 1.0, 0.0, 0.0 };

static const GLfloat blood_shininess[] = { 33.0 };


static const GLfloat grass_diffuse[] = { 0.2, 0.8, 0.2, 1.0 };

static const GLfloat grass_specular[] = { 0.25, 0.85, 0.25 };

static const GLfloat grass_shininess[] = { 10.0 };


static const GLfloat road_diffuse[] = { 0.05, 0.05, 0.05, 1.0 };

static const GLfloat road_specular[] = { 0.1, 0.1, 0.1 };

static const GLfloat road_shininess[] = { 10.0 };


static const GLfloat lane_diffuse[] = { 0.9, 0.9, 0.0, 1.0 };

static const GLfloat lane_specular[] = { 1.0, 1.0, 0.0 };

static const GLfloat lane_shininess[] = { 20.0 };



void setMaterial(int selection);


#endif  // _LIGHT_CONSTANTS_H_