#include "engine/iron-engine.hpp"
#include "entity_factory.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <reactphysics3d/components/RigidBodyComponents.h>

void test_physics () {
    for (int x = 0; x < 2; x++) {
        for (int y = 2; y < 20; y+=2) {
            for (int z = 0; z < 2; z++) {
                make_cuboid(glm::vec3(x,y,z), glm::vec3(.5, .5, .5), rp3d::BodyType::DYNAMIC);
            }
        }
    }
    make_cuboid(glm::vec3(0,0,0), glm::vec3(100,1,100), rp3d::BodyType::STATIC);
}

int main (){
    Iron().init();
    test_physics();
    while (Iron().is_running()) {
        Iron().update();
        Iron().render();
        Iron().handle_inputs();
    }
    Iron().clear();
    return 0;
}
