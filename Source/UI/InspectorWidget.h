#pragma once

#include "../Utils/CoreMinimal.h"
#include "Widget.h"
#include "../Actors/Actor.h"


class InspectorWidget : public Widget
{	
	Actor* currentSelectedActor;

public:
	InspectorWidget(const bool& _openedByDefault);
	virtual ~InspectorWidget() = default;

public:
	FORCEINLINE void SetCurrentActor(Actor* _actor)
	{
		currentSelectedActor = _actor;
	}

public:
	void Draw() override;
	void DrawComponents();

private:
	void ChangeValue();

};