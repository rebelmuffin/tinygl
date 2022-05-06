// Created by Selim bakirci
// 05/05/2022

#include <glm/glm.hpp>
#include <glad/glad.h>
#include "Scene.h"


Scene::Scene(int width, int height, const char *title)
{
    // Create window
    window = createWindow(width, height, title);

    // Set user pointer to this
    glfwSetWindowUserPointer(window, this);

    // Set resize handler
    glfwSetFramebufferSizeCallback(window, resizeHandler);

    // Set clear colour
    glClearColor(0.1f, 0.11f, 0.13f, 1.0f);

    // MSAA and Depth testing
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);

    // Create camera
    camera = new Camera(glm::mat4(1.0f));
    camera->position = glm::vec3(0.0f, 0.0f, 3.0f);
}

Scene::~Scene()
{
    glfwTerminate();
}

GLFWwindow* Scene::createWindow(int width, int height, const char *title)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 8);

    GLFWwindow *newWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
    // Handle the window creation errors, yk the drill.
    if (newWindow == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        throw std::runtime_error("Creating GLFW window failed.");
    }

    glfwMakeContextCurrent(newWindow);

    // Initialise GLAD before any GL functions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialise GLAD" << std::endl;
        glfwTerminate();
        throw std::runtime_error("Initialising GLAD failed. Check if OpenGL is present.");
    }

    // Initialise the OpenGL viewport
    glViewport(0, 0, width, height);

    return newWindow;
}

void Scene::render()
{
    // Clear the buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(const auto& object : objects) {
        object->draw();
    }

    glfwSwapBuffers(window);
}

void Scene::update()
{
    // Update camera
    camera->update();

    // Render scene
    render();

    glfwPollEvents();
}

void Scene::resizeWindow(int width, int height)
{
    glViewport(0, 0, width, height);
    camera->setAR((float)width/(float)height);
}

void Scene::resizeHandler(GLFWwindow *window, int width, int height)
{
    auto *scene = static_cast<Scene*>(glfwGetWindowUserPointer(window));
    scene->resizeWindow(width, height);
}

template<class T, typename... Args>
std::shared_ptr<T> Scene::createObject(Args... args)
{
    auto object = std::static_pointer_cast<Cube>(std::make_shared<T>(args...));
    this->objects.push_back(std::move(object));
}

GLFWwindow *Scene::getWindow() const
{
    return window;
}

void Scene::addObject(const std::shared_ptr<Cube>& object)
{
    objects.push_back(object);
}

Camera *Scene::getCamera() const {
    return camera;
}


