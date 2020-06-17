#ifndef SPRITE_3D
#define SPRITE_3D

#include "Shader.h"
#include "Texture.h"

class Sprite3D {
public:
    Sprite3D(const Shader &shader);
    ~Sprite3D();

    void drawSprite(const Texture &texture, glm::vec3 position, glm::vec3 size = glm::vec3(10.0f, 10.0f, 10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
protected:
    Shader shader;
    unsigned int quadVAO;
    void initRenderData();
};

#endif