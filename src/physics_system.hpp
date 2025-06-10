#ifndef physics_system_hpp
#define physics_system_hpp

#include <reactphysics3d/reactphysics3d.h>

struct RigidBody {
    rp3d::RigidBody* rigid_body;
};

class PhysicsSystem {
public:
    PhysicsSystem();
    void update();
private:
    rp3d::PhysicsCommon physics_common;
    rp3d::PhysicsWorld* physics_world;
    const double time_step = 1.0/60.0;
    long double previous_frame_time;
    long double frame_time_accumulator;
};

#endif
