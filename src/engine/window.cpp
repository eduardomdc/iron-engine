#include "window.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

Window :: Window () {}

void Window :: init() {
    if (init_glfw() != OK) return;
    if (init_glad() != OK) return;
    window_size ws = get_size();
    glViewport(0,0,ws.width,ws.height);
    glfwSetFramebufferSizeCallback(window, resize_callback);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    glEnable(GL_MULTISAMPLE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
}

EngineError Window :: init_glfw() {
    glfwInit();
    // set versions
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwSwapInterval(1); // v-sync
    window = glfwCreateWindow(1600, 800, "Iron Engine", NULL, NULL);
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
