#include "EditorPreferencesWidget.h"

EditorPreferencesWidget::EditorPreferencesWidget(const bool& _openedByDefault) : Widget("Editor Preferences", _openedByDefault),
themes{ "Dark" , "Light" , "Darker-Purple", "Custom" },
backgroundColor{ 0.0f, 0.0f, 0.0f },
textColor{ 0.0f, 0.0f, 0.0f },
buttonColor{ 0.0f, 0.0f, 0.0f },
hoverButtonColor{ 0.0f, 0.0f, 0.0f },
activeButtonColor{ 0.0f, 0.0f, 0.0f }
{
	selectedTheme = 0;
}

void EditorPreferencesWidget::UpdateTheme()
{
}

void EditorPreferencesWidget::DrawCustomStyleSettings()
{
	CustomColor("Background color", backgroundColor, ImGuiCol_WindowBg);
	CustomColor("Text color", textColor, ImGuiCol_Text);
	CustomColor("Button color", buttonColor, ImGuiCol_Button);
	CustomColor("Hover button color", hoverButtonColor, ImGuiCol_ButtonHovered);
	CustomColor("Active Button color", activeButtonColor, ImGuiCol_ButtonActive);
}

void EditorPreferencesWidget::CustomColor(const string& _colorTitle, float* _color, const ImGuiCol_& _type)
{
	Text(_colorTitle.c_str());
	SameLine();
	SetNextItemWidth(100.0f);
	ImGuiStyle& _style = GetStyle();
	if (ColorEdit3(_colorTitle.c_str(), _color, ImGuiColorEditFlags_NoLabel))
		_style.Colors[_type] = ImVec4(_color[0], _color[1], _color[2], 1.0f);
}

void EditorPreferencesWidget::Draw()
{
	Text("Editor style");
	SameLine();
	SetNextItemWidth(100.0f);
	if (Combo("##", &selectedTheme, themes, IM_ARRAYSIZE(themes)))
	{
		if (selectedTheme == 0) StyleColorsDark();
		else if (selectedTheme == 1) StyleColorsLight();
		else if (selectedTheme == 2) StyleColorsClassic();
	}
	Separator();
	BeginDisabled(selectedTheme != 3);
	DrawCustomStyleSettings();
	EndDisabled();
}

