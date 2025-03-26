#pragma once

#include "../Utils/CoreMinimal.h"
#include "Widget.h"

class EditorPreferencesWidget : public Widget
{
	int selectedTheme;
	const char* themes[4];
	// CustomTheme
	float backgroundColor[3];
	float textColor[3];
	float buttonColor[3];
	float hoverButtonColor[3];
	float activeButtonColor[3];
	// CustomTheme

public:
	EditorPreferencesWidget(const bool& _openedByDefault);
	virtual ~EditorPreferencesWidget() = default;

private:
	void UpdateTheme();
	void DrawCustomStyleSettings();
	void CustomColor(const string& _colorTitle, float* _color, const ImGuiCol_& _type);

public:
	void Draw() override;
};