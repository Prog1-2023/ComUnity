#pragma once

#include "../Utils/CoreMinimal.h"
#include "Widget.h"

class SceneWidget : public Widget
{
	
public:
	SceneWidget(const bool& _openedByDefault);
	virtual ~SceneWidget() = default;

public:
	void Draw() override;
};