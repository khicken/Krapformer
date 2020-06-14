#ifndef SPRITE_3D
#define SPRITE_3D

#include "Main.h"

class Sprite3D {
public:
    Sprite3D(Shader &shader);
    ~Sprite3D();

    void drawSprite(Texture &texture, glm::vec3 position, glm::vec3 size = glm::vec3(10.0f, 10.0f, 10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
private:
    Shader shader;
    unsigned int quadVAO;
    void initRenderData();
private:
};

#endif