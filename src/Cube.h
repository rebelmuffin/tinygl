// Selim Bakirci
// 02/05/2022
#ifndef TINYGL_CUBE_H
#define TINYGL_CUBE_H

#include <glm/glm.hpp>
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"


class Cube
{
private:
    unsigned int VAO, VBO, EBO;
    Texture *texture;
    Shader *shader;
    Camera *camera;

public:
    glm::mat4 transform;
    Cube(const char *textureFile, const char *fShader, const char *vShader, Camera *camera);
    ~Cube();
    virtual void draw();

    void scale(glm::vec3 scale);
    void rotate(float degrees, glm::vec3 multiplier);
    void translate(glm::vec3 translation);
};


#endif //TINYGL_CUBE_H
