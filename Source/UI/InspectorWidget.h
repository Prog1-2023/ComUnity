#pragma once

#include "../Utils/CoreMinimal.h"
#include "Widget.h"
#include "../Actors/Actor.h"
#include "../Serialization/Serialization.h"


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
	void DrawFromComplexeClass(Array<ValueAttachedToObject*> _serializedValues, SerializedValue* _value);
	void DrawIntOutput(SerializedValue* _intValue);;
	void DrawFloatOutput(SerializedValue* _floatValue);
	void DrawBoolOutput(SerializedValue* _boolValue);
	void DrawDoubleOutput(SerializedValue* _doubleValue);

};