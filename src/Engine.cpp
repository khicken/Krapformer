#include "Engine.h"

Camera *cam;


Engine::Engine(unsigned int windowwidth, unsigned int windowheight) : state(GAME_INGAME), keys() {
    WINDOW_WIDTH = windowwidth;
    WINDOW_HEIGHT = windowheight;
}

Engine::~Engine() {

}

void Engine::init() {

}

void Engine::update() {

}

void Engine::render() {

}

void Engine::pollEvents() {
    if(this->state == GAME_INGAME) {
        if(this->keys[GLFW_KEY_W])
        if(this->keys[GLFW_KEY_S])
        if(this->keys[GLFW_KEY_A])
        if(this->keys[GLFW_KEY_D])
    }
}