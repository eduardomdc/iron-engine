#include "iron-engine.hpp"
#include <GLFW/glfw3.h>
#include <cstddef>
#include <reactphysics3d/body/RigidBody.h>
#include <reactphysics3d/components/RigidBodyComponents.h>
#include <reactphysics3d/mathematics/Quaternion.h>
#include <reactphysics3d/mathematics/Transform.h>
#include <reactphysics3d/mathematics/Vector3.h>
#include "component_manager.hpp"
#include "mesh/mesh_manager.hpp"
#include "physics_system.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "transform.hpp"

IronEngine :: IronEngine () {
    window.init();
    default_shader = Shader::load("../src/engine/shaders/default.vert","../src/engine/shaders/default.frag");
    collider_shader = Shader::load("../src/engine/shaders/default.vert", "../src/engine/shaders/collider.frag");
    glfwSetCursorPosCallback(window.get(), gl_mouse_move_callback);
    glfwSetWindowSizeCallback(window.get(), gl_resize_callback);
    event_manager.register_resize_callback(
    [&](int w, int h){
        camera.set_viewport(w,h);
    });
    event_manager.register_mouse_move_callback(
    [&](double x, double y) {
        camera.mouse_callback(x, y);
    }
    );
    mesh_manager.setup();
    uv_texture = Texture::load("../assets/textures/uv_map.png");
}

Entity IronEngine :: create_entity () {
    return next_entity_id++;
}

void IronEngine :: update() {
    double current_time = glfwGetTime();
    double delta_time = current_time - last_frame;
    last_frame = current_time;
    accumulator += std::min(delta_time, max_physics_frame_time);
    while (accumulator >= frame_time){
        physics_system.update();
        accumulator -= frame_time;
    }
    // update tf's of every entity that has a RigidBody
    auto& all_bodies = rigid_bodies.all();
    auto& entities = rigid_bodies.entities();
    for (size_t i = 0; i < all_bodies.size(); i++){
        Entity entity = entities[i];
        Transform* tf = transforms.get(entity);
        if (!tf) continue;
        rp3d::RigidBody* rb = all_bodies[i].rigid_body;
        rp3d::Transform physics_tf = rb->getTransform();
        rp3d::Vector3 pos = physics_tf.getPosition(); 
        rp3d::Quaternion ori = physics_tf.getOrientation();
        tf->position = glm::vec3(pos.x, pos.y, pos.z);
        tf->rotation = glm::quat(ori.w, ori.x, ori.y, ori.z);
    }
}

void IronEngine :: render() {
    glfwSwapBuffers(window.get());
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    render_entities();
}

void IronEngine :: render_entities() {
    glBindTexture(GL_TEXTURE_2D, uv_texture.id); //bind uv tex temporary
    std::vector<MeshComponent>& all_meshes = meshes.all();
    auto& entities = meshes.entities();
    for (size_t i = 0; i < all_meshes.size(); i++) {
        Entity entity = entities[i];
        Transform* tf = transforms.get(entity);
        if (!tf) continue; // don't render entities without transform
        MeshComponent& mesh_c = all_meshes[i];
        Mesh* mesh = mesh_manager.get_mesh(mesh_c.mesh_id);
        mesh->draw(default_shader, camera, *tf);
        if (collider_debug_mode) {
            rp3d::RigidBody* rb = rigid_bodies.get(entity)->rigid_body; 
            if (!rb) continue;
            Transform collider_tf;
            rp3d::Transform physics_tf = rb->getTransform();
            rp3d::Vector3 pos = physics_tf.getPosition(); 
            rp3d::Quaternion ori = physics_tf.getOrientation();
            collider_tf.position = glm::vec3(pos.x, pos.y, pos.z);
            collider_tf.rotation = glm::quat(ori.z, ori.y, ori.x, ori.w);
            collider_tf.scale = tf->scale;
            mesh->draw(collider_shader, camera, collider_tf);
        }
    }
}

void IronEngine :: handle_inputs() {
   glfwPollEvents();
   if (glfwGetKey(window.get(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
       glfwSetWindowShouldClose(window.get(), true);
   }
   camera.handle_inputs(window.get());
}

bool IronEngine :: is_running() {
    return !glfwWindowShouldClose(window.get());
}

void IronEngine :: clear() {
    glfwTerminate();
}

void gl_resize_callback(GLFWwindow* window, int width, int height){
    IronEngine::get().event_manager.trigger_resize(width, height);    
}

void gl_mouse_move_callback(GLFWwindow* window, double xpos, double ypos){
    IronEngine::get().event_manager.trigger_mouse_move(xpos, ypos);
}

void IronEngine :: enable_collider_debug(){
    collider_debug_mode = true;
}
void IronEngine :: disable_collider_debug(){
    collider_debug_mode = false;
}
