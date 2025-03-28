#pragma once

#include "../Utils/CoreMinimal.h"
#include "Widget.h"
#include "Event.h"

class SceneWidget : public Widget
{
	Event<void, int> onDroppedElement;

public:
	FORCEINLINE Event<void, int>& OnDroppedElement() { return onDroppedElement; }

public:
	SceneWidget(const bool& _openedByDefault);
	void UpdateFocus(bool _gameStatus);
	virtual ~SceneWidget() = default;

public:
	void Draw() override;
};