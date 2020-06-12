#ifndef SPRITE_3D
#define SPRITE_3D

#include "Main.h"

class Sprite3D {
public:
    Sprite3D(Shader &shader);
    ~Sprite3D();

    void drawSprite(Texture &texture, glm::vec3 position, glm::vec3 size, float rotate, glm::vec3 color);
private:
    Shader shader;
    unsigned int quadVAO;
    void initRenderData();
private:
};

#endif