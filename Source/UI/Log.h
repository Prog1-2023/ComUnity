#pragma once

#include "../Utils/CoreMinimal.h"
#include "Log.h"

class Log
{
private:
    double time;
    Log_Severity severity;
    string text;

public:
    Log(double _time, Log_Severity _severity, const string& _text);

    Log_Severity GetSeverity() const { return severity; }
    const string& GetText() const { return text; }

    string GetFullText() const;

    ImVec4 GetColor() const;

private:
    string GetSeverityString(Log_Severity _severity) const;
};


class LogGroup
{
public:
    int count;
    string Text;
    string FullText;
    ImVec4 Color;

public:
    LogGroup(const string& _text, const string& _fullText, ImVec4 _color);

    bool IsEquals(const string& _text) const;
};