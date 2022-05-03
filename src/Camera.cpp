//
// Created by remuff on 5/2/22.
//

#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

Camera::Camera(glm::mat4 _transform, float _aspect_ratio, float _fov)
{
    transform = _transform;
    aspect_ratio = _aspect_ratio;
    fov = _fov;
    projection = glm::perspective(glm::radians(fov), aspect_ratio, 0.1f, 100.0f);
}

void Camera::setFOV(float _fov)
{
    fov = _fov;

    // Clamp the value
    if (fov > maxFOV)
        fov = maxFOV;
    if (fov < minFOV)
        fov = minFOV;

    projection = glm::perspective(glm::radians(fov), aspect_ratio, 0.1f, 100.0f);
}

void Camera::setAR(float _aspect_ratio)
{
    aspect_ratio = _aspect_ratio;
    projection = glm::perspective(glm::radians(fov), aspect_ratio, 0.1f, 100.0f);
}

void Camera::update()
{
    direction.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    direction.y = glm::sin(glm::radians(pitch));
    direction.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    direction = glm::normalize(direction);
    transform = glm::lookAt(position, position+direction, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::addPitch(float _pitch)
{
    pitch += _pitch;

    // Clamp the value
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
}

void Camera::addYaw(float _yaw)
{
    yaw += _yaw;
}