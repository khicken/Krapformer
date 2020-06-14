#include "Engine.h"

Sprite2D *sprite;
Sprite3D *cube;
Camera *camera;

Engine::Engine(unsigned int windowwidth, unsigned int windowheight) : state(GAME_INGAME), keys() {
    this->WINDOW_WIDTH = windowwidth;
    this->WINDOW_HEIGHT = windowheight;
}

Engine::~Engine() {
    delete sprite;
}

void Engine::windowInit(GLFWwindow* window) {
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor()); // fetch monitor stats
    this->MONITOR_WIDTH = mode->width, this->MONITOR_HEIGHT = mode->height;

    glViewport(0, 0, this->WINDOW_WIDTH, this->WINDOW_HEIGHT);
    glfwSetWindowPos(window, this->MONITOR_WIDTH/2 - this->WINDOW_WIDTH/2, this->MONITOR_HEIGHT/2 - this->WINDOW_HEIGHT/2);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPos(window, camera->lastPosX, camera->lastPosY);
}

void Engine::init() {
    ResourceManager::loadShader("./shaders/vs_2d.glsl", "./shaders/fs_2d.glsl", nullptr, "2D");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->WINDOW_WIDTH), static_cast<float>(this->WINDOW_HEIGHT), 0.0f, -1.0f, 1.0f);
    ResourceManager::getShader("2D").use().setInt("image", 0);
    ResourceManager::getShader("2D").setMat4("projection", projection);
    sprite = new Sprite2D(ResourceManager::getShader("2D"));
    ResourceManager::loadTexture("./assets/new.jpg", true, "goomba");
}

void Engine::update() {
    glm::mat4 projection = glm::perspective(glm::radians(camera->fov), (float)this->WINDOW_WIDTH / (float)this->WINDOW_HEIGHT, 0.1f, 100.0f); // update perspective by fov every frame
    ResourceManager::getShader("3D").setMat4("projection", projection);

    glm::mat4 view = camera->getViewMatrix();
    ResourceManager::getShader("3D").setMat4("view", view);
}

void Engine::render() {
    sprite->drawSprite(ResourceManager::getTexture("goomba"), glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->drawSprite(ResourceManager::getTexture("goomba"), glm::vec3(1.0f, 3.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f), 45.0f, glm::vec3(1.0f, 1.0f, 1.0f))
}

void Engine::pollEvents(float dt) {
    if(this->state == GAME_INGAME) {
        if(this->keys[GLFW_KEY_W]) camera->keyEvent(FORWARD, dt);
        if(this->keys[GLFW_KEY_S]) camera->keyEvent(BACKWARD, dt);
        if(this->keys[GLFW_KEY_A]) camera->keyEvent(LEFT, dt);
        if(this->keys[GLFW_KEY_D]) camera->keyEvent(RIGHT, dt);
    }
}