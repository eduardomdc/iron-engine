#ifndef physics_system_hpp
#define physics_system_hpp

#include <reactphysics3d/collision/shapes/CollisionShape.h>
#include <reactphysics3d/mathematics/Vector3.h>
#include <reactphysics3d/reactphysics3d.h>

struct RigidBody {
    rp3d::RigidBody* rigid_body;
};

class PhysicsSystem {
public:
    PhysicsSystem();
    void update();
    rp3d::RigidBody* create_rigid_body(rp3d::Transform tf);
    rp3d::BoxShape* create_box_collider(rp3d::Vector3 h_extents);
private:
    rp3d::PhysicsCommon physics_common;
    rp3d::PhysicsWorld* physics_world;
    const double time_step = 1.0/60.0;
    long double previous_frame_time;
    long double frame_time_accumulator;
};

#endif
