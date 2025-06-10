#ifndef vao_hpp
#define vao_hpp

#include <glad/glad.h>
#include "VBO.hpp"

class VAO {
public:
    VAO();
    uint32_t  id;
    void link_attrib(VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
    void bind();
    void unbind();
    void clear();
};

#endif
