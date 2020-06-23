#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>

#include "Libraries.h"

enum Directions { // other classes might need to know player's direction for later physics
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

extern float d_pitch, d_yaw;
extern float g_movementSpeed, g_mouseSensitivity, g_fov, g_minfov, g_maxfov;
extern bool g_invertY;

class Camera {
public:
    glm::vec3 position, front, up, right, worldUp, vertical;
    float yaw, pitch, movementSpeed, mouseSensitivity, fov;
    bool invertY;
    float velocity;
    float lastPosX, lastPosY;

    Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 u = glm::vec3(0.0f, 1.0f, 0.0f), float y = d_yaw, float p = d_pitch);
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float y, float p);

    void mouseEvent(float xpos, float ypos);
    void keyEvent(Directions dir, float deltaTime);
    void scrollEvent(double yoffset);

    glm::mat4 getViewMatrix();
private:
    glm::vec3 front_no_pitch;
    void updateCameraVectors();
};

#endif