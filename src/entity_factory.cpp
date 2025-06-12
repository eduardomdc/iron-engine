#include "entity_factory.hpp"
#include "engine/iron-engine.hpp"
#include "engine/mesh/primitive_meshes.hpp"

Entity make_cuboid(glm::vec3 position, glm::vec3 dimensions, rp3d::BodyType body_type){
    Entity entity = IronEngine::get().create_entity();
    // mesh
    MeshComponent meshc = {PrimitiveMeshes::CUBE};
    IronEngine::get().meshes.add(entity, meshc);
    // tf
    Transform tf = {position, glm::quat(0,0,0,1), dimensions}; 
    IronEngine::get().transforms.add(entity, tf);
    // rigid body
    rp3d::Vector3 ppos(position.x, position.y, position.z);
    rp3d::Quaternion ori = rp3d::Quaternion::identity();
    rp3d::Transform phys_tf(ppos, ori);
    rp3d::RigidBody* body = IronEngine::get().physics_system.create_rigid_body(phys_tf);
    body->setType(body_type);
    body->addCollider(IronEngine::get().physics_system.create_box_collider(rp3d::Vector3(dimensions.x/2, dimensions.y/2, dimensions.z/2)), rp3d::Transform::identity());
    IronEngine::get().rigid_bodies.add(entity, {body});

    return entity;
}
