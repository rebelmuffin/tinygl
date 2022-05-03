//
// Created by remuff on 5/2/22.
//

#include <glm/glm.hpp>

#ifndef TINYGL_CAMERA_H
#define TINYGL_CAMERA_H


class Camera {
    const float maxFOV = 110.0f;
    const float minFOV = 10.0f;

public:
    glm::mat4 transform;
    glm::mat4 projection;
    glm::vec3 position;
    glm::vec3 direction  = glm::vec3(0, 0, -1);
    float yaw = -90.f;
    float pitch = 0.0f;

    float aspect_ratio;
    float fov;
    Camera(glm::mat4 transform, float aspect_ratio=1.7f, float fov=90.f);
    void setFOV(float _fov);
    void setAR(float _aspect_ratio);
    void update();
    void addPitch(float pitch);
    void addYaw(float yaw);
};


#endif //TINYGL_CAMERA_H
