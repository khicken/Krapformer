#include "Shader.h"

#include "Main.h"

Shader::Shader() {

}

Shader &Shader::use() {
    glUseProgram(this->ID);
    return *this;
}

void Shader::compile(const char* vertexPath, const char* fragmentPath, const char* geometryPath) {
    unsigned int vertexS, fragmentS, geometryS; // initialize shader variables

    // compile vertex shader from source
    vertexS = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexS, 1, &vertexPath, NULL);
    glCompileShader(vertexS);
    this->checkCompileErrors(vertexS, "VERTEX");

    // compile fragment shader from source
    fragmentS = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentS, 1, &fragmentPath, NULL);
    glCompileShader(fragmentS);
    this->checkCompileErrors(fragmentS, "FRAGMENT");

    // compile geometry shader from source if passed
    if (geometryPath != nullptr) {
    geometryS = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometryS, 1, &geometryPath, NULL);
    glCompileShader(geometryS);
    this->checkCompileErrors(geometryS, "GEOMETRY");
    }

    // link and compile program (ID)
    this->ID = glCreateProgram();
    glAttachShader(this->ID, vertexS);
    glAttachShader(this->ID, fragmentS);
    if(geometryPath != nullptr) glAttachShader(this->ID, geometryS);
    glLinkProgram(this->ID);
    this->checkCompileErrors(this->ID, "PROGRAM");

    // free memory as shaders already binded to program
    glDeleteShader(vertexS);
    glDeleteShader(fragmentS);
    if(geometryPath != nullptr) glDeleteShader(geometryS);
}

void Shader::setBool(const char* name, bool value, bool useShader) {
    if(useShader) this->use();
    glUniform1i(glGetUniformLocation(ID, name), (int)value);
}
void Shader::setInt(const char* name, int value, bool useShader) {
    if(useShader) this->use();
    glUniform1i(glGetUniformLocation(ID, name), value);
}
void Shader::setVec2(const char *name, float x, float y, bool useShader) {
    if(useShader) this->use();
    glUniform2f(glGetUniformLocation(this->ID, name), x, y);
}
void Shader::setVec2(const char *name, const glm::vec2 &value, bool useShader) {
    if(useShader) this->use();
    glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
}
void Shader::setVec3(const char *name, float x, float y, float z, bool useShader) {
    if(useShader) this->use();
    glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
}
void Shader::setVec3(const char *name, const glm::vec3 &value, bool useShader) {
    if(useShader) this->use();
    glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
}
void Shader::setVec4(const char *name, float x, float y, float z, float w, bool useShader) {
    if(useShader) this->use();
    glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
}
void Shader::setVec4(const char *name, const glm::vec4 &value, bool useShader) {
    if(useShader) this->use();
    glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
}
void Shader::setMat4(const char *name, const glm::mat4 &matrix, bool useShader) {
    if(useShader) this->use();
    glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, false, glm::value_ptr(matrix));
}

void Shader::checkCompileErrors(unsigned int object, std::string type) {
    int success;
    char infoLog[1024];
    if(type != "PROGRAM") { // check if shader is throwing error
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n *---------------------------------------------------* " << std::endl;
        }
    } else { // then it must be program
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n *---------------------------------------------------* " << std::endl;
        }
    }
}