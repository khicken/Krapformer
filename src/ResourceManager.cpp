#include "ResourceManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

std::map<std::string, Shader> ResourceManager::shaders;
std::map<std::string, Texture> ResourceManager::textures;

Shader ResourceManager::loadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name) {
    shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return shaders[name];
}

Texture ResourceManager::loadTexture(const char *file, bool alpha, std::string name) {
    textures[name] = loadTextureFromFile(file, alpha);
    return textures[name];
}

Shader ResourceManager::getShader(std::string name) { return shaders[name]; }
Texture ResourceManager::getTexture(std::string name) { return textures[name]; }

void ResourceManager::flush() {
    for(auto iter: shaders) glDeleteProgram(iter.second.ID);
    for(auto iter: textures) glDeleteTextures(1, &iter.second.ID);
}

Shader ResourceManager::loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile) {
    std::string vertexCode, fragmentCode, geometryCode;
    try {
        // open files
        std::ifstream vertexShaderFile(vShaderFile), fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;
        
        vShaderStream << vertexShaderFile.rdbuf(); // read file buffer contents into streams
        fShaderStream << fragmentShaderFile.rdbuf();
        
        vertexShaderFile.close(); fragmentShaderFile.close(); // close file handlers
        vertexCode = vShaderStream.str(), fragmentCode = fShaderStream.str(); // convert stream into string
        
        if(gShaderFile != nullptr) { // load geometry shader if exists (same process for vertex and fragment shaders)
        std::ifstream geometryShaderFile(gShaderFile);
        std::stringstream gShaderStream;
        gShaderStream << geometryShaderFile.rdbuf();
        geometryShaderFile.close();
        geometryCode = gShaderStream.str();
        }
    } catch (std::exception &e) {
        std::cout << "ERROR::SHADER: Failed to read shader files :( ||| " << e.what() << std::endl;
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();
    const char *gShaderCode = geometryCode.c_str();

    Shader shader; // source code now as strings, now can be passed to the shader compiler
    shader.compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
}

Texture ResourceManager::loadTextureFromFile(const char *file, bool alpha) {
    Texture texture; // create texture object
    if (alpha) texture.Internal_Format = GL_RGBA, texture.Image_Format = GL_RGBA;

    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
    texture.generate(width, height, data);
    stbi_image_free(data);

    return texture;
}