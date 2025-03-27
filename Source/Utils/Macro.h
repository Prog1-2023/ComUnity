#pragma once
#include <iostream>
#include <filesystem>
#include <map>

#define _USE_MATH_DEFINES
#include <math.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <set>
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

using namespace Assimp;
using namespace std;
using namespace filesystem;
using namespace glm;

enum FolderType
{
	SHADERS,
	TEXTURES,
	CONTENT,

	COUNT
};

//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define FORCEINLINE __forceinline
#define SUPER __super

#define DEBUG

#ifdef DEBUG
#   define Assert(Expr, Msg) \
    AssertDebug(#Expr, Expr, Msg, __FILE__, __LINE__)
#else
#   define Assert(Expr, Msg) \
    AssertNoDebug(#Expr, Expr, Msg)
#endif

void AssertDebug(const char* _exprStr, const bool _expr, const char* _msg, const char* _file, const int _line);
void AssertNoDebug(const char* _exprStr, const bool _expr, const char* _msg);

string GetPath(const FolderType& _folderType);