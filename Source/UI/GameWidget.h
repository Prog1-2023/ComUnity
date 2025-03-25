#pragma once

#include "../Utils/CoreMinimal.h"
#include "Widget.h"

class GameWidget : public Widget
{
	
public:
	GameWidget(const bool& _openedByDefault);
	virtual ~GameWidget() = default;

public:
	void Draw() override;
};