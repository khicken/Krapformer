#ifndef SHADER_H
#define SHADER_H

#include "Main.h"

class Shader {
public:
    unsigned int ID; // state
    Shader();
    Shader &use();

    // compile shader from source code
    void compile(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr); // note: geometry source code is optional

    // pass values to shader
    void setBool(const char* name, bool value, bool useShader = false);
    void setInt(const char* name, int value, bool useShader = false);
    void setFloat(const char* name, float value, bool useShader = false);
    void setVec2(const char* name, const glm::vec2 &value, bool useShader = false);
    void setVec2(const char* name, float x, float y, bool useShader = false);
    void setVec3(const char* name, const glm::vec3 &value, bool useShader = false);
    void setVec3(const char* name, float x, float y, float z, bool useShader = false);
    void setVec4(const char* name, const glm::vec4 &value, bool useShader = false);
    void setVec4(const char* name, float x, float y, float z, float w, bool useShader = false);
    void setMat4(const char* name, const glm::mat4 &matrix, bool useShader = false);
private:
    // checks if compilation or linking failed and if so, print the error logs
    void checkCompileErrors(unsigned int object, std::string type);
};

#endif