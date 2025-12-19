#ifndef window_hpp
#define window_hpp

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "errors.hpp"

struct Dimensions {
    int width;
    int height;
};

enum class WindowMode {
    Resizable,
    FixedSize,
    Fullscreen,
};

enum class CursorMode {
    Normal,
    Hidden,
    Disabled,
    Captured,
};

struct WindowConfig {
    Dimensions window_dimensions = {640,480};
    Dimensions resolution = {640,480};
    WindowMode window_mode = WindowMode::FixedSize;
    CursorMode cursor_mode = CursorMode::Normal;
    const char* window_title = "Iron Engine";
    bool vsync = true;
};

class Window {
public:
    Window();
    void init(WindowConfig config);
    Dimensions get_window_size();
    GLFWwindow* get();
    bool open;
private:
    WindowConfig config;
    GLFWwindow* window;
    static void resize_callback(GLFWwindow* window, int width, int height);
    EngineError init_glfw();
    EngineError init_glad();
};

#endif
