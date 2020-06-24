//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup") // hide console for windows

#include "Engine.h"

Sprite2D *sprite;
Sprite3D *cube;
TextRenderer* text;
Camera camera(glm::vec3(0.0f, 3.0f, 0.0f));

glm::mat4 projection2D, projection3D, view3D;

Engine::Engine(unsigned int windowwidth, unsigned int windowheight) : TITLE("wat"), state(GAME_INGAME), keys() {
    this->WINDOW_WIDTH = windowwidth;
    this->WINDOW_HEIGHT = windowheight;
}

Engine::~Engine() {
    delete sprite;
    delete cube;
    delete text;
    // delete &camera;
}

void Engine::windowInit(GLFWwindow* window) {
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor()); // fetch monitor stats
    this->MONITOR_WIDTH = mode->width, this->MONITOR_HEIGHT = mode->height;

    glViewport(0, 0, this->WINDOW_WIDTH, this->WINDOW_HEIGHT);
    glfwSetWindowPos(window, this->MONITOR_WIDTH/2 - this->WINDOW_WIDTH/2, this->MONITOR_HEIGHT/2 - this->WINDOW_HEIGHT/2);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPos(window, camera.lastPosX, camera.lastPosY);

    this->state = GAME_INGAME;
    std::cout << this->state << std::endl;

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Engine::init() { // load objects and such
    // load shaders
    ResourceManager::loadShader(".\\src\\shaders\\vs_2d.glsl", ".\\src\\shaders\\fs_2d.glsl", nullptr, "2D");
    ResourceManager::loadShader(".\\src\\shaders\\vs_3d.glsl", ".\\src\\shaders\\fs_3d.glsl", nullptr, "3D");
    ResourceManager::loadShader(".\\src\\shaders\\vs_txt.glsl", ".\\src\\shaders\\fs_txt.glsl", nullptr, "txt");
    
    // set shader properties and projection matrix
    projection2D = glm::ortho(0.0f, static_cast<float>(this->WINDOW_WIDTH), static_cast<float>(this->WINDOW_HEIGHT), 0.0f, -1.0f, 1.0f);
    ResourceManager::getShader("2D").use().setInt("image", 0);
    ResourceManager::getShader("2D").setMat4("projection", projection2D);
    projection3D =  glm::perspective(glm::radians(camera.fov), (float)this->WINDOW_WIDTH / (float)this->WINDOW_HEIGHT, 0.1f, 100.0f);
    ResourceManager::getShader("3D").use().setInt("image", 0);

    sprite = new Sprite2D(ResourceManager::getShader("2D"));
    cube = new Sprite3D(ResourceManager::getShader("3D"));
    text = new TextRenderer(ResourceManager::getShader("txt"));

    text->init();
    ResourceManager::loadTexture(".\\src\\assets\\awesomeface.png", true, "goomba");
}

void Engine::update() {
    // update 3D objects by the camera
    projection3D = glm::perspective(glm::radians(camera.fov), (float)this->WINDOW_WIDTH / (float)this->WINDOW_HEIGHT, 0.1f, 100.0f); // update perspective by fov every frame
    view3D = camera.getViewMatrix();
    ResourceManager::getShader("3D").setMat4("projection", projection3D);
    ResourceManager::getShader("3D").setMat4("view", view3D);
}

void Engine::render() {
    sprite->drawSprite(ResourceManager::getTexture("goomba"), glm::vec2((float)this->WINDOW_WIDTH-300.0f, (float)this->WINDOW_HEIGHT - 300.0f), glm::vec2(300.0f, 300.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    cube->drawSprite(ResourceManager::getTexture("goomba"), glm::vec3(10.0f, 10.0f, (float)glm::cos(glfwGetTime())), glm::vec3(200.0f, 200.0f, 200.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    cube->drawSprite(ResourceManager::getTexture("goomba"), glm::vec3(-10.0f, -10.0f, 1.0f), glm::vec3(1000.0f, 1000.0f, 1000.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    text->drawText("lol", 10.0f, 10.0f, 10.0f, glm::vec3(1.0f, 1.0f, 0.0f));
}

void Engine::pollEvents(GLFWwindow* window, float dt) {
    if(this->state == GAME_INGAME) {
        if(this->keys[GLFW_KEY_W]) camera.keyEvent(FORWARD, dt);
        if(this->keys[GLFW_KEY_S]) camera.keyEvent(BACKWARD, dt);
        if(this->keys[GLFW_KEY_A]) camera.keyEvent(LEFT, dt);
        if(this->keys[GLFW_KEY_D]) camera.keyEvent(RIGHT, dt);
        if(this->keys[GLFW_KEY_SPACE]) camera.keyEvent(UP, dt);
        if(this->keys[GLFW_KEY_LEFT_SHIFT]) camera.keyEvent(DOWN, dt);
    } else if(this->state == GAME_PAUSED) {

    }
}

void Engine::updateKeys(GLFWwindow* window, int key, int action) {
    if(key >= 0 && key < 1024) {
        if(action == GLFW_PRESS) this->keys[key] = true;
        else if(action == GLFW_RELEASE) this->keys[key] = false;
    }

    if(key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE) {
        if(this->state == GAME_INGAME) {
            glfwSetCursorPos(window, this->WINDOW_WIDTH/2, this->WINDOW_HEIGHT/2);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            this->state = GAME_PAUSED;
        } else if(this->state == GAME_PAUSED) {
            glfwSetCursorPos(window, this->WINDOW_WIDTH/2, this->WINDOW_HEIGHT/2);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            this->state = GAME_INGAME;
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