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
extern float deltaTime, lastTime;

// default or global camera values (d prefix)
float d_pitch = 0.0f;
float d_yaw = -90.0f;

// customizable mouse stuff (global with g prefix)
float g_movementSpeed = 5.0f;
float g_mouseSensitivity = 0.1f;
float g_fov = 45.0f;
float g_minfov = 1.0f, g_maxfov = 45.0f;
bool g_invertY = false; // invert y-movement idk why

class Camera {
public:
    glm::vec3 position, front, up, right, worldUp;
    float yaw, pitch, movementSpeed, mouseSensitivity, fov;
    float velocity; // will be acted upon later
    float lastPosX, lastPosY;

    Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 u = glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3 f = glm::vec3(0.0f, 0.0f, -1.0f), float y = d_yaw, float p = d_pitch) :
            front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(g_movementSpeed), mouseSensitivity(g_mouseSensitivity), fov(g_fov), lastPosX(windowWidth/2), lastPosY(windowHeight/2) {
        position = pos;
        front = f;
        up = u;
        yaw = y;
        pitch = p;
    }

    void mouseEvent(double xpos, double ypos) {
        float xOffset = xpos - lastPosX;
        float yOffset = g_invertY ? ypos - lastPosY : lastPosY - ypos;
        lastPosX = xpos, lastPosY = ypos;

        xOffset *= mouseSensitivity;
        yOffset *= mouseSensitivity; // multiply by sensitivity or else mouse movement will go brrrr

        yaw += xOffset; // rotate around y-axis (left/right) by adding/subtracting deg from yaw
        pitch += yOffset; // do the same but up/down for pitch

        if(pitch > 89.0f) pitch = 89.0f;
        if(pitch < -89.0f) pitch = -89.0f;

        // now point camera in a direction
        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(direction); // finally apply direction to adjust camera view
        right = glm::normalize(glm::cross(front, worldUp));
        up = glm::normalize(glm::cross(right, front));
    }

    void keyEvent(Directions dir) {
        velocity = movementSpeed * deltaTime;

        if(dir == FORWARD)  position += front * velocity;
        if(dir == BACKWARD) position -= front * velocity;
        if(dir == LEFT)     position -= right * velocity;
        if(dir == RIGHT)    position += right * velocity;
    }

    void scrollEvent(double yoffset) {
        fov -= (float)yoffset;
        if(fov < g_minfov) fov = g_minfov;
        if(fov > g_maxfov) fov = g_maxfov;
    }

    glm::mat4 getViewMatrix() { // view matrix is changed by mouse input, so it must be called in main method
        return glm::lookAt(position, position + front, up);
    }
private:
};

#endif