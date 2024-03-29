﻿#include "main_loop.h"

#define STB_IMAGE_IMPLEMENTATION

#include "shader.h"
#include "object_platform.h"
#include "object_camera.h"
#include "object_model.h"
#include "object_lightCube.h"

#include "global.h"

#include <iostream>

void mainLoopBody(GLFWwindow* window)
{
    initGlobal();

    //OLightCube TEST(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.8f, 0.8f, 0.8f), 0.0f, 0.0f, 0.0f);
    Shader shader_lightCube("shaders/light_source.vert", "shaders/light_source.frag");

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


    //          Różne inne parametry
    // ---------------------------------------------

    // Drgania samolociku 

    float rate = 100.0f;         // Sybkość drgania samolocika
    float max_angle = 6.0f;     // Maksymalne odchylenie samolocika
    float alpha = 0.0f;



    // ---------------------------------------------


    while (!glfwWindowShouldClose(window))
    {
        G::current_camera->processKeyboard(window);
        
        // śledzimy za samolocikiem
        if (G::current_camera->hasTarget)
        {
            float R = 3.0f;
            float speed = 2.0f;      // Im większa wartość, tym wolniej samolocik się porusza.
            float time = (float)glfwGetTime() / speed;
            float x = sin(time) * R;
            float z = cos(time) * R;

            G::current_camera->setTarget(glm::vec3(x, 0.0f, z));
        }

        // Kamera znajdująca się za samolocikiem
        if (G::current_camera == &G::cameras.at(4))
        {
            float R = 3.0f;
            float speed = 2.0f;      // Im większa wartość, tym wolniej samolocik się porusza.
            float time = ((float)glfwGetTime());

            float time_target = time / speed;
            float time_position = (time - 4.0f) / speed;

            float x_pos = sin(time_position) * R;
            float z_pos = cos(time_position) * R;

            float x_target = sin(time_target) * R;
            float z_target = cos(time_target) * R;

            G::current_camera->setPosition(glm::vec3(x_pos, 1.0f, z_pos));
            G::current_camera->setTarget(glm::vec3(x_target, 0.5f, z_target));
        }

        if (G::current_camera == &G::cameras.at(2))
        {
            G::light_cubes.at(3).position = G::current_camera->GetPosition();
            G::light_cubes.at(3).direction = G::current_camera->GetFront();
        }

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

        // Light parametrs
        float speed = 8.0f;      // Im większa wartość, tym wolniej samolocik się porusza.
        float time = (float)glfwGetTime() / speed;
        float y = sin(time);
        float z = cos(time);

        G::light_cubes.at(1).position = glm::vec3(0.0f, 6 * y, 6 * z);
        G::light_cubes.at(1).direction = glm::vec3(0.0f, 0.0f, 0.0f) - glm::vec3(0.0f, y, z);

        G::light_cubes.at(1).draw(shader_lightCube, [&view, &projection](const IShader& s)
            {
                // Set model, view, specular matrices

                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, G::light_cubes.at(1).position);
                s.setMat4("model", model);
                s.setMat4("view", view);
                s.setMat4("projection", projection);
            }
        );

        G::light_cubes.at(2).draw(shader_lightCube, [&view, &projection](const IShader& s)
            {
                // Set model, view, specular matrices

                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, G::light_cubes.at(2).position);
                s.setMat4("model", model);
                s.setMat4("view", view);
                s.setMat4("projection", projection);
            }
        );


        G::light_cubes.at(3).draw(shader_lightCube, [&view, &projection](const IShader& s)
            {
                // Set model, view, specular matrices

                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, G::light_cubes.at(3).position);
                s.setMat4("model", model);
                s.setMat4("view", view);
                s.setMat4("projection", projection);
            }
        );




        model_platform.draw(shader_platform, [&view, &projection](const IShader& s)
            {
                // Set Light parametrs

                s.setVec3("day_light.direction", G::light_cubes.at(1).direction);
                s.setVec3("day_light.ambient", G::light_cubes.at(1).ambient);
                s.setVec3("day_light.diffuse", G::light_cubes.at(1).diffuse);
                s.setVec3("day_light.specular", G::light_cubes.at(1).specular);

                s.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
                s.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
                //s.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
                s.setVec3("material.specular", 0.0f, 0.0f, 0.0f);
                s.setFloat("material.shininess", 32.0f);


                // Point Light

                s.setVec3("point_light.position", G::light_cubes.at(2).position);
                s.setVec3("point_light.ambient", G::light_cubes.at(2).ambient);
                s.setVec3("point_light.diffuse", G::light_cubes.at(2).diffuse);
                s.setVec3("point_light.specular", G::light_cubes.at(2).specular);

                s.setFloat("point_light.constant", G::light_cubes.at(2).constant);
                s.setFloat("point_light.linear", G::light_cubes.at(2).linear);
                s.setFloat("point_light.quadratic", G::light_cubes.at(2).quadratic);

                // Latarka

                s.setVec3("latarka.position", G::light_cubes.at(3).position);
                s.setVec3("latarka.direction", G::light_cubes.at(3).direction);

                s.setVec3("latarka.ambient", G::light_cubes.at(3).ambient);
                s.setVec3("latarka.diffuse", G::light_cubes.at(3).diffuse);
                s.setVec3("latarka.specular", G::light_cubes.at(3).specular);

                s.setFloat("latarka.constant", G::light_cubes.at(3).constant);
                s.setFloat("latarka.linear", G::light_cubes.at(3).linear);
                s.setFloat("latarka.quadratic", G::light_cubes.at(3).quadratic);
                s.setFloat("latarka.cutOff", G::light_cubes.at(3).cutOff);
                s.setFloat("latarka.outerCutOff", G::light_cubes.at(3).outerCutOff);


                s.setVec3("Normal", glm::vec3(0.0f, 1.0f, 0.0f));

                // Set model, view, specular matrices

                glm::mat4 model = glm::mat4(1.0f);
                s.setMat4("model", model);
                s.setMat4("view", view);
                s.setMat4("projection", projection);
            }
        );

        model_plane.draw(shader_plane, [&view, &projection, &alpha, &max_angle, &rate](const IShader& s)
            {
                // Set Light parametrs

                s.setVec3("day_light.direction", G::light_cubes.at(1).direction);
                s.setVec3("day_light.ambient", G::light_cubes.at(1).ambient);
                s.setVec3("day_light.diffuse", G::light_cubes.at(1).diffuse);
                s.setVec3("day_light.specular", G::light_cubes.at(1).specular);

                s.setVec3("viewPos", G::current_camera->GetPosition());


                // Point light

                s.setVec3("point_light.position", G::light_cubes.at(2).position);
                s.setVec3("point_light.ambient", G::light_cubes.at(2).ambient);
                s.setVec3("point_light.diffuse", G::light_cubes.at(2).diffuse);
                s.setVec3("point_light.specular", G::light_cubes.at(2).specular);

                s.setFloat("point_light.constant", G::light_cubes.at(2).constant);
                s.setFloat("point_light.linear", G::light_cubes.at(2).linear);
                s.setFloat("point_light.quadratic", G::light_cubes.at(2).quadratic);

                // Latarka

                s.setVec3("latarka.position", G::light_cubes.at(3).position);
                s.setVec3("latarka.direction", G::light_cubes.at(3).direction);

                s.setVec3("latarka.ambient", G::light_cubes.at(3).ambient);
                s.setVec3("latarka.diffuse", G::light_cubes.at(3).diffuse);
                s.setVec3("latarka.specular", G::light_cubes.at(3).specular);

                s.setFloat("latarka.constant", G::light_cubes.at(3).constant);
                s.setFloat("latarka.linear", G::light_cubes.at(3).linear);
                s.setFloat("latarka.quadratic", G::light_cubes.at(3).quadratic);
                s.setFloat("latarka.cutOff", G::light_cubes.at(3).cutOff);
                s.setFloat("latarka.outerCutOff", G::light_cubes.at(3).outerCutOff);

                // Set model, view, specular matrices

                float scale = 0.01f;
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::scale(model, glm::vec3(scale, scale, scale));

                float R = 3.0f;
                float speed = 2.0f;      // Im większa wartość, tym wolniej samolocik się porusza.
                float time = (float)glfwGetTime() / speed;
                float x = sin(time) * R;
                float z = cos(time) * R;

                model = glm::translate(model, glm::vec3(x * (1 / scale), 0.0f, z * (1 / scale)));
                if (G::vibration)
                {
                    //std::cout << time << std::endl;
                    alpha = max_angle * (sin(rate * time));
                }
                model = glm::rotate(model, glm::radians(alpha), glm::vec3(-z, 0.0f, x));
                model = glm::rotate(model, time + glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));


                s.setMat4("model", model);
                s.setMat4("view", view);
                s.setMat4("projection", projection);
            }
        );

        model_kettle.draw(shader_kettle, [&view, &projection](const IShader& s)
            {
                // Set Light parametrs
                
                s.setVec3("day_light.direction", G::light_cubes.at(1).direction);
                s.setVec3("day_light.ambient", G::light_cubes.at(1).ambient);
                s.setVec3("day_light.diffuse", G::light_cubes.at(1).diffuse);
                s.setVec3("day_light.specular", G::light_cubes.at(1).specular);

                s.setVec3("viewPos", G::current_camera->GetPosition());

                // Point light

                s.setVec3("point_light.position", G::light_cubes.at(2).position);
                s.setVec3("point_light.ambient", G::light_cubes.at(2).ambient);
                s.setVec3("point_light.diffuse", G::light_cubes.at(2).diffuse);
                s.setVec3("point_light.specular", G::light_cubes.at(2).specular);

                s.setFloat("point_light.constant", G::light_cubes.at(2).constant);
                s.setFloat("point_light.linear", G::light_cubes.at(2).linear);
                s.setFloat("point_light.quadratic", G::light_cubes.at(2).quadratic);

                // Latarka

                s.setVec3("latarka.position", G::light_cubes.at(3).position);
                s.setVec3("latarka.direction", G::light_cubes.at(3).direction);

                s.setVec3("latarka.ambient", G::light_cubes.at(3).ambient);
                s.setVec3("latarka.diffuse", G::light_cubes.at(3).diffuse);
                s.setVec3("latarka.specular", G::light_cubes.at(3).specular);

                s.setFloat("latarka.constant", G::light_cubes.at(3).constant);
                s.setFloat("latarka.linear", G::light_cubes.at(3).linear);
                s.setFloat("latarka.quadratic", G::light_cubes.at(3).quadratic);
                s.setFloat("latarka.cutOff", G::light_cubes.at(3).cutOff);
                s.setFloat("latarka.outerCutOff", G::light_cubes.at(3).outerCutOff);

                // Set model, view, specular matrices

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
    // Nieruchoma i ruchoma kamera
    {
        auto Position = glm::vec3(-7.66737, 5.16839, 7.68594);
        auto Up = glm::vec3(0.351076, 0.866026, -0.356013);
        auto Right = glm::vec3(0.608762, -0, 0.793353);
        auto Front = glm::vec3(0.706883, -0.45399, -0.542412);
        auto WorldUp = glm::vec3(0.0, 1.0, 0.0);
        float Pitch = -30.0f;
        float Yaw = -45.4001f;

        OCamera cam(Position, Front, Up, Right, WorldUp, Yaw, Pitch);
        
        cam.isMovable = false;
        G::cameras.insert(std::pair(1, cam));

        cam.isMovable = true;
        G::cameras.insert(std::pair(2, cam));

        G::current_camera = &G::cameras.at(1);
    }

    // Kamera śledząca za obiektem
    {
        auto Position = glm::vec3(-8.12361, 4.14735, -1.413115);
        auto Up = glm::vec3(0.473769, 0.880478, 0.0173718);
        auto Right = glm::vec3(-0.0366425, 0, 0.999328);
        auto Front = glm::vec3(0.706883, -0.45399, -0.542412);
        auto WorldUp = glm::vec3(0.0, 1.0, 0.0);
        float Pitch = -28.3f;
        float Yaw = 2.09993f;

        OCamera cam(Position, Front, Up, Right, WorldUp, Yaw, Pitch);
        cam.isMovable = false;
        cam.hasTarget = true;
        G::cameras.insert(std::pair(3, cam));
    }

    // Kamera zaczepiona do obiektu
    {
        OCamera cam(glm::vec3(0.0f, 0.0f, 0.0f));
        G::cameras.insert(std::pair(4, cam));
    }




    // ---------------
    // Źródła światła 
    // ---------------

    // Światło dzień/noc
    {
        OLightCube light(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.8f, 0.8f, 0.8f), 0.0f, 0.0f, 0.0f);
        G::light_cubes.insert(std::pair(1, light));
    }

    // Światło nieruchome
    {
        OLightCube Pointlight(glm::vec3(-6.0f, 2.0f, -6.0f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.8f, 0.8f, 0.8f), 1.0f, 0.09f, 0.032f);
        G::light_cubes.insert(std::pair(2, Pointlight));
    }

    // Światło w postaci latarki powiązane z ruchomą kamerą
    {
        OLightCube latarka(G::cameras.at(2).GetPosition(), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.8f, 0.8f, 0.8f), 1.0f, 0.09f, 0.032f);
        G::light_cubes.insert(std::pair(3, latarka));
    }
}