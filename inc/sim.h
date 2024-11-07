#ifndef SIM_H
#define SIM_H

#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <string.h>

typedef struct	s_camera
{
	float	x, y, z;
	float	rotX, rotY;
}	t_camera;


typedef struct s_ball
{
    float x, y, z;    // Position
    float vx, vy, vz; // Velocity
    float ax, ay, az; // Acceleration
}	t_ball;

typedef struct	s_data
{
	GLFWwindow* win;
	t_camera cam;
	t_ball	ball;
}	t_data;

#endif