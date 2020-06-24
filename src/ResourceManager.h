#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>

#include "Shader.h"
#include "Texture.h"

class ResourceManager {
public:
    static std::map<std::string, Shader> shaders;
    static std::map<std::string, Texture> textures;
    static Shader loadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name);
    static Shader getShader(std::string name);
    static Texture loadTexture(const char *file, bool alpha, std::string name);
    static Texture getTexture(std::string name);
    static void flush();
private:
    ResourceManager() {}
    static Shader loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile = nullptr);
    static Texture loadTextureFromFile(const char *file, bool alpha);
};

#endif