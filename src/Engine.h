#ifndef ENGINE_H
#define ENGINE_H

#include "ResourceManager.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Camera.h"
#include "TextRenderer.h"

#include <GLFW/glfw3.h>

enum GameState {
    GAME_INGAME,
    GAME_TITLE,
    GAME_PAUSED,
    GAME_OPTIONS
};

class Engine {
public:
    GameState state;
    // window related variables
    unsigned int WINDOW_WIDTH, WINDOW_HEIGHT, MONITOR_WIDTH, MONITOR_HEIGHT;
    const char* TITLE;
    bool fullscreen;
    bool keys[1024];

    Engine(unsigned int windowwidth, unsigned int windowheight);
    ~Engine();
    void windowInit(GLFWwindow* window); // configs some window elements and such
    void init(); // loads textures, shaders, and other objects
    void update();
    void render();
    void pollEvents(GLFWwindow* window, float dt);

    void updateMouse(double xpos, double ypos);
    void updateScroll(double yoffset);
    void updateKeys(GLFWwindow* window, int key, int action);
private:
};

#endif