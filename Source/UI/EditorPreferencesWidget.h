#pragma once

#include "../Utils/CoreMinimal.h"
#include "Widget.h"

class EditorPreferencesWidget : public Widget
{
	
public:
	EditorPreferencesWidget(const bool& _openedByDefault);
	virtual ~EditorPreferencesWidget() = default;

public:
	void Draw() override;
};