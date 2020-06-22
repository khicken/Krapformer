#ifndef SPRITE_2D
#define SPRITE_2D

#include "Shader.h"
#include "Texture.h"

class Sprite2D {
public:
    Sprite2D(Shader shader);
    ~Sprite2D();

    void drawSprite(const Texture &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
protected:
    Shader shader;
    unsigned int quadVAO;
    void initRenderData();
};

#endif