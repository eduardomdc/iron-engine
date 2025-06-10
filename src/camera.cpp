#include "camera.hpp"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(int width, int height, glm::vec3 position){
    set_viewport(width, height);
    this->position = position;
}

void Camera::set_viewport(int width, int height){
    this->width = width;
    this->height = height;
    mouse_x = (float)width/2;
    mouse_y = (float)height/2;
}

glm::mat4 Camera::transform() const {
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);
    view = glm::lookAt(position, position+front, up);
    proj = glm::perspective(glm::radians(FOVdeg), (float)width/height, nearPlane, farPlane);
    return proj * view;
}

void Camera::handle_inputs(GLFWwindow* window){
   const float cam_speed = 0.05f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        position += cam_speed * front;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        position -= cam_speed * front;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        position -= glm::normalize(glm::cross(front, up)) * cam_speed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        position += glm::normalize(glm::cross(front, up)) * cam_speed;
}

void Camera :: mouse_callback(double xpos, double ypos){
    if (first_mouse)
    {
        mouse_x = xpos;
        mouse_y = ypos;
        first_mouse = false;
    }
  
    float xoffset = xpos - mouse_x;
    float yoffset = mouse_y - ypos; 
    mouse_x = xpos;
    mouse_y = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(direction); 
}
