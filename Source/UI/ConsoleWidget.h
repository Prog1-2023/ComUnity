#pragma once

#include "../Utils/CoreMinimal.h"
#include "Widget.h"
#include "Log.h"

struct ButtonConsoleElement
{
    const char* label;
    bool* toggleState;
    ImVec4 activeColor;
    ImVec4 inactiveColor;
};

class ConsoleWidget : public Widget
{
private:
    bool toggleWarning;
    bool toggleError;
    bool toggleLog;
    bool clear;
    bool collapse;
    bool showMessages;
    bool showWarnings;
    bool showErrors;
    bool autoScroll;

    ImGuiTextFilter filter;

    vector<ButtonConsoleElement> elements;
    vector<Log*> logs;
    vector<ButtonConsoleElement> buttons;

public:
    ConsoleWidget(const bool& _openedByDefault);
    virtual ~ConsoleWidget();

    void Draw() override;

private:
    void DrawButton(const ButtonConsoleElement& _button);
    void ShowLogs();
    vector<LogGroup*> GetLogs();
    void ClearLogs();

    bool IsFiltered(const Log_Severity& _severity, const string& _text);
    bool IsSeverityFiltered(Log_Severity severity);

public:
    void AddLog(const string& _message, Log_Severity _type);

    double GetCurrentTime()
    {
        chrono::system_clock::time_point now = chrono::system_clock::now(); 
        chrono::duration<double> duration = chrono::duration_cast<chrono::duration<double>>(now.time_since_epoch());    
        return duration.count();
    }

};
