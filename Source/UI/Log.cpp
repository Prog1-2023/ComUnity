#include "Log.h"

Log::Log(double _time, Log_Severity _severity, const string& _text)
    : time(_time), severity(_severity), text(_text) 
{
}

string Log::GetFullText() const
{
    return string("[") + to_string(time) + "] " + GetSeverityString(severity) + ": " + text;
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

LogGroup::LogGroup(const string& _text, const string& _fullText, ImVec4 _color)
{
    Text = _text;
    FullText = _fullText;
    Color = _color;
    count = 1;
}

bool LogGroup::IsEquals(const string& _text) const
{
    return Text == _text;
}
