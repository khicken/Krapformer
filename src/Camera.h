#ifndef CAMERA_H
#define CAMERA_H

#include "Main.h"

enum Directions { // other classes might need to know player's direction for later physics
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

extern unsigned int windowWidth, windowHeight;

// default or global camera values (d prefix)
float d_pitch = 0.0f;
float d_yaw = -90.0f;

// customizable mouse stuff (global with g prefix)
float g_movementSpeed = 5.0f;
float g_mouseSensitivity = 1.0f;
float g_fov = 45.0f;
float g_minfov = 1.0f, g_maxfov = 45.0f;
bool g_invertY = false; // invert y-movement idk why

class Camera {
public:
    glm::vec3 position, front, up, right, worldUp;
    float yaw, pitch, movementSpeed, mouseSensitivity, fov;
    bool invertY;
    float velocity;
    float lastPosX, lastPosY;

    Camera(glm::vec3 pos, glm::vec3 u, float y, float p);
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float y, float p);

    void mouseEvent(double xpos, double ypos);
    void keyEvent(Directions dir, float deltaTime);
    void scrollEvent(double yoffset);

    glm::mat4 getViewMatrix();
private:
    glm::vec3 front_no_pitch;
    void updateCameraVectors();
};

#endif