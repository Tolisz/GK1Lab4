#include "main_loop.h"

#include "shader.h"
#include "object_platform.h"
#include "object_interface.h"
//#include "camera.h"

#include "global.h"

void mainLoopBody(GLFWwindow* window)
{
    Shader shader("src/shaders/def.vert", "src/shaders/def.frag");

    OPlatform test(1.0f);

    while (!glfwWindowShouldClose(window))
    {
        G::testowa_camerka.processKeyboard(window);

        // time logic
        float currentFrame = static_cast<float>(glfwGetTime());
        G::deltaTime = currentFrame - G::lastFrame;
        G::lastFrame = currentFrame;


        // rendering 
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = G::testowa_camerka.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);

        test.draw(shader, [&model, &view, &projection](const IShader& s) 
            {
                s.setMat4("model", model);
                s.setMat4("view", view);
                s.setMat4("projection", projection);
            }
        );
        
        //test.draw(shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}