#pragma once

#include "../Utils/CoreMinimal.h"
#include "Widget.h"

class InspectorWidget : public Widget
{
	
public:
	InspectorWidget(const bool& _openedByDefault);
	virtual ~InspectorWidget() = default;

public:
	void Draw() override;
};