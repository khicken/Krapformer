// file with all extensions and shtuff
#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>

// os 0 for windows, 1 for mac, 2 for linux
#if defined(__WIN32) || defined(_WIN64)
#include <tchar.h>
#include <windows.h>
const int OS = 0;
#elif defined(__APPLE__) || defined(__MACH__)
const int OS = 1;
#elif defined(__linux__)
const int OS = 2;
#endif

#define GLEW_STATIC
#include "../glew-2.1.0/include/GL/glew.h"
#include "../glfw/include/GLFW/glfw3.h"

// transformations with matrices and all that stuff
#include "../glm/glm/glm.hpp"
#include "../glm/glm/gtc/matrix_transform.hpp"
#include "../glm/glm/gtc/type_ptr.hpp"

// #include "../soil2/include/SOIL2.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"

#include "../imgui/imgui_impl_glfw_gl3.h"
#include "../imgui/imgui.h"

#include "Object.h"
#include "Shader.h"
#include "Texture.h"
#include "Sprite2D.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "Engine.h"