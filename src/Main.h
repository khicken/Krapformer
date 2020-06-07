// file with all extensions and shtuff
#pragma once

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

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <array>
#include <vector>

#include "Shader.h"
#include "Camera.h"