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
}			t_camera;

typedef struct	s_fps
{
	double	delta_time, last_time,  current_time;
    int		frame_count;
    float	fps;
}			t_fps;

typedef struct s_ball
{
    float	x, y, z;    // Position
    float	vx, vy, vz; // Velocity
    float	ax, ay, az; // Acceleration
}			t_ball;

typedef struct	s_data
{
	GLFWwindow*	win;
	t_camera	cam;
	t_ball		ball;
	t_fps		fps;
}				t_data;

int init(t_data *data, int *ac, char **av);

// void 	setup_opengl();
// void    init_fps(t_fps *fps);
// void    init_camera(t_camera *cam);

#endif