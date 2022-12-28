#include "main_loop.h"

#include "shader.h"
#include "platform.h"
#include "camera.h"

#include <iostream>
#include <algorithm>

void mainLoopBody(GLFWwindow* window)
{
    Shader shader("src/shaders/def.vert", "src/shaders/def.frag");

    Platform test(1.0f);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //test.draw(shader, [](const IShader& s) {});
        test.draw(shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

