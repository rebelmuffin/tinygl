//
// Created by remuff on 5/5/22.
//

#ifndef TINYGL_SCENE_H
#define TINYGL_SCENE_H

#include <memory>
#include <GLFW/glfw3.h>
#include <vector>
#include "Camera.h"
#include "Cube.h"

class Scene
{
private:
    // Configuration variables
    bool showCursor = false;
    bool allowInput = true;

    // Objects
    GLFWwindow *window;
public:
    GLFWwindow *getWindow() const;

private:
    Camera *camera;
public:
    Camera *getCamera() const;

private:
    std::vector<std::shared_ptr<Cube>> objects;

    static GLFWwindow* createWindow(int width, int height, const char *title);
    void render();

    static void resizeHandler(GLFWwindow *window, int width, int height);
public:
    Scene(int width, int height, const char *title);
    ~Scene();

    void update();

    void resizeWindow(int width, int height);
    void addObject(const std::shared_ptr<Cube>& object);

    template <class T, typename... Args> std::shared_ptr<T> createObject(Args... args);
};


#endif //TINYGL_SCENE_H
