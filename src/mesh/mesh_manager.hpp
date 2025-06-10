#ifndef mesh_manager_hpp
#define mesh_manager_hpp

#include <cstdint>
#include <unordered_map>
#include "mesh.hpp"

using MeshID = uint32_t;

struct MeshComponent {
    MeshID mesh_id;
};

class MeshManager {
public:
    MeshID add_mesh(const Mesh& mesh) {
        MeshID id = next_id++;
        meshes[id] = mesh;
        return id;
    }

    Mesh* get_mesh(MeshID id){
        auto it = meshes.find(id);
        if (it != meshes.end()) return &it->second;
        return nullptr;
    }
private:
    MeshID next_id = 1;
    std::unordered_map<MeshID, Mesh> meshes;
};

#endif
