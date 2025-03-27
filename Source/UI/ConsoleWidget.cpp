#include "ConsoleWidget.h"
#include <iostream>
#include "UIText.h"

ConsoleWidget::ConsoleWidget(const bool& _openedByDefault)
    : Widget("Console", _openedByDefault), toggleWarning(true), toggleError(true), toggleLog(true), showMessages(true), showWarnings(true), showErrors(true)
{
    elements.push_back({ "Warnings", &toggleWarning, ImVec4(0.8f, 0.8f, 0.2f, 1.0f), ImVec4(0.3f, 0.3f, 0.1f, 1.0f) });
    elements.push_back({ "Errors", &toggleError, ImVec4(0.8f, 0.2f, 0.2f, 1.0f), ImVec4(0.3f, 0.1f, 0.1f, 1.0f) });
    elements.push_back({ "Logs", &toggleLog, ImVec4(0.2f, 0.8f, 0.2f, 1.0f), ImVec4(0.1f, 0.3f, 0.1f, 1.0f) });

    logs.clear();
    Logger::GetInstance().OnNewLog().Add(this, &ConsoleWidget::UpdateLogs);
}

void ConsoleWidget::Draw()
{
    for (size_t i = 0; i < elements.size(); ++i)
    {
        DrawButton(elements[i]);
        SameLine();
    }

    SameLine();
    if (Button("Clear"))
    {
        ClearLogs();
    }
    Separator();

    for (const Log& _log : logs)
    {
        if ((_log.GetSeverity() == WARNING && toggleWarning) ||
            (_log.GetSeverity() == ERROR && toggleError) ||
            (_log.GetSeverity() == LOG && toggleLog))
        {
            ImVec4 color;
            switch (_log.GetSeverity())
            {
            case WARNING:
                color = ImVec4(1.0f, 1.0f, 0.2f, 0.8f); // Yellow
                break;
            case ERROR:
                color = ImVec4(1.0f, 0.8f, 0.8f, 1.0f); // Red
                break;
            case LOG:
            default:
                color = ImVec4(0.8f, 1.0f, 0.8f, 1.0f); // Green
                break;
            }

            PushStyleColor(ImGuiCol_Text, color);
            Text("%s", _log.GetText().c_str());
            PopStyleColor();
        }
    }
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

void ConsoleWidget::ClearLogs()
{
    logs.clear();
    Logger::GetInstance().ClearLogs();
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

void ConsoleWidget::UpdateLogs()
{
    logs = Logger::GetInstance().GetLogs();
}
