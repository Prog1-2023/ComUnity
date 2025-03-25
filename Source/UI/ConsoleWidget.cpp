#include "ConsoleWidget.h"
#include <iostream>

ConsoleWidget::ConsoleWidget(const bool& _openedByDefault)
    :Widget("Console", _openedByDefault), toggleWarning(true), toggleError(true), toggleLog(true), clear(false)
{
    elements.push_back({ "Warnings", &toggleWarning, ImVec4(1.0f, 1.0f, 0.0f, 1.0f), ImVec4(0.5f, 0.5f, 0.5f, 1.0f) });
    elements.push_back({ "Errors", &toggleError, ImVec4(1.0f, 0.0f, 0.0f, 1.0f), ImVec4(0.5f, 0.5f, 0.5f, 1.0f) });
    elements.push_back({ "Logs", &toggleLog, ImVec4(0.0f, 1.0f, 0.0f, 1.0f), ImVec4(0.5f, 0.5f, 0.5f, 1.0f) });
}

void ConsoleWidget::Draw()
{
    Begin("Console");

    for (size_t i = 0; i < elements.size(); ++i)
    {
        DrawButton(elements[i]);
        if (i < elements.size() - 1)
            SameLine();
    }

    for (const string& _log : logs)
    {
        if ((_log.find("WARNING:") != string::npos && toggleWarning) ||
            (_log.find("ERROR:") != string::npos && toggleError) ||
            (_log.find("LOG:") != string::npos && toggleLog))
        {
            Text("%s", _log.c_str());
        }
    }

    if (Button("Clear"))
    {
        logs.clear();
    }

    End();
}


void ConsoleWidget::DrawButton(const ButtonConsoleElement& _button)
{
    PushStyleColor(ImGuiCol_Button, *_button.toggleState ? _button.activeColor : _button.inactiveColor);
    if (Button(_button.label))
    {
        *_button.toggleState = !(*_button.toggleState);
    }
    PopStyleColor();
}

void ConsoleWidget::AddLog(const string& _message, LogType _type)
{
    string _logMessage;

    switch (_type)
    {
    case WARNING:
        _logMessage = "WARNING: " + _message;
        break;
    case ERROR:
        _logMessage = "ERROR: " + _message;
        break;
    case LOG:
        _logMessage = "LOG: " + _message;
        break;
    }

    logs.push_back(_logMessage);

    cout << _logMessage << endl;
}
