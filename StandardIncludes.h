#ifndef STANDARD_INCLUDES_H
#define STANDARD_INCLUDES_H

//include standard headers
#include <vector> //vector is like list in c++
#include <string>
#include <fstream>

//Windows specific includes and defines
#ifdef _WIN32
#include <Windows.h>
#define M_ASSERT(_cond,_msg) \
	if (!(_cond)) { OutputDebugStringA(_msg); std::abort(); glfwTerminate(); }
#endif

//include GL/helper headers
#include <GL/glew.h> //including glew
#include <GLFW/glfw3.h> //including glfw
#include <glm/glm.hpp> //including glm
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Resolution.h"
#include "Singleton.h"

using namespace std;

#endif // STANDARD_INCLUDES_H


