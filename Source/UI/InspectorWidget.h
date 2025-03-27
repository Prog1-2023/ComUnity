#pragma once

#include "../Utils/CoreMinimal.h"
#include "Widget.h"
#include "../Actors/Actor.h"

struct SerializedValue;

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
	bool DrawFromType(SerializedValue* _value);
	void DrawFromComplexeClass(vector<std::any> _vector);
	void DrawIntOutput(SerializedValue* _value);;
	void DrawFloatOutput(SerializedValue* _value);
	void DrawBoolOutput(SerializedValue* _value);

};