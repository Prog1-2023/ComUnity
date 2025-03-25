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

//string GetAbsolutePath()
//{
//    const size_t size = 1024;
//    char buffer[size];
//
//    if (getcwd(buffer, size) != NULL)
//    {
//        string path = string(buffer);
//
//        size_t pos = path.find("ComUnity");
//        if (pos != string::npos)
//        {
//            string fixedPath = path.substr(0, pos + 7);
//
//            replace(fixedPath.begin(), fixedPath.end(), '/', '\\');
//
//            return fixedPath;
//        }
//        else
//        {
//            cerr << "The 'ComUnity' folder was not found in the current path." << endl;
//        }
//    }
//    else
//    {
//        cerr << "Error while retrieving the current directory." << endl;
//    }
//
//    return "";
//}

string GetAbsolutePath()
{
	path _path = current_path();

	path::iterator _it = find(_path.begin(), _path.end(), "ComUnity");
	if (_it != _path.end())
	{
		path _fixedPath;
		for (path::iterator _pathPart = _path.begin(); _pathPart != _it; ++_pathPart)
		{
			_fixedPath /= *_pathPart;
		}
		_fixedPath /= "ComUnity";

		return _fixedPath.string();
	}

    cerr << "The 'ComUnity' folder was not found in the current path." << endl;
    return "";
}

void LogMessage(const string& _message, LogType _type, const char* _file, int _line)
{
	string _logMessage;
	switch (_type)
	{
	case WARNING:
		_logMessage = "Log Warning: ";
		break;
	case ERROR:
		_logMessage = "Log Error: ";
		break;
	case LOG:
		_logMessage = "Log Temp: ";
		break;
	}

	_logMessage += _message + " (" + _file + ":" + to_string(_line) + ")";

	switch (_type)
	{
	case WARNING:
		TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), _logMessage.c_str());
		break;
	case ERROR:
		TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), _logMessage.c_str());
		break;
	case LOG:
		Text(_logMessage.c_str());
		break;
	}
}
