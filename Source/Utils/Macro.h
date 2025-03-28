#pragma once

#include <iostream>
#include <filesystem>
#include <map>

//INCLUDE P1
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <functional>
#include <typeindex>
#include <typeinfo>
#include <exception>
#include <random>
#include <filesystem>
#include <any>

#include <math.h>
#include <conio.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLM_ENABLE_EXPERIMENTAL //check to remove
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

typedef unsigned short u_short;
typedef unsigned int u_int;
typedef long long l_long;

//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
//#define FORCEINLINE __forceinline
//#define SUPER __super
//#define DEBUG_PATH
//#ifdef DEBUG_PATH
#define PATH __FUNCTION__

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define SUPER __super
#define Super __super
#define FILE_NAME (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define DEBUG_INFO "(File: " + CAST(string, PATH) + " | Line: " + to_string(__LINE__) + ")"
#define FORCEINLINE __forceinline
#define INLINE __inline
#define CAST(_type, _expr) static_cast<_type>(_expr)
#define SLEEP(_duration) sleep(_duration)
#define NO_DISCARD _NODISCARD
#define SAME_VALUE(_first, _second) is_same_v<_first, _second>
#define ENABLE_IF(_element) enable_if_t<_element>
#define IS_BASE_OF(_base, _type) typename = enable_if_t<is_base_of_v<_base, _type>>
#define TYPE(_type) decay_t<decltype(_type)>
#define TYPE_ID(_type) typeid(_type)
#define TYPE_NAME(_type) CAST(string, TYPE_ID(_type).name())
#define TYPE_INDEX_NAME(_typeIndex) CAST(string, _typeIndex.name())

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


#define IS_BASE_OF(_base, _type) typename = enable_if_t<is_base_of_v<_base, _type>>

template <typename Type, typename BaseType, IS_BASE_OF(BaseType, Type)>
Type* Cast(BaseType * _baseType)
{
	if (!_baseType) return nullptr;
	return dynamic_cast<Type*>(_baseType);
}

void AssertDebug(const char* _exprStr, const bool _expr, const char* _msg, const char* _file, const int _line);
void AssertNoDebug(const char* _exprStr, const bool _expr, const char* _msg);

enum FolderType
{
	SHADERS,
	CONTENT,
	TEXTURES,
};

string GetPath(const FolderType& _folderType);

const float MACHINE_EPSILON = std::numeric_limits<float>::epsilon();