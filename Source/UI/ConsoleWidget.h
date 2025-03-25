#pragma once

#include "../Utils/CoreMinimal.h"
#include "Widget.h"

class ConsoleWidget : public Widget
{
	
public:
	ConsoleWidget(const bool& _openedByDefault);
	virtual ~ConsoleWidget() = default;

public:
	void Draw() override;
};