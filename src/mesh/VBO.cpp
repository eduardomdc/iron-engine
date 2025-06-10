#include "VBO.hpp"
#include <glad/glad.h>
#include <iostream>

VBO::VBO (std::vector<Vertex>& vertices) {
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

void VBO::bind(){
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VBO::unbind(){
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::clear(){
    glDeleteBuffers(1, &id);
}

void print_vertices(std::vector<Vertex> &vertices) {
    for (int i = 0; i < vertices.size(); i ++ ){
        glm::vec3 pos = vertices[i].position;
        std::cout <<"["<<i<<"]"<<"x="<<pos.x<<" y="<<pos.y<<" z="<<pos.z<< std::endl;
    }
}
