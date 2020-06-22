#include "Engine.h"

Sprite2D *sprite;
Sprite3D *cube;
Camera camera(glm::vec3(0.0f, 3.0f, 0.0f));

Engine::Engine(unsigned int windowwidth, unsigned int windowheight) : TITLE("wat"), state(GAME_INGAME), keys() {
    this->WINDOW_WIDTH = windowwidth;
    this->WINDOW_HEIGHT = windowheight;
}

Engine::~Engine() {
    delete sprite;
    delete cube;
    // delete &camera;
}

void Engine::windowInit(GLFWwindow* window) {
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor()); // fetch monitor stats
    this->MONITOR_WIDTH = mode->width, this->MONITOR_HEIGHT = mode->height;

    glViewport(0, 0, this->WINDOW_WIDTH, this->WINDOW_HEIGHT);
    glfwSetWindowPos(window, this->MONITOR_WIDTH/2 - this->WINDOW_WIDTH/2, this->MONITOR_HEIGHT/2 - this->WINDOW_HEIGHT/2);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPos(window, camera.lastPosX, camera.lastPosY);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Engine::init() { // load objects and such
    ResourceManager::loadShader("C:\\Users\\kaleb\\Desktop\\3d\\src\\shaders\\vs_2d.glsl", "C:\\Users\\kaleb\\Desktop\\3d\\src\\shaders\\fs_2d.glsl", nullptr, "2D");
    // ResourceManager::loadShader("./shaders/vs_3d.glsl", "./shaders/fs_3d.glsl", nullptr, "3D");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->WINDOW_WIDTH), static_cast<float>(this->WINDOW_HEIGHT), 0.0f, -1.0f, 1.0f);
    ResourceManager::getShader("2D").use();
    ResourceManager::getShader("2D").setInt("image", 0);
    ResourceManager::getShader("2D").setMat4("projection", projection);
    sprite = new Sprite2D(ResourceManager::getShader("2D"));
    // cube = new Sprite3D(ResourceManager::getShader("3D"));
    ResourceManager::loadTexture("C:\\Users\\kaleb\\Desktop\\3d\\src\\assets\\new.jpg", false, "goomba");
}

void Engine::update() {
    // update camera
    glm::mat4 projection = glm::perspective(glm::radians(camera.fov), (float)this->WINDOW_WIDTH / (float)this->WINDOW_HEIGHT, 0.1f, 100.0f); // update perspective by fov every frame
    // ResourceManager::getShader("3D").setMat4("projection", projection);

    glm::mat4 view = camera.getViewMatrix();
    // ResourceManager::getShader("3D").setMat4("view", view);
}

void Engine::render() {
    sprite->drawSprite(ResourceManager::getTexture("goomba"), glm::vec2(glm::sin(glfwGetTime()), 200.0f), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    // cube->drawSprite(ResourceManager::getTexture("goomba"), glm::vec3(1.0f, 3.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f), 45.0f, glm::vec3(1.0f, 1.0f, 1.0f));
}

void Engine::pollEvents(float dt) {
    if(this->state == GAME_INGAME) {
        if(this->keys[GLFW_KEY_W]) camera.keyEvent(FORWARD, dt);
        if(this->keys[GLFW_KEY_S]) camera.keyEvent(BACKWARD, dt);
        if(this->keys[GLFW_KEY_A]) camera.keyEvent(LEFT, dt);
        if(this->keys[GLFW_KEY_D]) camera.keyEvent(RIGHT, dt);
    }
}

void Engine::updateKeys(GLFWwindow* window, int key, int action) {
    if(this->state == GAME_INGAME) {
        if(key == GLFW_KEY_ESCAPE) glfwSetWindowShouldClose(window, true); //this->state = this->state == GAME_PAUSED : this->state = GAME_INGAME ? this->state = GAME_PAUSED; // switch between paused or ingame
        if(key >= 0 && key < 1024) {
            if (action == GLFW_PRESS) this->keys[key] = true;
            else if(action == GLFW_RELEASE) this->keys[key] = false;
        }
    }
}

void Engine::updateMouse(double xpos, double ypos) {
    if(this->state == GAME_INGAME) {
        camera.mouseEvent((float)xpos, (float)ypos);
    }
}

void Engine::updateScroll(double yoffset) {
    if(this->state == GAME_INGAME) {
        camera.scrollEvent(yoffset);
    }
}