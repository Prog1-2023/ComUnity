#pragma once

#include "../Utils/CoreMinimal.h"
#include "Widget.h"
#include "../Utils/Event.h"

class Actor;

class HierarchyWidget : public Widget
{
	int selectedActorIndex;
	Event<void, Actor*> onActorSelected;
	Event<void, Actor*> onActorDeleteAction; 	

public:
	FORCEINLINE Event<void, Actor*>& OnActorSelected() { return onActorSelected; }
	FORCEINLINE Event<void, Actor*>& OnActorDeleteAction() { return onActorDeleteAction; }

public:
	HierarchyWidget(const bool& _openedByDefault);
	virtual ~HierarchyWidget() = default;

public:
	void Draw() override;
};