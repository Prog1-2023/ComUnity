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
#include <queue>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;
using namespace glm;
using namespace filesystem;
using namespace Assimp;

//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define FORCEINLINE __forceinline
#define SUPER __super

#define FOR(elements) const unsigned int& _size = static_cast<const unsigned int>(elements.size()); for (unsigned int _index = 0; _index < _size; _index++)
#define FOR_OFFSET(elements, offset) const unsigned int& _size = static_cast<const unsigned int>(elements.size()); for (unsigned int _index = 0; _index < _size - offset; _index++)
#define LOOP(name, amount) for (unsigned int name = 0; name < amount; name++)

#if _DEBUG
	#define DEBUG
#endif

#ifdef DEBUG
#   define Assert(Expr, Msg) AssertDebug(#Expr, Expr, Msg, __FILE__, __LINE__)
#else
#   define Assert(Expr, Msg) AssertNoDebug(#Expr, Expr, Msg)
#endif

void AssertDebug(const char* _exprStr, const bool _expr, const char* _msg, const char* _file, const int _line);
void AssertNoDebug(const char* _exprStr, const bool _expr, const char* _msg);

enum FolderType
{
	SHADERS,
	CONTENT,
	TEXTURES,
};

string GetPath(const FolderType& _folderType);