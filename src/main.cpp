#include "engine/iron-engine.hpp"
#include "entity_factory.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <reactphysics3d/components/RigidBodyComponents.h>

void test_physics () {
    for (int x = 0; x < 30; x++) {
        for (int y = 10; y < 13; y++) {
            for (int z = 0; z < 30; z++) {
                make_cuboid(glm::vec3(x,y,z), glm::vec3(.5, .5, .5), rp3d::BodyType::DYNAMIC);
            }
        }
    }
}

int main (){
    test_physics();
    //IronEngine::get().enable_collider_debug();
    //make_cuboid(glm::vec3(0,100,0), glm::vec3(1,1,1), rp3d::BodyType::DYNAMIC);
    make_cuboid(glm::vec3(0,0,0), glm::vec3(100,1,100), rp3d::BodyType::STATIC);
    while (IronEngine::get().is_running()) {
        IronEngine::get().update();
        IronEngine::get().render();
        IronEngine::get().handle_inputs();
    }
    IronEngine::get().clear();
    return 0;
}
