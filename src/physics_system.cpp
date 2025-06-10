#include "physics_system.hpp"
#include <GLFW/glfw3.h>

PhysicsSystem::PhysicsSystem(){
    physics_world = physics_common.createPhysicsWorld();
}

void PhysicsSystem::update(){
    long double current_time = glfwGetTime();
    long double delta_time = current_time - previous_frame_time;
    frame_time_accumulator += delta_time;
    previous_frame_time = current_time;

    while (frame_time_accumulator >= time_step){
        physics_world->update(time_step);
        frame_time_accumulator -= time_step;
    }
}
