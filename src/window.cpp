#include "window.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

Window :: Window () {}

void Window :: init() {
    if (init_glfw() != OK) return;
    if (init_glad() != OK) return;
    glViewport(0,0,800,600);
    glfwSetFramebufferSizeCallback(window, resize_callback);
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
}

EngineError Window :: init_glfw() {
    glfwInit();
    // set versions
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(800, 600, "Iron Engine", NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return ERROR;
    }
    glfwMakeContextCurrent(window);
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



window_size Window :: get_size() {
    window_size size;
    glfwGetWindowSize(window, &size.width, &size.height);
    return size;
}

GLFWwindow* Window :: get(){
    return window;
}
