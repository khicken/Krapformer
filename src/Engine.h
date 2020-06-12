#ifndef ENGINE_H
#define ENGINE_H

#include "Main.h"

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
    bool fullscreen;
    bool keys[1024];

    Engine(unsigned int windowwidth, unsigned int windowheight);
    ~Engine();
    void windowInit(GLFWwindow* window); // configs some window elements and such
    void init(); // loads textures, shaders, and other objects
    void update();
    void render();
    void pollEvents(float dt);
private:
    void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void mouseCallback(GLFWwindow* window, double xpos, double ypos);
    void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

};

#endif