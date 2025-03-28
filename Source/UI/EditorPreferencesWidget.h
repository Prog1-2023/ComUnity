#pragma once
#include "../Utils/CoreMinimal.h"
#include "Widget.h"
#include "FileManager.h"

struct CustomThemeData
{
	string title;
	ImGuiCol_ type;
	float color[4];

public:
	CustomThemeData()
	{

	}
	CustomThemeData(const string& _title, const ImGuiCol_& _type, const ImVec4& _defaultColor)
	{
		title = _title;
		type = _type;
		color[0] = _defaultColor.x;
		color[1] = _defaultColor.y;
		color[2] = _defaultColor.z;
		color[3] = _defaultColor.w;
	}

public:
	ImVec4 GetColor() const
	{
		return ImVec4(color[0], color[1], color[2], color[3]);
	}
};

class EditorPreferencesWidget : public Widget
{
	vector<CustomThemeData> customTheme;
	int selectedTheme;
	const char* themes[4];
	SaveData editorSave;

public:
	EditorPreferencesWidget(const bool& _openedByDefault);
	virtual ~EditorPreferencesWidget() = default;

private:
	void LoadCustomColors();
	void DrawCustomStyleSettings();
	void CustomColor(const string& _colorTitle, float* _color, const ImGuiCol_& _type);
	void LoadCustomStyle();
	void UpdateTheme();

public:
	void Draw() override;
};