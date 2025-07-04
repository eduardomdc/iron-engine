#ifndef SHADER_H
#define SHADER_H

#include <glm/glm.hpp>
#include <cstdint>
#include <string>

class Shader {
public:
    uint32_t id;
    Shader(const char* vertexPath, const char* fragmentPath);
    void use() const;
    void set_bool(const std::string &name, bool value) const;
    void set_int(const std::string &name, int value) const;
    void set_float(const std::string &name, float value) const;
    void set_mat4(const std::string &name, glm::mat4 matrix) const;
    void checkCompileErrors(unsigned int shader, std::string type);
};
#endif


