#include "EditorPreferencesWidget.h"

EditorPreferencesWidget::EditorPreferencesWidget(const bool& _openedByDefault) : Widget("Editor Preferences", _openedByDefault),
themes{ "Dark" , "Light" , "Darker-Purple", "Custom" }
{
	selectedTheme = 0;

	customTheme.push_back(CustomThemeData("Text color", ImGuiCol_Text, { 1.0f, 1.0f, 1.0f, 1.0f }));
	customTheme.push_back(CustomThemeData("Disabled Text color", ImGuiCol_Text, { 0.5f, 0.5f, 0.5f, 1.0f }));
	customTheme.push_back(CustomThemeData("Background color 1", ImGuiCol_WindowBg, { 0.0f, 0.0f, 0.0f, 1.0f }));
	customTheme.push_back(CustomThemeData("Background color 2", ImGuiCol_ChildBg, { 0.0f, 0.0f, 0.0f, 1.0f }));
	customTheme.push_back(CustomThemeData("Popup Background color", ImGuiCol_PopupBg, { 0.0f, 0.0f, 0.0f, 1.0f }));
	customTheme.push_back(CustomThemeData("Border color", ImGuiCol_Border, { 0.0f, 0.0f, 0.0f, 1.0f }));
	customTheme.push_back(CustomThemeData("Border Shadow color", ImGuiCol_BorderShadow, { 0.0f, 0.0f, 0.0f, 1.0f }));
	customTheme.push_back(CustomThemeData("Text Input Background color", ImGuiCol_FrameBg, { 0.5f, 0.5f, 0.5f, 1.0f }));
	customTheme.push_back(CustomThemeData("Hover Text Input Background color", ImGuiCol_FrameBgHovered, { 0.6f, 0.6f, 0.6f, 1.0f }));
	customTheme.push_back(CustomThemeData("Active Text Input Background color", ImGuiCol_FrameBgHovered, { 0.7f, 0.7f, 0.7f, 1.0f }));
	customTheme.push_back(CustomThemeData("Title Bar Background color", ImGuiCol_TitleBg, { 0.9f, 0.9f, 0.9f, 1.0f }));
	customTheme.push_back(CustomThemeData("Active Title Bar Background color", ImGuiCol_TitleBgActive, { 1.0f, 1.0f, 1.0f, 1.0f }));
	customTheme.push_back(CustomThemeData("Collapsed Title Bar Background color", ImGuiCol_TitleBgActive, { 0.5f, 0.5f, 0.5f, 1.0f }));
	customTheme.push_back(CustomThemeData("Menu Bar Background color", ImGuiCol_MenuBarBg, { 1.0f, 1.0f, 1.0f, 1.0f }));
	customTheme.push_back(CustomThemeData("Scroll Bar Background color", ImGuiCol_ScrollbarBg, { 1.0f, 1.0f, 1.0f, 1.0f }));
	customTheme.push_back(CustomThemeData("Scroll Bar Grab color", ImGuiCol_ScrollbarGrab, { 0.8f, 0.8f, 0.8f, 1.0f }));
	customTheme.push_back(CustomThemeData("Hover Scroll Bar Grab color", ImGuiCol_ScrollbarGrabHovered, { 0.9f, 0.9f, 0.9f, 1.0f }));
	customTheme.push_back(CustomThemeData("Active Scroll Bar Grab color", ImGuiCol_ScrollbarGrabActive, { 0.7f, 0.7f, 0.7f, 1.0f }));
	customTheme.push_back(CustomThemeData("Checkmark color", ImGuiCol_CheckMark, { 1.0f, 1.0f, 1.0f, 1.0f }));
	customTheme.push_back(CustomThemeData("Slider Grab color", ImGuiCol_SliderGrab, { 1.0f, 1.0f, 1.0f, 1.0f }));
	customTheme.push_back(CustomThemeData("Active Slider Grab color", ImGuiCol_SliderGrabActive, { 0.8f, 0.8f, 0.8f, 1.0f }));
	customTheme.push_back(CustomThemeData("Button color", ImGuiCol_Button, { 0.2f, 0.2f, 0.2f, 1.0f }));
	customTheme.push_back(CustomThemeData("Hover Button color", ImGuiCol_ButtonHovered, { 0.3f, 0.3f, 0.3f, 1.0f }));
	customTheme.push_back(CustomThemeData("Active Button color", ImGuiCol_ButtonActive, { 0.1f, 0.1f, 0.1f, 1.0f }));
	customTheme.push_back(CustomThemeData("Header color", ImGuiCol_Header, { 0.8f, 0.8f, 0.8f, 1.0f }));
	customTheme.push_back(CustomThemeData("Hover Header color", ImGuiCol_HeaderHovered, { 0.9f, 0.9f, 0.9f, 1.0f }));
	customTheme.push_back(CustomThemeData("Active Header color", ImGuiCol_HeaderActive, { 0.7f, 0.7f, 0.7f, 1.0f }));
	customTheme.push_back(CustomThemeData("Separator color", ImGuiCol_Separator, { 0.9f, 0.9f, 0.9f, 1.0f }));
	customTheme.push_back(CustomThemeData("Hover Separator color", ImGuiCol_SeparatorHovered, { 1.0f, 1.0f, 1.0f, 1.0f }));
	customTheme.push_back(CustomThemeData("Active Separator color", ImGuiCol_SeparatorActive, { 0.8f, 0.8f, 0.8f, 1.0f }));
	customTheme.push_back(CustomThemeData("Resize Grip color", ImGuiCol_ResizeGrip, { 0.9f, 0.9f, 0.9f, 1.0f }));
	customTheme.push_back(CustomThemeData("Hover Resize Grip color", ImGuiCol_ResizeGripHovered, { 1.0f, 1.0f, 1.0f, 1.0f }));
	customTheme.push_back(CustomThemeData("Active Resize Grip color", ImGuiCol_ResizeGripActive, { 0.8f, 0.8f, 0.8f, 1.0f }));
	customTheme.push_back(CustomThemeData("Input Text Cursor color", ImGuiCol_InputTextCursor, { 0.5f, 0.5f, 0.5f, 1.0f }));
	customTheme.push_back(CustomThemeData("Tab color", ImGuiCol_Tab, { 1.0f, 1.0f, 1.0f, 1.0f }));
	customTheme.push_back(CustomThemeData("Hover Tab color", ImGuiCol_TabHovered, { 0.9f, 0.9f, 0.9f, 1.0f }));
	customTheme.push_back(CustomThemeData("Selected Tab color", ImGuiCol_TabSelected, { 0.8f, 0.8f, 0.8f, 1.0f }));
	customTheme.push_back(CustomThemeData("Selected Overline Tab color", ImGuiCol_TabSelected, { 0.7f, 0.7f, 0.7f, 1.0f }));
	customTheme.push_back(CustomThemeData("Dimmed Tab color", ImGuiCol_TabDimmed, { 0.5f, 0.5f, 0.5f, 1.0f }));
	customTheme.push_back(CustomThemeData("Dimmed Selected Tab color", ImGuiCol_TabDimmedSelected, { 0.6f, 0.6f, 0.6f, 1.0f }));
	customTheme.push_back(CustomThemeData("Dimmed Selected Overline Tab color", ImGuiCol_TabDimmedSelectedOverline, { 0.4f, 0.4f, 0.4f, 1.0f }));
	customTheme.push_back(CustomThemeData("Docking Preview color", ImGuiCol_DockingPreview, { 1.0f, 1.0f, 1.0f, 1.0f }));
	customTheme.push_back(CustomThemeData("Docking Empty color", ImGuiCol_DockingEmptyBg, { 0.8f, 0.8f, 0.8f, 1.0f }));
	customTheme.push_back(CustomThemeData("Plot Lines color", ImGuiCol_PlotLines, { 1.0f, 1.0f, 1.0f, 1.0f }));
	customTheme.push_back(CustomThemeData("Hover Plot Lines color", ImGuiCol_PlotLinesHovered, { 0.8f, 0.8f, 0.8f, 1.0f }));
	customTheme.push_back(CustomThemeData("Plot Histogram color", ImGuiCol_PlotHistogram, { 1.0f, 1.0f, 1.0f, 1.0f }));
	customTheme.push_back(CustomThemeData("Hover Plot Histogram color", ImGuiCol_PlotHistogramHovered, { 0.8f, 0.8f, 0.8f, 1.0f }));
	customTheme.push_back(CustomThemeData("Table Header color", ImGuiCol_TableHeaderBg, { 0.8f, 0.8f, 0.8f, 1.0f }));
	customTheme.push_back(CustomThemeData("Table Border Strong color", ImGuiCol_TableBorderStrong, { 1.0f, 1.0f, 1.0f, 1.0f }));
	customTheme.push_back(CustomThemeData("Table Border Light color", ImGuiCol_TableBorderLight, { 0.6f, 0.6f, 0.6f, 1.0f }));
	customTheme.push_back(CustomThemeData("Table Row Background color 1", ImGuiCol_TableRowBg, { 1.0f, 1.0f, 1.0f, 1.0f }));
	customTheme.push_back(CustomThemeData("Table Row Background color 2", ImGuiCol_TableRowBgAlt, { 0.6f, 0.6f, 0.6f, 1.0f }));
	customTheme.push_back(CustomThemeData("Text Link color", ImGuiCol_TextLink, { 0.8f, 0.8f, 1.0f, 1.0f }));
	customTheme.push_back(CustomThemeData("Selected Text Background color", ImGuiCol_TextSelectedBg, { 0.7f, 0.7f, 1.0f, 1.0f }));
	customTheme.push_back(CustomThemeData("Drag Drop Target color", ImGuiCol_DragDropTarget, { 0.7f, 0.7f, 0.7f, 1.0f }));
	customTheme.push_back(CustomThemeData("Nav Cursor color", ImGuiCol_NavCursor, { 0.7f, 1.0f, 0.7f, 1.0f }));
	customTheme.push_back(CustomThemeData("Nav Windowing Highlight color", ImGuiCol_NavWindowingHighlight, { 1.0f, 0.7f, 0.7f, 1.0f }));
	customTheme.push_back(CustomThemeData("Nav Windowing Dimmed color", ImGuiCol_NavWindowingDimBg, { 0.5f, 0.7f, 0.7f, 1.0f }));
	customTheme.push_back(CustomThemeData("Modal Window Dimmed color", ImGuiCol_ModalWindowDimBg, { 0.2f, 0.2f, 0.2f, 1.0f }));
}

void EditorPreferencesWidget::DrawCustomStyleSettings()
{
	const unsigned int& _amount = static_cast<const unsigned int>(customTheme.size());
	for (unsigned int _index = 0; _index < _amount; _index++)
	{
		CustomThemeData& _data = customTheme[_index];
		CustomColor(_data.title, _data.color, _data.type);
	}
}

void EditorPreferencesWidget::CustomColor(const string& _colorTitle, float* _color, const ImGuiCol_& _type)
{
	Text(_colorTitle.c_str());
	SameLine();
	SetNextItemWidth(200.0f);
	ImGuiStyle& _style = GetStyle();
	if (ColorEdit3(_colorTitle.c_str(), _color, ImGuiColorEditFlags_NoLabel))
		_style.Colors[_type] = ImVec4(_color[0], _color[1], _color[2], 1.0f);
}

void EditorPreferencesWidget::LoadCustomStyle()
{
	ImGuiStyle& _style = GetStyle();
	const unsigned int& _amount = static_cast<const unsigned int>(customTheme.size());
	for (unsigned int _index = 0; _index < _amount; _index++)
	{
		const CustomThemeData& _data = customTheme[_index];
		_style.Colors[_data.type] = _data.GetColor();
	}
}

void EditorPreferencesWidget::Draw()
{
	Text("Editor style");
	SameLine();
	SetNextItemWidth(150.0f);
	if (Combo("##", &selectedTheme, themes, IM_ARRAYSIZE(themes)))
	{
		if (selectedTheme == 0) StyleColorsDark();
		else if (selectedTheme == 1) StyleColorsLight();
		else if (selectedTheme == 2) StyleColorsClassic();
		else if (selectedTheme == 3) LoadCustomStyle();
	}
	Separator();
	BeginDisabled(selectedTheme != 3);
	DrawCustomStyleSettings();
	EndDisabled();
}

