#pragma once

#include "../Utils/CoreMinimal.h"
#include "Widget.h"
#include "Event.h"

class SceneWidget : public Widget
{
	Event<void, string> onDroppedElement;

public:
	FORCEINLINE Event<void, string>& OnDroppedElement() { return onDroppedElement; }

public:
	SceneWidget(const bool& _openedByDefault);
	virtual ~SceneWidget() = default;

public:
	void Draw() override;
};