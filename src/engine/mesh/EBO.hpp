#ifndef ebo_hpp
#define ebo_hpp

#include <glad/glad.h>
#include <vector>

class EBO {
public:
    EBO(const std::vector<GLuint>& indices);
    GLuint id;
    void bind();
    void unbind();
    void clear();
};

#endif
