#include "iron-engine.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main (){
    while (IronEngine::get().is_running()) {
        IronEngine::get().update();
        IronEngine::get().render();
        IronEngine::get().handle_inputs();
    }
    IronEngine::get().clear();
    return 0;
}
