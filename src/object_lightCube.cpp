#include "object_lightCube.h"


OLightCube::OLightCube(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic)
	: position{ position }, ambient{ ambient }, diffuse{ diffuse }, specular{ specular }, constant{ constant }, linear{ linear }, quadratic{quadratic}
{
	init();
	fill();
}

void OLightCube::init()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
}

void OLightCube::fill()
{
    float vertices[] = {
        // positions          // normals         
        -0.02f, -0.02f, -0.02f,  0.0f,  0.0f, -1.0f,
         0.02f, -0.02f, -0.02f,  0.0f,  0.0f, -1.0f,
         0.02f,  0.02f, -0.02f,  0.0f,  0.0f, -1.0f,
         0.02f,  0.02f, -0.02f,  0.0f,  0.0f, -1.0f,
        -0.02f,  0.02f, -0.02f,  0.0f,  0.0f, -1.0f,
        -0.02f, -0.02f, -0.02f,  0.0f,  0.0f, -1.0f,

        -0.02f, -0.02f,  0.02f,  0.0f,  0.0f,  1.0f,
         0.02f, -0.02f,  0.02f,  0.0f,  0.0f,  1.0f,
         0.02f,  0.02f,  0.02f,  0.0f,  0.0f,  1.0f,
         0.02f,  0.02f,  0.02f,  0.0f,  0.0f,  1.0f,
        -0.02f,  0.02f,  0.02f,  0.0f,  0.0f,  1.0f,
        -0.02f, -0.02f,  0.02f,  0.0f,  0.0f,  1.0f,

        -0.02f,  0.02f,  0.02f, -1.0f,  0.0f,  0.0f,
        -0.02f,  0.02f, -0.02f, -1.0f,  0.0f,  0.0f,
        -0.02f, -0.02f, -0.02f, -1.0f,  0.0f,  0.0f,
        -0.02f, -0.02f, -0.02f, -1.0f,  0.0f,  0.0f,
        -0.02f, -0.02f,  0.02f, -1.0f,  0.0f,  0.0f,
        -0.02f,  0.02f,  0.02f, -1.0f,  0.0f,  0.0f,

         0.02f,  0.02f,  0.02f,  1.0f,  0.0f,  0.0f,
         0.02f,  0.02f, -0.02f,  1.0f,  0.0f,  0.0f,
         0.02f, -0.02f, -0.02f,  1.0f,  0.0f,  0.0f,
         0.02f, -0.02f, -0.02f,  1.0f,  0.0f,  0.0f,
         0.02f, -0.02f,  0.02f,  1.0f,  0.0f,  0.0f,
         0.02f,  0.02f,  0.02f,  1.0f,  0.0f,  0.0f,

        -0.02f, -0.02f, -0.02f,  0.0f, -1.0f,  0.0f,
         0.02f, -0.02f, -0.02f,  0.0f, -1.0f,  0.0f,
         0.02f, -0.02f,  0.02f,  0.0f, -1.0f,  0.0f,
         0.02f, -0.02f,  0.02f,  0.0f, -1.0f,  0.0f,
        -0.02f, -0.02f,  0.02f,  0.0f, -1.0f,  0.0f,
        -0.02f, -0.02f, -0.02f,  0.0f, -1.0f,  0.0f,

        -0.02f,  0.02f, -0.02f,  0.0f,  1.0f,  0.0f,
         0.02f,  0.02f, -0.02f,  0.0f,  1.0f,  0.0f,
         0.02f,  0.02f,  0.02f,  0.0f,  1.0f,  0.0f,
         0.02f,  0.02f,  0.02f,  0.0f,  1.0f,  0.0f,
        -0.02f,  0.02f,  0.02f,  0.0f,  1.0f,  0.0f, 
        -0.02f,  0.02f, -0.02f,  0.0f,  1.0f,  0.0f 
    };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, VAO);
    glBindVertexArray(0);
}