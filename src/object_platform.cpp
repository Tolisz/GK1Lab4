#include "object_platform.h"

#include <iostream>

OPlatform::OPlatform(const float& a, const float& y) : m_a{ a }, m_y{ y }
{
	init();
	fill();
}

void OPlatform::init()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}

void OPlatform::fill()
{
	GLfloat vertices[] = {
		 m_a,  m_y, -m_a,	// 0 
		 m_a,  m_y,  m_a,   // 1
		-m_a,  m_y,  m_a,	// 2
		-m_a,  m_y, -m_a	// 3
	};

	GLuint indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void OPlatform::draw(const IShader& shader)
{
	shader.use();

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	shader.disuse();
}

OPlatform::~OPlatform()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}