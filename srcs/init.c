#include "sim.h"

void    init_camera(t_camera *cam);
void    init_fps(t_fps *fps);
void    setup_opengl();

int init(t_data *data, int *ac, char **av)
{
	int width, height;

    bzero(data, sizeof(t_data));
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
		return (1);
    }
	data->win = glfwCreateWindow(800, 600, "Particle Simulation", NULL, NULL);
	if (!data->win) {
        fprintf(stderr, "Failed to create GLFW window\n");
		return (1);
    }
    glutInit(ac, av);
	glfwMakeContextCurrent(data->win);
	glfwGetFramebufferSize(data->win, &width, &height);
	glViewport(0, 0, width, height);
    setup_opengl();
    init_camera(&data->cam);
    init_fps(&data->fps);
    return (0);
}

void    init_camera(t_camera *cam)
{
    cam->x = 0.0f;
    cam->y = .0f;
    cam->z = -20.0f;
    cam->rotX = 90.0f;
    cam->rotY = 0.0f;
}

void    init_fps(t_fps *fps)
{
    bzero(fps, sizeof(t_fps));
    fps->last_time = glfwGetTime();
}

void    setup_opengl()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.8, 0.8, 0.8, 1.0);
    // Set up projection matrix for perspective
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 800.0 / 600.0, 0.1, 100.0);  // FOV = 45°, aspect ratio = width/height, near/far planes

    // Switch to modelview matrix for object transformations
    glMatrixMode(GL_MODELVIEW);
}