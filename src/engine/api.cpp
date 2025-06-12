#include "../include/steel-engine/steel.hpp"
#include "iron-engine.hpp"

namespace steel 
{

bool is_running() {
    return IronEngine::get().is_running();
}

void render() {
    IronEngine::get().render();
}

void update() {
    IronEngine::get().update();
}

void handle_inputs() {
    IronEngine::get().handle_inputs();
}

void exit() {
    IronEngine::get().clear();
}

}
