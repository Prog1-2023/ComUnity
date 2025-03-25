#pragma once

#include "../Utils/CoreMinimal.h"
#include "Widget.h"
#include "Event.h"

struct SpawnActorTab
{
	map<string, Event<>> actorList;
};

class SpawnActorWidget : public Widget
{

	map<string, SpawnActorTab> tabList;
	string currentOpenedTab;
	
public:
	SpawnActorWidget(const bool& _openedByDefault);
	virtual ~SpawnActorWidget() = default;

public:
	void Draw() override;
};