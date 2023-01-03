#pragma once

#include <string>

#include "glad/glad.h"

#include "shader_interface.h"


class Shader: public IShader
{
public:

    Shader(const char* vertexPath, const char* fragmentPath);

    void use() const override;
    void disuse() const override;

    void setBool(const char* name, bool value) const override;
    void setInt(const char* name, int value) const override;
    void setFloat(const char* name, float value) const override;
    void setVec2(const char* name, const glm::vec2& value) const override;
    void setVec2(const char* name, float x, float y) const override;
    void setVec3(const char* name, const glm::vec3& value) const override;
    void setVec3(const char* name, float x, float y, float z) const override;
    void setVec4(const char* name, const glm::vec4& value) const override;
    void setVec4(const char* name, float x, float y, float z, float w) const override;
    void setMat2(const char* name, const glm::mat2& mat) const override;
    void setMat3(const char* name, const glm::mat3& mat) const override;
    void setMat4(const char* name, const glm::mat4& mat) const override;

    unsigned int getID() const override;

private:

    unsigned int ID;

private: 
    void checkCompileErrors(GLuint shader, std::string type);
};