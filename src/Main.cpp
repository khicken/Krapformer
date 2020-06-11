// g++ Main.cpp -o run -lglfw3 -lopengl32 -lglu32  -lgdi32 -lglew32 -lfreeglut -lsoil2

#include "Main.h"

enum GameState {
    GAME_INGAME,
    GAME_TITLE,
    GAME_PAUSED,
    GAME_OPTIONS
};

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void pollExtraEvents(GLFWwindow* window);

// window
unsigned int windowWidth = 1280, windowHeight = 720;

bool paused = false;

// object vertices
float floorVertices[] = {
    -10.0f, -1.0f, 10.0f, 0.0f, 0.0f,
    10.0f, -1.0f, 10.0f, 1.0f, 0.0f,
    10.0f, -1.0f, -10.0f, 1.0f, 1.0f,
    -10.0f, -1.0f, -10.0f, 0.0f, 1.0f
};
float vertices[] = { // basic cube vertices
    // vertex coords     texture coords
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
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

// init objects
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
Object cube(vertices, "./src/assets/new.jpg");

// time variables to keep program consistent based off of time, not frames
float deltaTime = 0.0f;
float lastTime = 0.0f;

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
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    int monitorWidth = mode->width, monitorHeight = mode->height;

    // viewport and window position
    glViewport(0, 0, windowWidth, windowHeight);
    glfwSetWindowPos(window, monitorWidth/2 - windowWidth/2, monitorHeight/2 - windowHeight/2);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPos(window, camera.lastPosX, camera.lastPosY);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback); // when window resized
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);

    glEnable(GL_DEPTH_TEST); // enable z-axis depth (we're working with 3d here!)

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsClassic();

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
        ImGui_ImplGlfwGL3_NewFrame();
        pollExtraEvents(window); // need to poll continuously frame-by-frame
        glClearColor(0.9f, 1.0f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(paused) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }

        ImGui::Text("huh");
        
        rectShader.use();
cube.bind();
        glm::mat4 projection = glm::perspective(glm::radians(camera.fov), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f); // update perspective by fov every frame
        rectShader.setMat4("projection", projection);

        glm::mat4 view = camera.getViewMatrix();
        rectShader.setMat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);
        
        for(int i = 0; i < sizeof(cubePositions)/sizeof(cubePositions[0]); i++) {
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, glm::sin((float)glfwGetTime()), glm::vec3(1.0f, 0.0f, 0.0f));
            rectShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        } // draw cubes from cube pos array

        // end render
        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents(); // poll regular glfw callbacks
    }

    cube.destroy();
    ImGui_ImplGlfwGL3_Shutdown();
    glfwTerminate();
    return 0;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) { // call when window resized
    glViewport(0, 0, width, height);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(key == GLFW_KEY_ESCAPE) paused = paused ? false : true; // glfwSetWindowShouldClose(window, true);
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    camera.mouseEvent((float)xpos, (float)ypos);
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.scrollEvent(yoffset);
}

// events that need to be run at every frame refresh at a constant rate
void pollExtraEvents(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.keyEvent(FORWARD, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.keyEvent(BACKWARD, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.keyEvent(LEFT, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.keyEvent(RIGHT, deltaTime);
}