#pragma once

#include "../Utils/CoreMinimal.h"
#include "Widget.h"
#include "Event.h"

class Actor;

class HierarchyWidget : public Widget
{
	int selectedActorIndex;
	Event<void, Actor*> onActorSelected;
	
public:
	FORCEINLINE Event<void, Actor*>& OnActorSelected() { return onActorSelected; }

public:
	HierarchyWidget(const bool& _openedByDefault);
	virtual ~HierarchyWidget() = default;

public:
	void Draw() override;
};