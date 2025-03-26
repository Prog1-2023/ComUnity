#include "Macro.h"
#include "direct.h"
#include <filesystem>

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