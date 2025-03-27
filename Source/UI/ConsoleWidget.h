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
    vector<Log> logs;

    bool toggleWarning;
    bool toggleError;
    bool toggleLog;
    bool showMessages;
    bool showWarnings;
    bool showErrors;

    ImGuiTextFilter filter;
    vector<ButtonConsoleElement> elements;

public:
    ConsoleWidget(const bool& _openedByDefault);
    virtual ~ConsoleWidget() = default;

    void Draw() override;

private:
    void DrawButton(const ButtonConsoleElement& _button);
    void ClearLogs();

    bool IsFiltered(const Log_Severity& _severity, const string& _text);
    bool IsSeverityFiltered(Log_Severity severity);
    void UpdateLogs();
};
