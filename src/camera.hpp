#ifndef camera_hpp
#define camera_hpp

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Camera {
public:
    Camera(int width, int height, glm::vec3 position);
    void handle_inputs(GLFWwindow* window);
    void set_viewport(int width, int height);
    void mouse_callback(double x, double y);
    glm::mat4 transform() const;
private:
    int width, height;
    glm::vec3 position;
    glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    float FOVdeg = 60;
    float nearPlane = 0.1;
    float farPlane = 100;

    float base_speed = 0.1f;
    float sensitivity = 100.0f;

    bool first_mouse = false;
    float mouse_x, mouse_y, yaw, pitch;
};

#endif
