#ifndef SHADER_H
#define SHADER_H

#include <glm/glm.hpp>
#include <cstdint>
#include <string>

struct Shader {
public:
    uint32_t id;
    static Shader load(const char* vertexPath, const char* fragmentPath);
    void use() const;
    void set_bool(const std::string &name, bool value) const;
    void set_int(const std::string &name, int value) const;
    void set_float(const std::string &name, float value) const;
    void set_vec3(const std::string &name, const glm::vec3 &vector) const;
    void set_mat4(const std::string &name, const glm::mat4 &matrix) const;
    static void checkCompileErrors(unsigned int shader, std::string type);
};
#endif


