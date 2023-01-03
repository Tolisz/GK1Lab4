#include "callbacks.h"

#include "global.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (key == GLFW_KEY_V && action == GLFW_PRESS)
    {
        G::vibration = !G::vibration;
    }

    // Zmiana kamery
    if (key == GLFW_KEY_1 && action == GLFW_PRESS)
    {
        G::current_camera = &G::cameras.at(1);
    }
    if (key == GLFW_KEY_2 && action == GLFW_PRESS)
    {
        G::current_camera = &G::cameras.at(2);
    }
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    G::current_camera->processMouse(window, xpos, ypos);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}