#include <iostream>
#include <array>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <map>
#include <vector>

#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Cube.h"
#include "Scene.h"


using namespace glm;


// General runtime config
bool wireframeEnabled = false;
bool cursorShown = false;
bool inputAllowed = false;

// Keeping track of objects
std::vector<Cube*> cubes;

// Window constants
const int width = 800;
const int height = 600;

// Direction values
float lastX = 400, lastY = 300;

// Keep track of time
float lastUpdate = 0.0f;

// Camera values
Camera *camera;
float cameraSpeed = 5.f;

void keyHandler(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
    {
        cursorShown = !cursorShown;
        glfwSetInputMode(window, GLFW_CURSOR, cursorShown ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
    }
    if (key == GLFW_KEY_M && action == GLFW_RELEASE)
    {
        wireframeEnabled = !wireframeEnabled;
        glPolygonMode(GL_FRONT_AND_BACK, wireframeEnabled ? GL_LINE : GL_FILL);
    }
}

void mouseHandler(GLFWwindow *window, double xpos, double ypos)
{
    if (inputAllowed) {
        auto xoffset = (float) (xpos - lastX);
        auto yoffset = (float) (lastY - ypos);
        lastX = (float) xpos;
        lastY = (float) ypos;

        const float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        camera->addPitch(yoffset);
        camera->addYaw(xoffset);
    } else {
        inputAllowed = true;
        lastX = (float) xpos;
        lastY = (float) ypos;
    }
}

void scrollHandler(GLFWwindow *window, double xoffset, double yoffset)
{
    if (inputAllowed)
    {
        cameraSpeed += (float)(cameraSpeed*.05*yoffset);

        cameraSpeed = clamp(cameraSpeed, 1.0f, 50.0f);
    }
}

void updateInput(GLFWwindow *window, float timeDelta)
{
    // Simple movement
    const float cameraSpeed = (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) ? 3.f*::cameraSpeed : ::cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera->position += cameraSpeed * camera->direction * timeDelta;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera->position -= cameraSpeed * camera->direction * timeDelta;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera->position += normalize(cross(camera->direction, vec3(0, 1, 0))) * cameraSpeed * timeDelta;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera->position -= normalize(cross(camera->direction, vec3(0, 1, 0))) * cameraSpeed * timeDelta;
    }

    // Zoom
    float zoom_speed = 100.f * timeDelta;
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        camera->setFOV(camera->fov-(float)(zoom_speed));
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        camera->setFOV(camera->fov+(float)(zoom_speed));
    }
}


int main() {
    Scene scene(800, 600, "Hello GL!");

    GLFWwindow *window = scene.getWindow();
    camera = scene.getCamera();

    // Set key handlers
    glfwSetKeyCallback(window, keyHandler);
    glfwSetScrollCallback(window, scrollHandler);
    glfwSetCursorPosCallback(window, mouseHandler);

    // Create some objects
    std::shared_ptr<Cube> cube1 = std::make_shared<Cube>("textures/test.png", "shaders/frag/default.glsl", "shaders/vertex/default.glsl", camera);
    scene.addObject(cube1);
    std::shared_ptr<Cube> cube2 = std::make_shared<Cube>("textures/grass.bmp", "shaders/frag/default.glsl", "shaders/vertex/default.glsl", camera);
    scene.addObject(cube2);
    std::shared_ptr<Cube> cube3 = std::make_shared<Cube>("textures/burlap.jpg", "shaders/frag/default.glsl", "shaders/vertex/default.glsl", camera);
    scene.addObject(cube3);

    // Set cursor state
    glfwSetInputMode(window, GLFW_CURSOR, cursorShown ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);

    // Move cubes
    cube2->translate(vec3(2, 2, 0));
    cube3->translate(vec3(-2, 2, 0));

    while (!glfwWindowShouldClose(window)) {
        float timeDelta = (float)glfwGetTime() - lastUpdate;
        lastUpdate = (float)glfwGetTime();

        scene.update();
        updateInput(window, timeDelta);
    }
}
