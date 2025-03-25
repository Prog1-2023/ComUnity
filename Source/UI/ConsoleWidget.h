#pragma once

#include "../Utils/CoreMinimal.h"
#include "Widget.h"

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

    vector<ButtonConsoleElement> elements;
    vector<string> logs; 

public:
    ConsoleWidget(const bool& _openedByDefault);
    virtual ~ConsoleWidget() = default;

    void Draw() override;

private:
    void DrawButton(const ButtonConsoleElement& _button);

public:
    void AddLog(const string& _message, LogType _type);
};
