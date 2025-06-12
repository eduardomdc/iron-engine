#ifndef window_hpp
#define window_hpp

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "errors.hpp"

struct window_size {
    int width;
    int height;
};

class Window {
public:
    Window();
    void init();
    window_size get_size();
    GLFWwindow* get();
private:
    GLFWwindow* window;
    static void resize_callback(GLFWwindow* window, int width, int height);
    EngineError init_glfw();
    EngineError init_glad();
};

#endif
