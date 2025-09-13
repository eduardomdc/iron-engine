#include "texture.hpp"
#include <glad/glad.h>
#include <iostream>

Texture Texture::load(const char* image_path) {
    Texture tex;
    int width, height, n_color_channels;
    unsigned char* data = stbi_load(image_path, &width, &height, &n_color_channels, 0);
    if (!data) {
        std::cerr << "Failed to load texture file " << image_path << std::endl;
    }
    
    glGenTextures(1, &tex.id);
    glBindTexture(GL_TEXTURE_2D, tex.id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    return tex;
}
