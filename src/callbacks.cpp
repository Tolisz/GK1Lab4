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

    static bool ShadingChange = false;

    // Zmiana kamery
    if (!ShadingChange && key >= GLFW_KEY_1 && key <= GLFW_KEY_9)
    {
        G::current_camera = &G::cameras.at(key - GLFW_KEY_1 + 1);
    }
    else if (ShadingChange && key >= GLFW_KEY_1 && key <= GLFW_KEY_9)
    {
        ShadingChange = false;
        std::uint8_t shading = static_cast<std::uint8_t>(key - GLFW_KEY_1 + 1);
        G::shading = shading > 2 ? 2 : shading;
    }

    if (key == GLFW_KEY_P)
    {
        ShadingChange = true;
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