#include "Macro.h"
#include "direct.h"
#include <filesystem>
#include "../UI/Log.h"

void AssertDebug(const char* _exprStr, const bool _expr, const char* _msg, const char* _file, const int _line)
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