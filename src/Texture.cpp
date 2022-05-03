//
// Created by remuff on 5/2/22.
//

#include <glad/glad.h>
#include <iostream>
#include "stb_image.h"
#include "Texture.h"


unsigned int createTexture(unsigned char* textureData, int width, int height)
{
    unsigned int texture;

    // Generate GL texture
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    return texture;
}

unsigned char *loadTexture(const char *source, int *width, int *height, int *nrChannels)
{
    unsigned char *data = stbi_load(source, width, height, nrChannels, 0);
    if (!data) {
        std::cout << "Failed to load Texture: " << source << std::endl;
    }
    return data;
}

Texture::Texture(const char *source)
{
    int width, height, nrChannels;
    unsigned char *textureData = loadTexture(source, &width, &height, &nrChannels);

    // Create OpenGL texture object
    ID = createTexture(textureData, width, height);

    // Free the memory allocated for texture data
    stbi_image_free(textureData);
}

Texture::~Texture()
{
    glDeleteTextures(1, &ID);
}

void Texture::use() const
{
    glBindTexture(GL_TEXTURE_2D, ID);
}
