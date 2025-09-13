#ifndef texture_hpp 
#define texture_hpp

#include "../../external/stb/stb_image.h"
#include <cstdint>

struct Texture {
    uint32_t id; 
    static Texture load(const char* image_path);
};

#endif
