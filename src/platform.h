#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader_interface.h"

class Platform
{
public:
	
	// constructors & deconstructors
	Platform(const Platform&) = delete;
	Platform(const float& a, const float& y = 0);
	~Platform();

	// methods
	template<typename Func>
	void draw(const IShader& shader, Func shader_modifier);

	void draw(const IShader& shader);
		
private:

	// members
	float m_y;
	float m_a;

	// methods
	void init();
	void fill();

	// OpenGL 
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
};


template<class Func>
void Platform::draw(const IShader& shader, Func shader_modifier)
{
	shader.use();

	shader_modifier(shader);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	shader.disuse();
}