#ifndef iron_engine_hpp
#define iron_engine_hpp

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "camera.hpp"
#include "light.hpp"
#include "physics_system.hpp"
#include "window.hpp"
#include "shader.hpp"
#include "component_manager.hpp"
#include "transform.hpp"
#include "mesh/mesh_manager.hpp"
#include "event_manager.hpp"
#include "texture.hpp"

class IronEngine {
public:
    static IronEngine& get() { // singleton
        static IronEngine instance;
        return instance;
    }
    void render();
    void update();
    void render_entities();
    void handle_inputs();
    bool is_running();
    void clear();

    void enable_collider_debug();
    void disable_collider_debug();

    Entity create_entity();
    EventManager event_manager;
    ComponentManager<Transform> transforms;
    ComponentManager<MeshComponent> meshes;
    ComponentManager<RigidBody> rigid_bodies;
    PhysicsSystem physics_system;
private:
    IronEngine();// only by get
    IronEngine(const IronEngine&) = delete; // no copy
    IronEngine& operator = (const IronEngine&) = delete; // no assignments
    const double fps = 60.0;
    const double frame_time = 1/fps;
    const double max_physics_frame_time = 0.25;
    double last_frame, accumulator;
    Entity next_entity_id = 1;
    Window window;
    Camera camera = Camera(800,600,{0,0,0});
    Shader default_shader;
    Shader collider_shader;
    MeshManager mesh_manager;
    Texture uv_texture;
    PointLight test_light;

    bool collider_debug_mode;
};

void gl_resize_callback(GLFWwindow* window, int width, int height);
void gl_mouse_move_callback(GLFWwindow* window, double xpos, double ypos); 

#endif
