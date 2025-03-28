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

//template <typename Type, typename ...Args>
//Type* Spawn(Args&&... _args)
//{
//    return new Type(forward<Args>(_args)...);
//}

//template <typename Type>
//Type* Spawn(const SubclassOf<Type>& _ref)
//{
//    return new Type(_ref.GetObject());
//}


const float MACHINE_EPSILON = std::numeric_limits<float>::epsilon();
