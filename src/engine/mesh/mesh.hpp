#ifndef mesh_hpp
#define mesh_hpp

#include "VBO.hpp"
#include "VAO.hpp"
#include "../shader.hpp"
#include "../camera.hpp"
#include "../transform.hpp"

#include <glm/glm.hpp>
#include <vector>

class Mesh {
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices);
    VAO vao;
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    void draw(const Shader& shader, const Camera& camera, const Transform& tf);
};

#endif
