#include "Macro.h"

void AssertDebug(const char* _exprStr, const bool _expr, const char* _msg, const char* _file, const int _line)
{
	if (!_expr)
	{
		cerr << "Assert failed:\t" << _msg << endl
			 << "Expected:\t" << _exprStr << endl
			 << "Source:\t\t" << _file << ", line " << _line << endl;
		abort();
	}
}

void AssertNoDebug(const char* _exprStr, const bool _expr, const char* _msg)
{
	if (!_expr)
	{
		cerr << "Assert failed:\t" << _msg << endl
			<< "Expected:\t" << _exprStr << endl;
		abort();
	}
}

string GetPath(const FolderType& _folderType)
{
	const path& _currentPath = current_path();
	path _path = _currentPath.parent_path();
	switch (_folderType)
	{
	case SHADERS:
		_path /= "Source/Shaders/";
		break;
	case CONTENT:
		_path /= "Content/";
		break;
	case TEXTURES:
		_path /= "Content/Textures/";
		break;
	}
	return _path.string();
}
