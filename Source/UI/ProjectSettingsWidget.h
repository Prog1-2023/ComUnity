#pragma once

#include "../Utils/CoreMinimal.h"
#include "Widget.h"

class ProjectSettingsWidget : public Widget
{
	
public:
	ProjectSettingsWidget(const bool& _openedByDefault);
	virtual ~ProjectSettingsWidget() = default;

public:
	void Draw() override;
};