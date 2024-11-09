#include "sim.h"

void	prop_exit(t_data *data ,int err)
{
    if (data->win)
        glfwDestroyWindow(data->win);
	
    glfwTerminate();
	exit(err);
}

void render_sphere()
{
    glColor4f(0.0, 0.5, 0.8, 0.15);  // Semi-transparent blue
    GLUquadric* quad = gluNewQuadric();
    gluSphere(quad, 5.0, 32, 32);  // Sphere with radius 1.0 and 32 slices/stacks
    gluDeleteQuadric(quad);
}

void draw_grid(float radius)
{
    int i, j;
    int slices = 32;  // Number of slices (latitude lines)
    int stacks = 32;  // Number of stacks (longitude lines)

    // Draw latitude lines (horizontal grid lines)
    glColor3f(0.6, 0.6, 0.6);
    for (i = -slices / 2; i <= slices / 2; i++) 
    {
        float lat = (i * M_PI / slices);  // Latitude angle

        glBegin(GL_LINE_LOOP);
        for (j = 0; j < stacks; j++) 
        {
            float lon = j * 2.0f * M_PI / stacks;  // Longitude angle
            float x = radius * cos(lat) * cos(lon);
            float y = radius * cos(lat) * sin(lon);
            float z = radius * sin(lat);
            glVertex3f(x, y, z);
        }
        glEnd();
    }

    // Draw longitude lines (vertical grid lines)
    for (i = 0; i < stacks; i++) 
    {
        float lon = i * 2.0f * M_PI / stacks;  // Longitude angle

        glBegin(GL_LINE_LOOP);
        for (j = -slices / 2; j <= slices / 2; j++) 
        {
            float lat = j * M_PI / slices;  // Latitude angle
            float x = radius * cos(lat) * cos(lon);
            float y = radius * cos(lat) * sin(lon);
            float z = radius * sin(lat);
            glVertex3f(x, y, z);
        }
        glEnd();
    }
}

void process_input(t_data *data)
{
    if (glfwGetKey(data->win, GLFW_KEY_W) == GLFW_PRESS)
        data->cam.y -= 0.1f;  // Move up along y-axis
    if (glfwGetKey(data->win, GLFW_KEY_S) == GLFW_PRESS)
        data->cam.y += 0.1f;  // Move down along y-axis
    if (glfwGetKey(data->win, GLFW_KEY_A) == GLFW_PRESS)
        data->cam.x += 0.1f;  // Move left along x-axis
    if (glfwGetKey(data->win, GLFW_KEY_D) == GLFW_PRESS)
        data->cam.x -= 0.1f;  // Move right along x-axis
    if (glfwGetKey(data->win, GLFW_KEY_X) == GLFW_PRESS)
        data->cam.z += 0.1f;  // Move forward along z-axis (away from the sphere)
    if (glfwGetKey(data->win, GLFW_KEY_C) == GLFW_PRESS)
        data->cam.z -= 0.1f;  // Move backward along z-axis (closer to the sphere)

    if (glfwGetKey(data->win, GLFW_KEY_LEFT) == GLFW_PRESS)
        data->cam.rotY -= 1.0f;  // Rotate left (yaw)
    if (glfwGetKey(data->win, GLFW_KEY_RIGHT) == GLFW_PRESS)
        data->cam.rotY += 1.0f;  // Rotate right (yaw)
    if (glfwGetKey(data->win, GLFW_KEY_UP) == GLFW_PRESS)
        data->cam.rotX -= 1.0f;  // Rotate up (pitch)
    if (glfwGetKey(data->win, GLFW_KEY_DOWN) == GLFW_PRESS)
        data->cam.rotX += 1.0f;  // Rotate down (pitch)
}

void render_fps(t_fps *fps)
{
    char fps_text[16];
    sprintf(fps_text, "FPS: %.2f", fps->fps);

    // Switch to orthogonal projection for 2D rendering
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 800, 600, 0, -1, 1);  // Orthogonal projection for text rendering (adjust width and height to match your window size)

    // Switch to modelview matrix to render the text
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2f(9, 20);
    for (int i = 0; fps_text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, fps_text[i]);

    // Restore previous depth test and projection settings
    glPopAttrib();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void fps_count(t_fps *fps)
{
    fps->current_time = glfwGetTime();
    fps->delta_time += fps->current_time - fps->last_time;
    fps->last_time = fps->current_time;
    fps->frame_count++;
    if (fps->delta_time > 1)
    {
        fps->fps = fps->frame_count / fps->delta_time;
        fps->frame_count = fps->delta_time = 0;
    }
}

int main(int ac, char **av)
{
    t_data data;

    if (init(&data, &ac, av))
        prop_exit(&data, 1);
    while (!glfwWindowShouldClose(data.win)) 
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();  // Reset modelview matrix
        fps_count(&data.fps);
        render_fps(&data.fps);
        process_input(&data);
        glTranslatef(data.cam.x, data.cam.y, data.cam.z);  // Move the sphere back so it's visible
        glRotatef(data.cam.rotX, 1.0f, 0.0f, 0.0f);  // Pitch: Rotate around x-axis
        glRotatef(data.cam.rotY, 0.0f, 1.0f, 0.0f);  // Yaw: Rotate around y-axis

        draw_grid(5);
        render_sphere();

        glfwSwapBuffers(data.win);
        glfwPollEvents();
    }
    glfwDestroyWindow(data.win);
    glfwTerminate();
	return (0);
}