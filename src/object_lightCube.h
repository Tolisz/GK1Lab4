#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader_interface.h"

#include <glm/glm.hpp>

class OLightCube
{
public:

	OLightCube(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic);

	template<typename Func>
	void draw(const IShader& shader, Func shader_modifier);

	glm::vec3 position;
	glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f);

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	float constant;
	float linear;
	float quadratic;

	float cutOff = 12.5f;
	float outerCutOff = 12.6f;

private:

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	void init();
	void fill();
};

template<typename Func>
void OLightCube::draw(const IShader& shader, Func shader_modifier)
{
	shader.use();
	shader_modifier(shader);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	shader.disuse();
}