#ifndef CAMERA_H
#define CAMERA_H

#include "Libraries.h"

enum Directions { // other classes might need to know player's direction for later physics
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera {
public:
    glm::vec3 position, front, up, right, worldUp;
    float yaw, pitch, movementSpeed, mouseSensitivity, fov;
    bool invertY;
    float velocity;
    float lastPosX, lastPosY;

    Camera(unsigned int windowWidth, unsigned int windowHeight, glm::vec3 pos, glm::vec3 u, float y, float p);
    Camera(unsigned int windowWidth, unsigned int windowHeight, float posX, float posY, float posZ, float upX, float upY, float upZ, float y, float p);

    void mouseEvent(double xpos, double ypos);
    void keyEvent(Directions dir, float deltaTime);
    void scrollEvent(double yoffset);

    glm::mat4 getViewMatrix();
private:
    glm::vec3 front_no_pitch;
    void updateCameraVectors();
};

#endif