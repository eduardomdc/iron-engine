#include "physics_system.hpp"
#include <GLFW/glfw3.h>
#include <reactphysics3d/body/RigidBody.h>
#include <reactphysics3d/collision/shapes/CollisionShape.h>
#include <reactphysics3d/mathematics/Transform.h>
#include <reactphysics3d/mathematics/Vector3.h>

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

rp3d::RigidBody* PhysicsSystem::create_rigid_body(rp3d::Transform tf){
    return physics_world->createRigidBody(tf);
}

rp3d::BoxShape* PhysicsSystem::create_box_collider(rp3d::Vector3 h_extents){
    return physics_common.createBoxShape(h_extents);
}
