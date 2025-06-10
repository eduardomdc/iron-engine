#ifndef mesh_hpp
#define mesh_hpp

#include "VBO.hpp"
#include "VAO.hpp"
#include "EBO.hpp"
#include "../shader.hpp"
#include "../camera.hpp"
#include "../transform.hpp"

#include <glm/glm.hpp>
#include <vector>

struct Mesh {
    VAO vao;
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    void draw(const Shader& shader, const Camera& camera, const Transform& tf){
        shader.use(); 
        shader.set_mat4("camera", camera.transform());
        shader.set_mat4("model", tf.get_matrix());
        vao.bind();
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    }
    void make_mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices) {
        this->vertices = vertices;
        this->indices = indices;
        vao.bind();
        VBO vbo = VBO(vertices);
        EBO ebo = EBO(indices);
        vao.link_attrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
        vao.link_attrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
        vao.link_attrib(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
        vao.link_attrib(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
        vao.unbind();
        vbo.unbind();
        ebo.unbind();
    }
};

#endif
