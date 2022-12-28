#include "main_loop.h"

#include "shader.h"
#include "object_platform.h"
#include "object_interface.h"
//#include "camera.h"
#include "model.h"

#include "global.h"


void mainLoopBody(GLFWwindow* window)
{
    Shader shader("shaders/def.vert", "shaders/def.frag");
    Shader bag_shader("shaders/biplane.vert", "shaders/biplane.frag");

    OPlatform test(4.0f);

    Model ourModel("objects/biplane/biplane.obj");

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        G::testowa_camerka.processKeyboard(window);

        // time logic
        float currentFrame = static_cast<float>(glfwGetTime());
        G::deltaTime = currentFrame - G::lastFrame;
        G::lastFrame = currentFrame;    

        // rendering 
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
        
        bag_shader.use();
        
        float scale = 0.01f;
        model = glm::scale(model, glm::vec3(scale, scale, scale));
        //model = glm::rotate(model, (float)glfwGetTime() / 2, glm::vec3(0.0, 1.0, 0.0));
        //model = glm::translate(model, glm::vec3(5.0f * (1 / scale), 0.0f, 5.0f * (1/scale)));
        //model = glm::rotate(model, (float)glfwGetTime() / 2, glm::vec3(0.0, 1.0, 0.0));
        bag_shader.setMat4("model", model);
        bag_shader.setMat4("view", view);
        bag_shader.setMat4("projection", projection);
        
        ourModel.Draw(bag_shader);

        //test.draw(shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}