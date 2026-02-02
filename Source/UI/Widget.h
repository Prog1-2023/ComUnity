#pragma once

#include "../Utils/CoreMinimal.h"

class Widget
{
	string widgetName;
	bool isActive = true;
	
public:
	FORCEINLINE string GetWidgetName() const { return widgetName; }
	FORCEINLINE bool& GetIsActiveRef() { return isActive; }
	FORCEINLINE void SetIsActive(const bool& _newValue) { isActive = _newValue; }
	FORCEINLINE void ToggleIsActive() { isActive = !isActive; }

public:
	Widget(const string& _widgetName, const bool& _openedByDefault);
	virtual ~Widget() = default;

private:
	void Register();

public:
	virtual void Draw() = 0;
};