//
// Created by remuff on 5/2/22.
//

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Cube.h"

using namespace glm;


void setUpVertices(unsigned int &VAO, unsigned int &VBO, unsigned int &EBO)
{
    // There are duplicates, needs more optimisation
    float vertices[] = {
            0, 0, 0, 0, 0,
            0, 1, 0, 0, 1,
            1, 0, 0, 1, 0,
            1, 1, 0, 1, 1,

            0, 0, 1, 0, 0,
            0, 1, 1, 0,1,
            0, 0, 0, 1, 0,
            0, 1, 0, 1, 1,

            1, 0, 0, 0, 0,
            1, 1, 0, 0, 1,
            1, 0, 1, 1, 0,
            1, 1, 1, 1, 1,

            0, 0, 1, 0, 0,
            0, 1, 1, 0, 1,
            1, 0, 1, 1, 0,
            1, 1, 1, 1, 1,

            1, 0, 0, 0, 0,
            0, 0, 0, 0, 1,
            1, 0, 1, 1, 0,
            0, 0, 1, 1, 1,

            1, 1, 0, 0, 0,
            0, 1, 0, 0, 1,
            1, 1, 1, 1, 0,
            0, 1, 1, 1, 1
    };
    unsigned int indices[] = {
            0, 1, 2,
            1, 3, 2,

            4, 5, 6,
            5, 7, 6,

            8, 9, 10,
            9, 11, 10,

            12, 13, 14,
            13, 15, 14,

            16, 17, 18,
            17, 19, 18,

            20, 21, 22,
            21, 23, 22,

            24, 25, 26,
            25, 27, 26
    };

    // Create array object
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create vertex buffer
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create element buffer
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}


Cube::Cube(const char *textureFile, const char *fShader, const char *vShader, Camera *_camera)
{
    texture = new Texture(textureFile);
    shader = new Shader(vShader, fShader);
    camera = _camera;
    transform = mat4(1.0f);

    setUpVertices(VAO, VBO, EBO);
}

Cube::~Cube()
= default;

void Cube::draw()
{
    // Set texture and shader to be used
    texture->use();
    shader->use();

    // Set world information
    shader->setMat4("view", camera->transform);
    shader->setMat4("projection", camera->projection);
    shader->setMat4("transform", transform);

    // Bind VAO, VBO and EBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // Explain to OpenGL how we represent the data in memory
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 5 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 5 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glDrawElements(GL_TRIANGLES, 40, GL_UNSIGNED_INT, nullptr);
}

void Cube::translate(glm::vec3 translation)
{
    transform = glm::translate(transform, translation);
}

void Cube::rotate(float degrees, glm::vec3 multiplier)
{
    transform = glm::rotate(transform, radians(degrees), multiplier);
}

void Cube::scale(glm::vec3 scale)
{
    transform = glm::scale(transform, scale);
}
