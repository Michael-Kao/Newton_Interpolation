#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Window.h"
#include "Object.h"
#include "Shader.h"
#include "Camera.h"
#include "Line.h"
#include "Analytic.h"
#include "Newton.h"

class Application{
public:
    Application(Window *wnd_ptr);
    Application();
    ~Application();
    void run();
private:
    Window *m_window;
    Object *m_cube;
    Shader *m_shader;
    Shader *m_white;
    Camera *m_camera;
    Line *m_line;
    Analytical *m_origin;
    Newton *m_interpolation;
    void Init();
    void drawTest();
    void drawPlane();
    void drawOrigin();
    void NewtonTest();
    void processCamera(float delta_time);
    void processInput();
};