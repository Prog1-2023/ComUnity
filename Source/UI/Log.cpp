#include "Log.h"

Log::Log(Log_Severity _severity, const string& _text)
    : severity(_severity), text(_text) 
{
}

string Log::GetFullText() const
{
    return GetSeverityString(severity) + ": " + text;
}


ImVec4 Log::GetColor() const
{
    switch (severity)
    {
    case LOG:
        return ImVec4(1.0f, 1.0f, 1.0f, 1.0f);  // White
    case WARNING:
        return ImVec4(1.0f, 0.35f, 0.0f, 1.0f); // Orange
    case ERROR:
        return ImVec4(1.0f, 0.0f, 0.0f, 1.0f);  // Red
    default:
        return ImVec4(1.0f, 1.0f, 1.0f, 1.0f);  // White default
    }
}

string Log::GetSeverityString(Log_Severity _severity) const
{
    switch (_severity)
    {
    case LOG:
        return "LOG";
    case WARNING:
        return "WARNING";
    case ERROR:
        return "ERROR";
    default:
        return "";
    }
}

void Logger::LogMessage(const string& _message, Log_Severity _type, const char* _file, int _line)
{
    string _typeStr;
    ImVec4 _color;

    switch (_type)
    {
    case WARNING:
        _typeStr = "WARNING";
        _color = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
        break;
    case ERROR:
        _typeStr = "ERROR";
        _color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
        break;
    case LOG:
        _typeStr = "LOG";
        _color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        break;
    }

    string _fullMessage = "[" + _typeStr + "] (" + _file + ":" + std::to_string(_line) + ") " + _message;
    Log _log(_type, _fullMessage);
    logs.push_back(_log);
    onNewLog.Invoke();
}

void Logger::ClearLogs()
{
    logs.clear();
}
