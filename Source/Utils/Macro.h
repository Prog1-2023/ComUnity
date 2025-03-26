/*
#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <functional>

// Collections
#include <vector>
#include <map>
#include <set>
#include <queue>

#define _USE_MATH_DEFINES // for C++
#include <math.h>

using namespace std;

// Filesystem
#include <filesystem>
using namespace filesystem;

// FMT
#include <fmt/core.h>
using namespace fmt;

// ImGui
#include <imgui.h>
using namespace ImGui;

// Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
using namespace Assimp;

// ReactPhysics3D
#include <reactphysics3d/reactphysics3d.h>
using namespace reactphysics3d;

// IrrKlang
#include <irrKlang.h>
using namespace irrklang;

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// GLM
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

typedef unsigned short u_short;
typedef unsigned int u_int;
typedef long long l_long;

#define FORCEINLINE __forceinline
#define SUPER __super
#define IS_BASE_OF(_base, _type) typename = enable_if_t<is_base_of_v<_base, _type>>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

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
enum FolderType
{
	SHADERS,
    CONTENT,
	TEXTURES,
};
void AssertDebug(const char* _exprStr, const bool _expr, const char* _msg, const char* _file, const int _line);
void AssertNoDebug(const char* _exprStr, const bool _expr, const char* _msg);
string GetPath(const FolderType& _folderType);
//u_int GetUniqueID()
//{
//	static u_int _id = 0;
//	return ++_id;
//}

template <typename Type, typename ...Args>
Type* Spawn(Args&&... _args)
{
    return new Type(forward<Args>(_args)...);
}

const float MACHINE_EPSILON = std::numeric_limits<float>::epsilon();
*/

#pragma once

#include <iostream>
#include <functional>
#include <filesystem>
#include <map>
#include <queue>


#define _USE_MATH_DEFINES // for C++
#include <math.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_ENABLE_EXPERIMENTAL //check to remove
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>


#include <set>

using namespace std;
using namespace filesystem;
using namespace glm;
using namespace Assimp;

typedef unsigned short u_short;
typedef unsigned int u_int;
typedef long long l_long;

//class SubclassOf;


#define FORCEINLINE __forceinline
#define SUPER __super
#define IS_BASE_OF(_base, _type) typename = enable_if_t<is_base_of_v<_base, _type>>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

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
enum FolderType
{
    SHADERS,
    CONTENT,
    TEXTURES,
};
void AssertDebug(const char* _exprStr, const bool _expr, const char* _msg, const char* _file, const int _line);
void AssertNoDebug(const char* _exprStr, const bool _expr, const char* _msg);
string GetPath(const FolderType& _folderType);
//u_int GetUniqueID()
//{
//    static u_int _id = 0;
//    return ++_id;
//}

template <typename Type, typename ...Args>
Type* Spawn(Args&&... _args)
{
    return new Type(forward<Args>(_args)...);
}

//template <typename Type>
//Type* Spawn(const SubclassOf<Type>& _ref)
//{
//    return new Type(_ref.GetObject());
//}


const float MACHINE_EPSILON = std::numeric_limits<float>::epsilon();
