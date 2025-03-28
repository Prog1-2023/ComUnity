#pragma once

#include <iostream>
#include <functional>
#include <filesystem>
#include <algorithm>

#define _USE_MATH_DEFINES // for C++
#include <math.h>

#include <chrono>  
#include <ctime>

// FMT
#include <fmt/core.h>

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// GLM
#define GLM_ENABLE_EXPERIMENTAL //check to remove
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// ImGUI
 #include "../IMGUI/imgui.h"
 #include "../IMGUI/imgui_impl_glfw.h"
 #include "../IMGUI/imgui_impl_opengl3.h"

//#include "imgui.h"
//#include "backends/imgui_impl_glfw.h"
//#include "backends/imgui_impl_opengl3.h"

// Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// IrrKlang
#include <irrKlang.h>

#include <map>
#include <queue>
#include <set>

enum Log_Severity { LOG, WARNING, ERROR };

using namespace std;
using namespace filesystem;
using namespace glm;
using namespace fmt;
using namespace Assimp;
using namespace ImGui;
using namespace irrklang;

typedef unsigned short u_short;
typedef unsigned int u_int;
typedef long long l_long;

//class SubclassOf;

#define DEBUG_PATH
#ifdef DEBUG_PATH
#define PATH __FUNCTION__
#else
#define PATH __FILE__
#endif // DEBUG_FILE

#define FORCEINLINE __forceinline
#define SUPER __super
#define CAST(_type, _expr) static_cast<_type>(_expr) 
#define DEBUG_INFO "(File: " + CAST(string, PATH) + " | Line: " + to_string(__LINE__) + ")"
#define IS_BASE_OF(_base, _type) typename = std::enable_if_t<std::is_base_of_v<_base, _type>>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define NO_DISCARD _NODISCARD


#if _DEBUG
#define DEBUG
#endif

#ifdef DEBUG
#   define Assert(Expr, Msg) \
    AssertDebug(#Expr,Expr,Msg,__FILE__,__LINE__)
#else
#   define Assert(Expr, Msg) \
        AssertNoDebug(#Expr, Expr, Msg)
#endif

#pragma region Log

#define LOG(_msg) Logger::GetInstance().LogMessage(_msg, LOG, __FILE__, __LINE__)
#define LOG_WARNING(_msg) Logger::GetInstance().LogMessage(_msg, WARNING, __FILE__, __LINE__)
#define LOG_ERROR(_msg) Logger::GetInstance().LogMessage(_msg, ERROR, __FILE__, __LINE__)

#pragma endregion

enum FolderType
{
    SHADERS,
    CONTENT,
    TEXTURES,
};
void AssertDebug(const char* _exprStr, const bool _expr, const char* _msg, const char* _file, const int _line);
void AssertNoDebug(const char* _exprStr, const bool _expr, const char* _msg);
string GetPath(const FolderType& _folderType);

const float MACHINE_EPSILON = std::numeric_limits<float>::epsilon();