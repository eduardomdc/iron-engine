#ifndef mesh_manager_hpp
#define mesh_manager_hpp

#include <cstdint>
#include <unordered_map>
#include "mesh.hpp"

using MeshID = uint32_t;

struct MeshData {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
};

struct MeshComponent {
    MeshID mesh_id;
};

class MeshManager {
public:
    void setup();
    MeshID add_mesh(const MeshData& mesh_data) {
        MeshID id = next_id++;
        meshes.insert_or_assign(id,Mesh(mesh_data.vertices, mesh_data.indices));
        return id;
    }

    Mesh* get_mesh(MeshID id){
        auto it = meshes.find(id);
        if (it != meshes.end()) return &it->second;
        return nullptr;
    }
private:
    void create_primitive_meshes();
    MeshID next_id = 1;
    std::unordered_map<MeshID, Mesh> meshes;
};

#endif
