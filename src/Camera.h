#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>

#include "Libraries.h"

enum Directions { // other classes might need to know player's direction for later physics
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

extern float d_pitch, d_yaw;
extern float g_movementSpeed, g_mouseSensitivity, g_fov, g_minfov, g_maxfov;
extern bool g_invertY;

class Camera {
public:
    glm::vec3 position, front, up, right, worldUp;
    float yaw, pitch, movementSpeed, mouseSensitivity, fov;
    bool invertY;
    float velocity;
    float lastPosX, lastPosY;

    Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 u = glm::vec3(0.0f, 1.0f, 0.0f), float y = d_yaw, float p = d_pitch) :
  front(glm::vec3(0.0f, 0.0f, -1.0f)), invertY(g_invertY), movementSpeed(g_movementSpeed), mouseSensitivity(0.1f), fov(g_fov), lastPosX(1280.0f/2.0f), lastPosY(720.0f/2.0f) {
        this->position = pos;
        this->worldUp = u;
        this->yaw = y;
        this->pitch = p;
        this->updateCameraVectors();
    }

    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float y, float p) : 
  front(glm::vec3(0.0f, 0.0f, -1.0f)), invertY(g_invertY), movementSpeed(g_movementSpeed), mouseSensitivity(0.1f), fov(g_fov), lastPosX(1280.0f/2.0f), lastPosY(720.0f/2.0f) {
        this->position = glm::vec3(posX, posY, posZ);
        this->worldUp = glm::vec3(upX, upY, upZ);
        this->yaw = y;
        this->pitch = p;
        this->updateCameraVectors();
    }

    void mouseEvent(float xpos, float ypos) {
        std::cout << this->yaw << " " << std::endl;
        float xOffset = xpos - lastPosX;
        float yOffset = this->invertY ? ypos - this->lastPosY : this->lastPosY - ypos;
        this->lastPosX = xpos, this->lastPosY = ypos;

        xOffset *= this->mouseSensitivity;
        yOffset *= this->mouseSensitivity; // multiply by sensitivity or else mouse movement will go brrrr

        this->yaw = glm::mod(this->yaw + xOffset, 360.0f); // rotate around y-axis (left/right) by adding/subtracting deg from this->yaw (also modulate this->yaw so it never goes above 360 deg)
        this->pitch += yOffset; // do the same but up/down for pitch

        if(this->pitch > 89.0f) this->pitch = 89.0f;
        if(this->pitch < -89.0f) this->pitch = -89.0f;

        this->updateCameraVectors();
    }
    void keyEvent(Directions dir, float deltaTime) {
            velocity = this->movementSpeed * deltaTime;

    if(dir == FORWARD)  this->position += this->front_no_pitch * velocity;
    if(dir == BACKWARD) this->position -= this->front_no_pitch * velocity;
    if(dir == LEFT)     this->position -= this->right * velocity;
    if(dir == RIGHT)    this->position += this->right * velocity;
    }
    void scrollEvent(double yoffset) {
            this->fov -= (float)yoffset;
    if(this->fov < g_minfov) this->fov = g_minfov;
    if(this->fov > g_maxfov) this->fov = g_maxfov;

    this->mouseSensitivity = g_mouseSensitivity * (this->fov / (10 * g_maxfov)); // sensitivity changes based on zoom level
    }

    glm::mat4 getViewMatrix() {
        return glm::lookAt(this->position, this->position + this->front, up);
    }
private:
    glm::vec3 front_no_pitch;
    void updateCameraVectors() {
            std::cout << "here: " << this->lastPosX << std::endl;  
    // need to use on init and every mouse movement (to update camera, duh)
    glm::vec3 direction;
    direction.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    direction.y = sin(glm::radians(this->pitch));
    direction.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    this->front = glm::normalize(direction); // apply direction to the camera
    this->right = glm::normalize(glm::cross(this->front, this->worldUp)); // normalize the vectors as their length approaches 0 the more the vectors move
    this->up    = glm::normalize(glm::cross(this->right, this->front));
    this->front_no_pitch = glm::vec3(glm::cos(glm::radians(this->yaw)), 0.0f, glm::sin(glm::radians(this->yaw)));
    };
};

#endif