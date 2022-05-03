#ifndef TINYGL_SHADER_H
#define TINYGL_SHADER_H

#include <glm/glm.hpp>
#include <iostream>

namespace Shaders
{
    std::string readShaderFromFile(const std::string &source);

    unsigned int createVertexShader(const char *source);

    unsigned int createFragmentShader(const char *source);

    unsigned int createShaderProgram(unsigned int vShader, unsigned int fShader);
};

class Shader
{
public:
    unsigned int ID;

    explicit Shader(const char* vertexPath,  const char* fragmentPath);
    ~Shader();
    void use() const;
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec3(const std::string &name, glm::vec3 vec) const;
    void setVec4(const std::string &name, glm::vec4 vec) const;
    void setMat4(const std::string &name, glm::mat4 mat) const;
};


#endif //TINYGL_SHADER_H
