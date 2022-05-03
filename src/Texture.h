//
// Created by remuff on 5/2/22.
//

#ifndef TINYGL_TEXTURE_H
#define TINYGL_TEXTURE_H


class Texture
{
public:
    unsigned int ID;

    explicit Texture(const char *source);
    ~Texture();
    void use() const;
};


#endif //TINYGL_TEXTURE_H
