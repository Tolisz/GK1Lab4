#include "main_loop.h"

#define STB_IMAGE_IMPLEMENTATION

#include "shader.h"
#include "object_platform.h"
#include "object_light.h"
#include "object_camera.h"
#include "object_model.h"

#include "global.h"

#include <iostream>

void mainLoopBody(GLFWwindow* window)
{
    initGlobal();

    Shader shader("shaders/def.vert", "shaders/def.frag");
    //Shader bag_shader("shaders/biplane.vert", "shaders/biplane.frag");

    OPlatform model_platform(5.0f);
    Shader shader_platform("shaders/platform.vert", "shaders/platform.frag");
    
    OModel model_plane("objects/biplane/biplane.obj");
    Shader shader_plane("shaders/biplane.vert", "shaders/biplane.frag");

    OModel model_kettle("objects/kettle/1.obj");
    Shader shader_kettle("shaders/biplane.vert", "shaders/biplane.frag");

    //OLight test_light(glm::vec3(1.0f, 1.0f, 1.0f), 0.0f, 0.0f, 0.0f);
    //Shader light_shader("shaders/light_source.vert", "shaders/light_source.frag");

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        //std::cout << *G::current_camera;

        G::current_camera->processKeyboard(window);

        // time logic
        float currentFrame = static_cast<float>(glfwGetTime());
        G::deltaTime = currentFrame - G::lastFrame;
        G::lastFrame = currentFrame;    

        // rendering 
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = G::current_camera->GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);

        model_platform.draw(shader_platform, [&view, &projection](const IShader& s)
            {
                glm::mat4 model = glm::mat4(1.0f);
                s.setMat4("model", model);
                s.setMat4("view", view);
                s.setMat4("projection", projection);
            }
        );

        model_plane.draw(shader_plane, [&view, &projection](const IShader& s)
            {
                float scale = 0.01f;
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::scale(model, glm::vec3(scale, scale, scale));

                float R = 3.0f;
                float time = (float)glfwGetTime() / 2;
                float x = sin(time) * R;
                float z = cos(time) * R;

                model = glm::translate(model, glm::vec3(x * (1 / scale), 0.0f, z * (1 / scale)));
                model = glm::rotate(model, time + glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

                s.setMat4("model", model);
                s.setMat4("view", view);
                s.setMat4("projection", projection);
            }
        );

        model_kettle.draw(shader_kettle, [&view, &projection](const IShader& s)
            {
                glm::mat4 model = glm::mat4(1.0f);

                float scale = 0.05f;
                model = glm::scale(model, glm::vec3(scale, scale, scale));
                model = glm::translate(model, glm::vec3(0.0f, 0.27f * (1 / scale), 0.0f));

                s.setMat4("model", model);
                s.setMat4("view", view);
                s.setMat4("projection", projection);
            }
        );




        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}


void initGlobal()
{
    //------------------------Camera------------------------
    //    Front = [0.706883, -0.45399, -0.542412]
    //    Up = [0.360174, 0.891007, -0.276372]
    //    Right = [0.608762, -0, 0.793353]
    //    Position = [-9.05762, 4.64883, 7.02102]
    //    WorldUp = [0, 1, 0]
    //    Pitch = -27
    //    Yaw = -37.5001
    //  

    // Nieruchoma i ruchoma
    {
        auto Position = glm::vec3(-7.66737, 5.16839, 7.68594);
        auto Up = glm::vec3(0.351076, 0.866026, -0.356013);
        auto Right = glm::vec3(0.608762, -0, 0.793353);
        auto Front = glm::vec3(0.706883, -0.45399, -0.542412);
        auto WorldUp = glm::vec3(0.0, 1.0, 0.0);
        float Pitch = -30;
        float Yaw = -45.4001;

        OCamera cam(Position, Front, Up, Right, WorldUp, Yaw, Pitch);
        
        cam.isMovable = false;
        G::cameras.insert(std::pair(1, cam));

        cam.isMovable = true;
        G::cameras.insert(std::pair(2, cam));

        G::current_camera = &G::cameras.at(1);
    }

    // Zaczepiona do obiektu (samolociku)
    {
        OCamera cam(glm::vec3(0.0f, 1.0f, 0.0f));
        cam.isMovable = false;
        G::cameras.insert(std::pair(3, cam));
    }
}
