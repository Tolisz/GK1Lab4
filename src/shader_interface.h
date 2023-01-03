#pragma once

#include "glm/glm.hpp"

class IShader
{
public:

	virtual void use() const = 0;
	virtual void disuse() const = 0;

    virtual void setBool(const char* name, bool value) const = 0;
    virtual void setInt(const char* name, int value) const = 0;
    virtual void setFloat(const char* name, float value) const = 0;
    virtual void setVec2(const char* name, const glm::vec2& value) const = 0;
    virtual void setVec2(const char* name, float x, float y) const = 0;
    virtual void setVec3(const char* name, const glm::vec3& value) const = 0;
    virtual void setVec3(const char* name, float x, float y, float z) const = 0;
    virtual void setVec4(const char* name, const glm::vec4& value) const = 0;
    virtual void setVec4(const char* name, float x, float y, float z, float w) const = 0;
    virtual void setMat2(const char* name, const glm::mat2& mat) const = 0;
    virtual void setMat3(const char* name, const glm::mat3& mat) const = 0;
    virtual void setMat4(const char* name, const glm::mat4& mat) const = 0;

    virtual unsigned int getID() const = 0;
};