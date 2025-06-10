cmake_minimum_required(VERSION 3.14)
project (
    iron-engine
    LANGUAGES C CXX
)

set(OpenGL_GL_PREFERENCE LEGACY)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_library(glad STATIC ../external/glad/src/glad.c)
set_target_properties(glad PROPERTIES LINKER_LANGUAGE C)
target_include_directories(glad PUBLIC ../external/glad/include)

set(MY_SOURCE_FILES
    ../src/main.cpp
    ../src/iron-engine.cpp
    ../src/window.cpp
    ../src/shader.cpp
    ../src/camera.cpp
    ../src/mesh/VBO.cpp
    ../src/mesh/VAO.cpp
    ../src/mesh/EBO.cpp
    ../src/mesh/primitive_meshes.cpp
)
add_executable(main ${MY_SOURCE_FILES})

target_include_directories( main PRIVATE
    ${OPENGL_INCLUDE_DIRS} 
)

target_link_libraries(main PRIVATE glad glfw OpenGL::GL glm::glm)
