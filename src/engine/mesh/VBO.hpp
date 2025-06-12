#ifndef vbo_hpp
#define vbo_hpp

#include <cstdint>
#include <vector>
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;
    glm::vec2 texUV;
};

class VBO {
public:
    uint32_t id;
    VBO(const std::vector<Vertex>& vertices);
    void bind();
    void unbind();
    void clear();
};

void print_vertices(std::vector<Vertex>& vertices);

#endif
