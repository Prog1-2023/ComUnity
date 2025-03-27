#pragma once
#include <iostream>
#include <filesystem>
#include <map>
#include <set>
#include <queue>
#include <functional>
#include <algorithm>

#define _USE_MATH_DEFINES
#include <math.h>

#include <chrono>  
#include <ctime>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include "../IMGUI/imgui.h"
#include "../IMGUI/imgui_impl_glfw.h"
#include "../IMGUI/imgui_impl_opengl3.h"

enum Log_Severity { LOG, WARNING, ERROR };

using namespace std;
using namespace filesystem;
using namespace glm;
using namespace Assimp;
using namespace ImGui;

//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define FORCEINLINE __forceinline
#define Super __super

#define DEBUG

#ifdef DEBUG
#define Assert(Expr, Msg) \
		AssertDebug(#Expr, Expr, Msg, __FILE__, __LINE__)
#else
#define Assert(Expr, Msg) \
		AssertNoDebug(#Expr, Expr, Msg)
#endif

void AssertDebug(const char* _exprStr, const bool _expr, const char* _msg, const char* _file, const int _line);
void AssertNoDebug(const char* _exprStr, const bool _expr, const char* _msg);

#pragma region Log

#define LOG(_msg) Logger::GetInstance().LogMessage(_msg, LOG, __FILE__, __LINE__)
#define LOG_WARNING(_msg) Logger::GetInstance().LogMessage(_msg, WARNING, __FILE__, __LINE__)
#define LOG_ERROR(_msg) Logger::GetInstance().LogMessage(_msg, ERROR, __FILE__, __LINE__)

#pragma endregion


