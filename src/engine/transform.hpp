#ifndef transform_hpp
#define transform_hpp

#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtx/quaternion.hpp>

struct Transform {
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;
    glm :: mat4 get_matrix() const {
        return glm::translate(glm::mat4(1.0f), position)*glm::mat4_cast(rotation)*glm::scale(glm::mat4(1.0f),scale);
    }

};

#endif
