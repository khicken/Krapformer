#ifndef ENGINE_H
#define ENGINE_H

#include "Main.h"

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
Object cube(vertices, "./src/assets/new.jpg");
Engine eng();

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
    unsigned int WINDOW_WIDTH, WINDOW_HEIGHT;
    bool fullscreen;
    bool keys[1024];

    Engine(unsigned int windowwidth, unsigned int windowheight);
    ~Engine();
    void init();
    void update();
    void render();
    void pollEvents();
private:
};

#endif