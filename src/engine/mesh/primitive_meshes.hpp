#ifndef primitive_meshes_hpp
#define primitive_meshes_hpp
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "mesh_manager.hpp"

enum PrimitiveMeshes {
    CUBE=1,
    LEN,
};


MeshData create_cube_mesh();

#endif
