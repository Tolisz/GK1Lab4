#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "model.h"

#include "object_camera.h"

class OModel
{
public:

	// constructors
	OModel(const char* path);

	// methods 
	//void cammeraAttach(OCamera* cam);

	template<typename Func>
	void draw(const IShader& shader, Func shader_modifier);


private:

	Model m_model;
	OCamera* m_camera;
};

template<class Func>
void OModel::draw(const IShader& shader, Func shader_modifier)
{
	shader.use();
	shader_modifier(shader);

	m_model.Draw(shader);

	shader.disuse();
}