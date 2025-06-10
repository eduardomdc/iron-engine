#ifndef iron_engine_hpp
#define iron_engine_hpp

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "camera.hpp"
#include "window.hpp"
#include "shader.hpp"
#include "component_manager.hpp"
#include "transform.hpp"
#include "mesh/mesh_manager.hpp"
#include "event_manager.hpp"

class IronEngine {
public:
    static IronEngine& get() { // singleton
        static IronEngine instance;
        return instance;
    }
    void render();
    void render_entities();
    void handle_inputs();
    bool is_running();
    void clear();
    Entity create_entity();
    void test_entities();
    EventManager event_manager;
private:
    IronEngine();// only by get
    IronEngine(const IronEngine&) = delete; // no copy
    IronEngine& operator = (const IronEngine&) = delete; // no assignments
    Entity next_entity_id = 1;
    Window window;
    Camera camera = Camera(800,600,{0,0,0});
    Shader* test_shader;
    MeshManager mesh_manager;
    ComponentManager<Transform> transforms;
    ComponentManager<MeshComponent> meshes;
};

void gl_resize_callback(GLFWwindow* window, int width, int height);
void gl_mouse_move_callback(GLFWwindow* window, double xpos, double ypos); 

#endif
