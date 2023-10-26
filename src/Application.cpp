#include "Application.h"

Application::Application(Window *wnd_ptr)
    :   m_window(wnd_ptr) {
    Init();
}

Application::Application() {
    m_window = new Window();
    Init();
}

Application::~Application() {
    glfwTerminate();
}

void Application::Init() {
    // m_cube = new Object("assets/objfiles/cube.obj");
    std::cout << std::setprecision(15);
    m_shader = new Shader("assets/shaders/basic.vs", "assets/shaders/basic.fs");
    m_white = new Shader("assets/shaders/whitevs.glsl", "assets/shaders/whitefs.glsl");
    m_camera = new Camera();
    m_line = new Line();
    m_origin = new Analytical();
    m_interpolation = new Newton();
    NormCalc norm;
    norm.Norm2(m_origin, m_interpolation);
    // for(int i = 0; i < 6; i++) {
    //     norm.Norm2(m_origin, m_interpolation, i);
    // }
    norm.Norminf(m_origin, m_interpolation);
    // for(int i = 0; i < 6; i++) {
    //     norm.Norminf(m_origin, m_interpolation, i);
    // }
}

void Application::drawTest() {
    m_shader->bind();
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    // projection = glm::perspective(glm::radians(45.0f), (float)m_window->getWidth() / (float)m_window->getHeight(), 0.1f, 100.0f);
    // view       = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
    projection = glm::perspective(glm::radians(m_camera->fov), (float)m_window->getWidth() / (float)m_window->getHeight(), 0.1f, 100.0f);
    view       = m_camera->getLookAt();
    m_shader->setMat4("view", view);
    m_shader->setMat4("projection", projection);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1, 0, 0));
    m_shader->setMat4("model", model);
    // m_cube->draw();
    m_shader->unbind();
}

void Application::drawPlane() {
    m_white->bind();
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(m_camera->fov), (float)m_window->getWidth() / (float)m_window->getHeight(), 0.1f, 100.0f);
    view       = m_camera->getLookAt();
    m_white->setMat4("view", view);
    m_white->setMat4("projection", projection);
    { //model
        for (int i = -5; i < 6; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0.0, i, 0.0));
            m_white->setMat4("model", model);
            m_line->drawLine();
        }
        for (int i = -5; i < 6; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(i, 0.0, 0.0));
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
            m_white->setMat4("model", model);
            m_line->drawLine();
        }
    }
    m_white->unbind();
}

void Application::drawNewton() {
    m_shader->bind();
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(m_camera->fov), (float)m_window->getWidth() / (float)m_window->getHeight(), 0.1f, 100.0f);
    view       = m_camera->getLookAt();
    m_shader->setMat4("view", view);
    m_shader->setMat4("projection", projection);
    glm::mat4 model = glm::mat4(1.0f);
    m_shader->setMat4("model", model);
    // if(m_interpolation->NofCoef > 8)
        m_interpolation->draw();
    // for(int i = 0; i < 6; i++) {
    //     m_interpolation->draw(i);
    // }
    m_shader->unbind();
}

void Application::drawOrigin() {
    m_shader->bind();
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(m_camera->fov), (float)m_window->getWidth() / (float)m_window->getHeight(), 0.1f, 100.0f);
    view       = m_camera->getLookAt();
    m_shader->setMat4("view", view);
    m_shader->setMat4("projection", projection);
    glm::mat4 model = glm::mat4(1.0f);
    m_shader->setMat4("model", model);
    m_origin->draw();
    m_shader->unbind();
}

void Application::processCamera(float delta_time) {
    if(m_window->isPressed(GLFW_KEY_W)){
        m_camera->updateInput(FORWARD, delta_time);
    }
    if(m_window->isPressed(GLFW_KEY_S)){
        m_camera->updateInput(BACKWARD, delta_time);
    }
    if(m_window->isPressed(GLFW_KEY_A)){
        m_camera->updateInput(LEFT, delta_time);
    }
    if(m_window->isPressed(GLFW_KEY_D)){
        m_camera->updateInput(RIGHT, delta_time);
    }
    if(m_window->isPressed(GLFW_KEY_K)){
        m_camera->updateInput(RPITCH, delta_time);
    }
    if(m_window->isPressed(GLFW_KEY_J)){
        m_camera->updateInput(PITCH, delta_time);
    }
    if(m_window->isPressed(GLFW_KEY_L)){
        m_camera->updateInput(YAW, delta_time);
    }
    if(m_window->isPressed(GLFW_KEY_H)){
        m_camera->updateInput(RYAW, delta_time);
    }
}

void Application::processInput() {
    if(m_window->isPressed(GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(m_window->getWindow(), true);
    }
}

void Application::run() {
    // timing
    float deltaTime = 0.0f;	// time between current frame and last frame
    float lastFrame = 0.0f;
    while(!m_window->shouldClose()) {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // glViewport(0, 0, m_window->getWidth()/2, m_window->getHeight()/2);
        m_window->setClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        m_window->clear();

        processCamera(deltaTime);
        processInput();

        glViewport(0, 0, m_window->getWidth(), m_window->getHeight());
        if(0){
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            drawTest();
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        {
            drawPlane();
            drawNewton();
            // drawOrigin();
        }
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        // glViewport(0, 0, m_window->getWidth() / 2, m_window->getHeight() / 2);
        // drawTest();
        // glViewport(m_window->getWidth() / 2, m_window->getHeight() / 2, m_window->getWidth() / 2, m_window->getHeight() / 2);
        // drawTest();
        // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        // glViewport(m_window->getWidth() / 2, 0, m_window->getWidth() / 2, m_window->getHeight() / 2);
        // drawTest();
        // glViewport(0, m_window->getHeight() / 2, m_window->getWidth() / 2, m_window->getHeight() / 2);
        // drawTest();
        m_window->swapBuffers();
    }
}