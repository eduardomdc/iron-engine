#include "iron-engine.hpp"
#include <GLFW/glfw3.h>
#include <cstddef>
#include "mesh/mesh_manager.hpp"
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

void IronEngine :: test_entities () {
    Entity entity = create_entity();
    MeshData mesh_data = create_cube_mesh();
    Mesh mesh;
    mesh.make_mesh(mesh_data.vertices, mesh_data.indices);
    MeshID id = mesh_manager.add_mesh(mesh);
    MeshComponent meshc = {id};
    meshes.add(entity, meshc);
    Transform tf = {glm::vec3(0.0f), glm::quat(), glm::vec3(1.0f)}; 
    transforms.add(entity, tf);
}

Entity IronEngine :: create_entity () {
    return next_entity_id++;
}

void IronEngine :: render() {
    glfwSwapBuffers(window.get());
    glClearColor(0.2f, 0.5f, 0.5f, 1.0f);
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
        tf->position += glm::vec3(0.01, 0,0);
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
