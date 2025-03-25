#pragma once

#include "../Utils/CoreMinimal.h"
#include "Widget.h"

class ContentWidget : public Widget
{
	
public:
	ContentWidget(const bool& _openedByDefault);
	virtual ~ContentWidget() = default;

public:
	void Draw() override;
};