/*
 * The random 3D FPS by Kaleb (khicken)
 *    Developed by a future sophomore in high school.
 * 
 * View commits and changes on the Github repo: https://github.com/khicken/3d7
 * 
 * Started with basic OpenGL in C++ the summer of 2019, but started learning core OpenGL in April of 2020.
 * 
 * Latest change: 6/21/20
 * 
 * Important update: Shaders don't compile for an unknown reason, might just give up cause nothing wants to cooperate
 * 
*/

#include "Main.h"

// default or global camera values (d prefix)
float d_pitch = 0.0f;
float d_yaw = -90.0f;

// customizable mouse stuff (global with g prefix)
float g_movementSpeed = 5.0f;
float g_mouseSensitivity = 1.0f;
float g_fov = 45.0f;
float g_minfov = 1.0f, g_maxfov = 45.0f;
bool g_invertY = false; // invert y-movement idk why

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

unsigned int DEFAULT_WINDOW_WIDTH = 1280, DEFAULT_WINDOW_HEIGHT = 720;
Engine game(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);

int main() {
    float deltaTime = 0.0f, lastTime = 0.0f;
    glm::vec3 cubePositions[] = { // cube positions
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    
    glfwInit(); // initialize glfw
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // using glfw 3.x
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // using glfw x.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // using core glfw functions
    glfwWindowHint(GLFW_RESIZABLE, false);

    if(OS == 1) glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // iOS supports only opengl versions forward to the version of program/system

    GLFWwindow* window = glfwCreateWindow(game.WINDOW_WIDTH, game.WINDOW_HEIGHT, game.TITLE, nullptr, nullptr);
    if(window == nullptr) { // check if glfw is ok
        std::cout << "uh glfw broke" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // select the window

    glewInit();
    glewExperimental = true;

    game.windowInit(window);

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback); // when window resized
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);

    glEnable(GL_DEPTH_TEST); // enable z-axis depth (we're working with 3d here!)

    game.init();

    // MessageBox(0, _T("content"), _T("title"), MB_OK);

    while(!glfwWindowShouldClose(window)) { // render loop(each iteration is a frame)
        // update time logic
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastTime;
        lastTime = currentFrame;

        // refresh frame
        glClearColor(0.9f, 1.0f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        game.render();

        game.pollEvents(deltaTime);
        glfwSwapBuffers(window);
        glfwPollEvents(); // poll regular glfw callbacks
    }

    // ImGui_ImplGlfwGL3_Shutdown();
    
    glfwTerminate();
    return 0;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) { // call when window resized
    glViewport(0, 0, width, height);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    game.updateKeys(window, key, action);
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    game.updateMouse(xpos, ypos);
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    game.updateScroll(yoffset);
}