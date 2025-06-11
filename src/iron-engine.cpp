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
#include "mesh/primitive_meshes.hpp"
#include "transform.hpp"

IronEngine :: IronEngine () {
    window.init();
    test_shader = new(Shader)("../src/shaders/default.vert","../src/shaders/default.frag");
    test_entities();
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
}

void IronEngine::make_cube_at (glm::vec3 pos, MeshID mesh_id, rp3d::BodyType physics_type){
    Entity entity = create_entity();
    MeshComponent meshc = {mesh_id};
    meshes.add(entity, meshc);
    Transform tf = {pos, glm::quat(), glm::vec3(1.0f)}; 
    transforms.add(entity, tf);
    rp3d::Vector3 ppos(pos.x, pos.y, pos.z);
    rp3d::Quaternion ori = rp3d::Quaternion::identity();
    rp3d::Transform phys_tf(ppos, ori);
    rp3d::RigidBody* body = physics_system.create_rigid_body(phys_tf);
    body->setType(physics_type);
    body->addCollider(physics_system.create_box_collider(rp3d::Vector3(0.5, 0.5, 0.5)), rp3d::Transform::identity());
    rigid_bodies.add(entity, {body});
}

void IronEngine :: test_entities () {
    MeshData mesh_data = create_cube_mesh();
    Mesh mesh;
    mesh.make_mesh(mesh_data.vertices, mesh_data.indices);
    MeshID id = mesh_manager.add_mesh(mesh);
    make_cube_at(glm::vec3(0,0,0), id, rp3d::BodyType::STATIC);
    make_cube_at(glm::vec3(0,100,0), id, rp3d::BodyType::DYNAMIC);
}

Entity IronEngine :: create_entity () {
    return next_entity_id++;
}

void IronEngine :: update() {
    double current_time = glfwGetTime();
    double delta_time = current_time - last_frame;
    last_frame = current_time;
    accumulator += delta_time;
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
        tf->rotation = glm::quat(ori.x, ori.y, ori.z, ori.w);
    }
}

void IronEngine :: render() {
    glfwSwapBuffers(window.get());
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    render_entities();
}

void IronEngine :: render_entities() {
    std::vector<MeshComponent>& all_meshes = meshes.all();
    auto& entities = meshes.entities();
    for (size_t i = 0; i < all_meshes.size(); i++) {
        Entity entity = entities[i];
        Transform* tf = transforms.get(entity);
        if (!tf) continue; // don't render entities without transform
        MeshComponent& mesh_c = all_meshes[i];
        Mesh* mesh = mesh_manager.get_mesh(mesh_c.mesh_id);
        mesh->draw(*test_shader, camera, *tf);
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
