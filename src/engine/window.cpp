#include "window.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

Window :: Window () {
    open = false;
}

void Window :: init(WindowConfig config) {
    this->config = config;
    if (init_glfw() != OK) return;
    if (init_glad() != OK) return;
    
    glViewport(0,0,config.resolution.width,config.resolution.height);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    glEnable(GL_MULTISAMPLE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    open = true;
}

EngineError Window :: init_glfw() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x msaa
    if (config.vsync) glfwSwapInterval(1);
    if (config.window_mode == WindowMode::Resizable) {
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        glfwSetFramebufferSizeCallback(window, resize_callback);
    } else if (config.window_mode == WindowMode::FixedSize) {
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    }
    window = glfwCreateWindow(config.window_dimensions.width, config.window_dimensions.height, config.window_title, NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return ERROR;
    }
    glfwMakeContextCurrent(window);
    switch (config.cursor_mode) {
    case CursorMode::Captured:
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_CAPTURED); 
        break;
    case CursorMode::Disabled:
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
        break;
    case CursorMode::Hidden:
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN); 
        break;
    case CursorMode::Normal:
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); 
        break;
    }
    return OK;
}

EngineError Window :: init_glad() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return ERROR;
    }
    return OK;
}

void Window :: resize_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}



Dimensions Window :: get_window_size() {
    Dimensions size;
    glfwGetWindowSize(window, &size.width, &size.height);
    return size;
}

GLFWwindow* Window :: get(){
    return window;
}
