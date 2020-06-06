// file with all extensions and shtuff
#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

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
#include "../glfw-3.3.2/include/GLFW/glfw3.h"

// transformations with matrices and all that stuff
#include "../glm-0.9.9.8/glm/glm/glm.hpp"
#include "../glm-0.9.9.8/glm/glm/gtc/matrix_transform.hpp"
#include "../glm-0.9.9.8/glm/glm/gtc/type_ptr.hpp"

// #include "../soil2/include/SOIL2.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"

#include "Object.h"
#include "Shader.h"
#include "Camera.h"