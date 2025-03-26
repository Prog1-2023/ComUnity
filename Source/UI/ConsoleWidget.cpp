#include "ConsoleWidget.h"
#include <iostream>
#include "UIText.h"

ConsoleWidget::ConsoleWidget(const bool& _openedByDefault)
    : Widget("Console", _openedByDefault), toggleWarning(true), toggleError(true), toggleLog(true), clear(false)
{
    elements.push_back({ "Warnings", &toggleWarning, ImVec4(1.0f, 1.0f, 0.0f, 1.0f), ImVec4(0.5f, 0.5f, 0.5f, 1.0f) });
    elements.push_back({ "Errors", &toggleError, ImVec4(1.0f, 0.0f, 0.0f, 1.0f), ImVec4(0.5f, 0.5f, 0.5f, 1.0f) });
    elements.push_back({ "Logs", &toggleLog, ImVec4(0.0f, 1.0f, 0.0f, 1.0f), ImVec4(0.5f, 0.5f, 0.5f, 1.0f) });

    logs.clear();
}

ConsoleWidget::~ConsoleWidget() = default;
void ConsoleWidget::Draw()
{
    Begin("Console");

    for (size_t i = 0; i < elements.size(); ++i)
    {
        DrawButton(elements[i]);
        SameLine();
        if (i >= elements.size() - 1)
            Separator();
    }

    for (const Log* _log : logs)
    {
        if ((_log->GetText().find("WARNING:") != string::npos && toggleWarning) ||
            (_log->GetText().find("ERROR:") != string::npos && toggleError) ||
            (_log->GetText().find("LOG:") != string::npos && toggleLog))
        {
            Text("%s", _log->GetText().c_str());
        }
    }

    if (Button("Clear"))
    {
        ClearLogs();
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

void ConsoleWidget::AddLog(const string& _message, Log_Severity _type)
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

    Log* log = new Log(GetCurrentTime(), _type, _logMessage);
    logs.push_back(log);

    LOG(_logMessage);           
    LOG_WARNING(_logMessage);   
    LOG_ERROR(_logMessage);    

    cout << _logMessage << endl;
}



void ConsoleWidget::ShowLogs()
{
    if (BeginChild("Console", ImVec2(0.0f, 0.0f), false, ImGuiWindowFlags_HorizontalScrollbar))
    {
        for (size_t i = 0; i < logs.size(); ++i)
        {
            const Log* log = logs[i]; 
            if ((log->GetText().find("WARNING:") != string::npos && toggleWarning) ||
                (log->GetText().find("ERROR:") != string::npos && toggleError) ||
                (log->GetText().find("LOG:") != string::npos && toggleLog))
            {
                Text("%s", log->GetText().c_str());
            }
        }

        if (autoScroll && GetScrollY() >= GetScrollMaxY())
        {
            SetScrollHereY(1.0f);
        }
    }

    EndChild();
}

vector<LogGroup*> ConsoleWidget::GetLogs()
{
    vector<LogGroup*> logGroups;

    for (const Log* log : logs)
    {
        string logText = log->GetText(); 
        string fullText = log->GetFullText(); 

        LogGroup* group = new LogGroup(logText, fullText, log->GetColor()); 
        logGroups.push_back(group);
    }

    return logGroups;
}


void ConsoleWidget::ClearLogs()
{
    logs.clear();
}

bool ConsoleWidget::IsFiltered(const Log_Severity& _severity, const string& _text)
{
    return IsSeverityFiltered(_severity) || filter.IsActive() && !filter.PassFilter(_text.c_str());
}

bool ConsoleWidget::IsSeverityFiltered(Log_Severity _severity)
{
    switch (_severity)
    {
    case LOG:
        return !showMessages;

    case WARNING:
        return !showWarnings;

    case ERROR:
        return !showErrors;
    }

    return false;
}
