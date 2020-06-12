/*
 * The random 3D FPS by Kaleb (khicken)
 *    Developed by a future sophomore in high school.
 * 
 * View commits and changes on the Github repo: https://github.com/khicken/3d
 * 
 * Started with basic OpenGL in C++ the summer of 2019, but started learning core OpenGL in April of 2020.
 * 
 * Latest change: 6/12/20
 * 
*/

#include "Main.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

// object vertices
float floorVertices[] = {
    -10.0f, -1.0f, 10.0f, 0.0f, 0.0f,
    10.0f, -1.0f, 10.0f, 1.0f, 0.0f,
    10.0f, -1.0f, -10.0f, 1.0f, 1.0f,
    -10.0f, -1.0f, -10.0f, 0.0f, 1.0f
};
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

Engine game(1280, 720);

// time variables to keep program consistent based off of time, not frames
float deltaTime = 0.0f, lastTime = 0.0f;

int main() {
    glfwInit(); // initialize glfw
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // using glfw 3.x
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // using glfw x.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // using core glfw functions
    glfwWindowHint(GLFW_RESIZABLE, false);

    if(OS == 1) glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // iOS supports only opengl versions forward to the version of program/system

    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "What", nullptr, nullptr);
    if(window == nullptr) { // check if glfw is ok
        std::cout << "uh glfw broke" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // select the window

    glewInit();
    glewExperimental = true;

    // Shader rectShader();
    // rectShader.compile();

    // fetch monitor stats
    // const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    // int monitorWidth = mode->width, monitorHeight = mode->height;

    // viewport and window position


    game.windowInit(window);


    glEnable(GL_DEPTH_TEST); // enable z-axis depth (we're working with 3d here!)

    // ImGui::CreateContext();
    // ImGuiIO& io = ImGui::GetIO(); (void)io;
    // ImGui_ImplGlfwGL3_Init(window, true);
    // ImGui::StyleColorsClassic();

    // cube.init();

    // rectShader.use();
    // rectShader.setInt("texture", 0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // MessageBox(0, _T("content"), _T("title"), MB_OK);

    while(!glfwWindowShouldClose(window)) { // render loop(each iteration is a frame)
        // update time logic
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastTime;
        lastTime = currentFrame;

        // refresh frame
        // ImGui_ImplGlfwGL3_NewFrame();
        glClearColor(0.9f, 1.0f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // ImGui::Text("huh");



        // end render
        // ImGui::Render();
        // ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
        game.pollEvents(deltaTime);
        glfwSwapBuffers(window);
        glfwPollEvents(); // poll regular glfw callbacks
    }

    // ImGui_ImplGlfwGL3_Shutdown();
    glfwTerminate();
    return 0;
}

// events that need to be run at every frame refresh at a constant rate
// void pollExtraEvents(GLFWwindow* window) {
//     if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.keyEvent(FORWARD, deltaTime);
//     if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.keyEvent(BACKWARD, deltaTime);
//     if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.keyEvent(LEFT, deltaTime);
//     if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.keyEvent(RIGHT, deltaTime);
// }