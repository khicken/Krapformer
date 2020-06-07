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
    float velocity; // will be acted upon later
    float lastPosX, lastPosY;

    Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 u = glm::vec3(0.0f, 1.0f, 0.0f), float y = d_yaw, float p = d_pitch) :
        front(glm::vec3(0.0f, 0.0f, -1.0f)), invertY(g_invertY), movementSpeed(g_movementSpeed), mouseSensitivity(0.1f), fov(g_fov), lastPosX(windowWidth/2), lastPosY(windowHeight/2) {
        position = pos;
        worldUp = u;
        yaw = y;
        pitch = p;
        updateCameraVectors();
    }

    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float y, float p) : 
        front(glm::vec3(0.0f, 0.0f, -1.0f)), invertY(g_invertY), movementSpeed(g_movementSpeed), mouseSensitivity(0.1f), fov(g_fov), lastPosX(windowWidth/2), lastPosY(windowHeight/2) {
        position = glm::vec3(posX, posY, posZ);
        worldUp = glm::vec3(upX, upY, upZ);
        yaw = y;
        pitch = p;
        updateCameraVectors();
    }

    void mouseEvent(double xpos, double ypos) {
        float xOffset = xpos - lastPosX;
        float yOffset = invertY ? ypos - lastPosY : lastPosY - ypos;
        lastPosX = xpos, lastPosY = ypos;

        xOffset *= mouseSensitivity;
        yOffset *= mouseSensitivity; // multiply by sensitivity or else mouse movement will go brrrr

        yaw = glm::mod(yaw + xOffset, 360.0f); // rotate around y-axis (left/right) by adding/subtracting deg from yaw (also modulate yaw so it never goes above 360 deg)
        pitch += yOffset; // do the same but up/down for pitch

        if(pitch > 89.0f) pitch = 89.0f;
        if(pitch < -89.0f) pitch = -89.0f;

        updateCameraVectors();
    }

    void keyEvent(Directions dir, float deltaTime) {
        velocity = movementSpeed * deltaTime;

        if(dir == FORWARD)  position += front_no_pitch * velocity;
        if(dir == BACKWARD) position -= front_no_pitch * velocity;
        if(dir == LEFT)     position -= right * velocity;
        if(dir == RIGHT)    position += right * velocity;
    }

    void scrollEvent(double yoffset) {
        fov -= (float)yoffset;
        if(fov < g_minfov) fov = g_minfov;
        if(fov > g_maxfov) fov = g_maxfov;

        mouseSensitivity = g_mouseSensitivity * (fov / (10 * g_maxfov)); // sensitivity changes based on zoom level
    }

    glm::mat4 getViewMatrix() { // view matrix is changed by mouse input, so it must be called in main method
        return glm::lookAt(position, position + front, up);
    }
private:
    glm::vec3 front_no_pitch;
    void updateCameraVectors() { // need to use on init and every mouse movement
        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(direction); // apply direction to the camera
        right = glm::normalize(glm::cross(front, worldUp)); // normalize the vectors as their length approaches 0 the more the vectors move
        up    = glm::normalize(glm::cross(right, front));
        front_no_pitch = glm::vec3(glm::cos(glm::radians(yaw)), 0.0f, glm::sin(glm::radians(yaw)));
    }
};

#endif