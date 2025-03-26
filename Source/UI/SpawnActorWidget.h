#pragma once

#include "../Utils/CoreMinimal.h"
#include "Widget.h"
#include "Event.h"

struct SpawnActorTab
{
	unordered_map<string, Event<>> actorList;
};

class SpawnActorWidget : public Widget
{

	unordered_map<string, SpawnActorTab> tabList;
	string currentOpenedTab;
	
public:
	SpawnActorWidget(const bool& _openedByDefault);
	virtual ~SpawnActorWidget() = default;

private:
	void ExecuteEvent(const string& _id);

public:
	void Draw() override;
};