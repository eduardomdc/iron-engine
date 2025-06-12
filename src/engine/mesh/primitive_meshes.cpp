#include "primitive_meshes.hpp"
#include <glm/ext/matrix_transform.hpp>

MeshData create_cube_mesh() {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    indices.clear();

    glm::vec3 faceNormals[] = {
        { 0.0f,  0.0f,  1.0f}, // Front
        { 0.0f,  0.0f, -1.0f}, // Back
        {-1.0f,  0.0f,  0.0f}, // Left
        { 1.0f,  0.0f,  0.0f}, // Right
        { 0.0f,  1.0f,  0.0f}, // Top
        { 0.0f, -1.0f,  0.0f}  // Bottom
    };

    glm::vec3 faceColors[] = {
        {1, 0, 0}, // Front - Red
        {0, 1, 0}, // Back - Green
        {0, 0, 1}, // Left - Blue
        {1, 1, 0}, // Right - Yellow
        {1, 0, 1}, // Top - Magenta
        {0, 1, 1}  // Bottom - Cyan
    };

    glm::vec3 positions[6][4] = {
        // Front face
        {{-0.5f, -0.5f,  0.5f},
         { 0.5f, -0.5f,  0.5f},
         { 0.5f,  0.5f,  0.5f},
         {-0.5f,  0.5f,  0.5f}},
        // Back face
        {{ 0.5f, -0.5f, -0.5f},
         {-0.5f, -0.5f, -0.5f},
         {-0.5f,  0.5f, -0.5f},
         { 0.5f,  0.5f, -0.5f}},
        // Left face
        {{-0.5f, -0.5f, -0.5f},
         {-0.5f, -0.5f,  0.5f},
         {-0.5f,  0.5f,  0.5f},
         {-0.5f,  0.5f, -0.5f}},
        // Right face
        {{ 0.5f, -0.5f,  0.5f},
         { 0.5f, -0.5f, -0.5f},
         { 0.5f,  0.5f, -0.5f},
         { 0.5f,  0.5f,  0.5f}},
        // Top face
        {{-0.5f,  0.5f,  0.5f},
         { 0.5f,  0.5f,  0.5f},
         { 0.5f,  0.5f, -0.5f},
         {-0.5f,  0.5f, -0.5f}},
        // Bottom face
        {{-0.5f, -0.5f, -0.5f},
         { 0.5f, -0.5f, -0.5f},
         { 0.5f, -0.5f,  0.5f},
         {-0.5f, -0.5f,  0.5f}}
    };

    glm::vec2 uvs[4] = {
        {0.0f, 0.0f},
        {1.0f, 0.0f},
        {1.0f, 1.0f},
        {0.0f, 1.0f}
    };
    
    for (int face = 0; face < 6; ++face) {
        int baseIndex = vertices.size();
        for (int i = 0; i < 4; ++i) {
            Vertex v;
            v.position = positions[face][i];
            v.normal = faceNormals[face];
            v.color = faceColors[face];
            v.texUV = uvs[i];
            vertices.push_back(v);
        }

        // Two triangles per face
        indices.push_back(baseIndex + 0);
        indices.push_back(baseIndex + 1);
        indices.push_back(baseIndex + 2);

        indices.push_back(baseIndex + 2);
        indices.push_back(baseIndex + 3);
        indices.push_back(baseIndex + 0);
    }
    MeshData cube_data = {vertices, indices};
    return cube_data;
}
