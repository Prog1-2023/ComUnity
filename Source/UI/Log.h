#pragma once
//#include "../Utils/CoreMinimal.h"
#include "../Manager/Singleton.h"
#include "../Utils/Event.h"

class Log
{
private:
    Log_Severity severity;
    string text;

public:
    Log(Log_Severity _severity, const string& _text);

    Log_Severity GetSeverity() const { return severity; }
    const string& GetText() const { return text; }

    string GetFullText() const;

    ImVec4 GetColor() const;

private:
    string GetSeverityString(Log_Severity _severity) const;
};

//=========================================================================

class Logger : public Singleton<Logger>
{
    Event<> onNewLog;
    vector<Log> logs;

public :
    Event<>& OnNewLog() { return onNewLog; }
    vector<Log> GetLogs() const { return logs; }

public:
    void LogMessage(const string& _message, Log_Severity _type, const char* _file, int _line);
    void ClearLogs();
};