#include "mesh_manager.hpp"
#include "primitive_meshes.hpp"

void MeshManager :: setup(){
    create_primitive_meshes();
}

void MeshManager :: create_primitive_meshes() {
    MeshData cube_mesh = create_cube_mesh();
    add_mesh(cube_mesh);
}
