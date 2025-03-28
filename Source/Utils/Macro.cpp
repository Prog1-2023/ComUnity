#include "Macro.h"
#include "direct.h"
#include <filesystem>
#include "../UI/Log.h"

string GetPath(const FolderType& _folderType)
{
	const path& _currentPath = current_path();
	path _shaderPath = _currentPath.parent_path();

	switch (_folderType)
	{
	case SHADERS:
		_shaderPath /= "Source/Shaders/";
		break;
	case CONTENT:
		_shaderPath /= "Content/";
		break;
	case TEXTURES:
		_shaderPath /= "Content/Textures/";
		break;
	default:
		break;
	}

	return _shaderPath.string();
}

void AssertDebug(const char* _exprStr, const bool _expr, const char* _msg,  const char* _file, const int _line)
{
	if (!_expr)
	{
		LOG_ERROR(string("Assert failed:\t") + _msg + "\n"
			+ "Expected:\t" + _exprStr + "\n"
			+ "Source:\t\t" + _file + ", line " + to_string(_line));

		abort();
	}
}

void AssertNoDebug(const char* _exprStr, const bool _expr, const char* _msg)
{
	if (!_expr)
	{
		LOG_ERROR(string("Assert failed:\t") + _msg + "\n"
			+ "Expected:\t" + _exprStr);

		abort();
	}
}
