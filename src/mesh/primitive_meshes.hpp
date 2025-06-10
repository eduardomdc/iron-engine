#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "VBO.hpp"

struct MeshData {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
};

MeshData create_cube_mesh();
