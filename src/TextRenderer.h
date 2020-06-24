#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Shader.h"

struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // Size of glyph
    glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};
std::map<GLchar, Character> Characters;
unsigned int VAO, VBO;

class TextRenderer {
public:
    Shader shader;
    TextRenderer(const Shader& shader);
    void init();
	void drawText(std::string text, float x, float y, float scale, glm::vec3 color);
private:

};

#endif