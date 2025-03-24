#pragma once

#include "../Utils/CoreMinimal.h"
#include "Widget.h"

class ConsoleWidget : public Widget
{
	
public:
	ConsoleWidget();
	virtual ~ConsoleWidget() = default;

public:
	void Draw() override;
};