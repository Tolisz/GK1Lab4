#pragma once

#include "shader_interface.h"

class IObject 
{
public:

	virtual void draw(const IShader& shader) = 0;
};