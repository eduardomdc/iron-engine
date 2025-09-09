#include "engine/iron-engine.hpp"
#include "entity_factory.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <reactphysics3d/components/RigidBodyComponents.h>

int main (){
    make_cuboid(glm::vec3(0,100,0), glm::vec3(1,1,1), rp3d::BodyType::DYNAMIC);
    make_cuboid(glm::vec3(0,0,0), glm::vec3(100,1,100), rp3d::BodyType::STATIC);
    IronEngine::get().enable_collider_debug();
    while (IronEngine::get().is_running()) {
        IronEngine::get().update();
        IronEngine::get().render();
        IronEngine::get().handle_inputs();
    }
    IronEngine::get().clear();
    return 0;
}
