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
Camera camera (mat4(1.0f));
float cameraSpeed = 5.f;

void framebuffer_resize_handler(GLFWwindow *window, int new_width, int new_height)
{
    glViewport(0, 0, new_width, new_height);
    camera.setAR((float)new_width/(float)new_height);
}

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

        camera.addPitch(yoffset);
        camera.addYaw(xoffset);
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

GLFWwindow *initialise_window()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 8);

    GLFWwindow* window = glfwCreateWindow(width, height, "tiny gl renderer :>", nullptr, nullptr);
    // Handle the window creation errors, yk the drill.
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    // Initialise GLAD before any GL functions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialise GLAD" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    // Initialise the OpenGL viewport
    glViewport(0, 0, width, height);

    return window;
}

void updateInput(GLFWwindow *window, float timeDelta)
{
    // Simple movement
    const float cameraSpeed = (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) ? 3.f*::cameraSpeed : ::cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.position += cameraSpeed * camera.direction * timeDelta;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.position -= cameraSpeed * camera.direction * timeDelta;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.position += normalize(cross(camera.direction, vec3(0, 1, 0))) * cameraSpeed * timeDelta;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.position -= normalize(cross(camera.direction, vec3(0, 1, 0))) * cameraSpeed * timeDelta;
    }

    // Zoom
    float zoom_speed = 100.f * timeDelta;
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        camera.setFOV(camera.fov-(float)(zoom_speed));
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        camera.setFOV(camera.fov+(float)(zoom_speed));
    }
}

void update(GLFWwindow *window)
{
    float timeDelta = (float)glfwGetTime() - lastUpdate;
    lastUpdate = (float)glfwGetTime();

    updateInput(window, timeDelta);
    cubes[0]->rotate(1.f, vec3(1, 1, 0));
}

void render()
{
    // Draw all cubes
    for(auto cube : cubes)
    {
        cube->draw();
    }
}


int main() {
    GLFWwindow *window = initialise_window();
    if (window == nullptr)
        return -1;

    // Set resize handler
    glfwSetFramebufferSizeCallback(window, framebuffer_resize_handler);

    // Set clear colour
    glClearColor(0.1f, 0.11f, 0.13f, 1.0f);

    // MSAA and Depth testing
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);

    // Set mouse handler
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouseHandler);
    glfwSetScrollCallback(window, scrollHandler);

    // Set key handler
    glfwSetKeyCallback(window, keyHandler);

    // Move camera backwards
    camera.position = vec3(0.0f, 0.0f, 3.0f);

    // Create some cubes
    Cube *cube1 = new Cube("textures/test.png", "shaders/frag/default.glsl", "shaders/vertex/default.glsl", &camera);
    Cube *cube2 = new Cube("textures/burlap.jpg", "shaders/frag/default.glsl", "shaders/vertex/default.glsl", &camera);
    Cube *cube3 = new Cube("textures/grass.bmp", "shaders/frag/default.glsl", "shaders/vertex/default.glsl", &camera);
    cubes.push_back(cube1);
    cubes.push_back(cube2);
    cubes.push_back(cube3);

    cube2->scale(vec3(.5));
    cube2->translate(vec3(4, 0, 0));

    cube3->scale(vec3(2));
    cube3->translate(vec3(-2, 0, 0));

    while (!glfwWindowShouldClose(window)) {
        update(window);

        // Clear the buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Update camera
        camera.update();

        // Render code
        render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
