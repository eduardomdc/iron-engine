#ifndef entity_factory_hpp
#define entity_factory_hpp

#include "engine/entity.hpp"
#include <reactphysics3d/reactphysics3d.h>
#include <glm/glm.hpp>

Entity make_cuboid(glm::vec3 position, glm::vec3 dimensions, rp3d::BodyType body_type);

#endif
