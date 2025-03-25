#pragma once

#include "../Utils/CoreMinimal.h"
#include "Event.h"

class Toolbar
{
	Event<void, bool> onGameStatusChanged;
	vector<string> allToggleablePanels;
	bool isGameRunning;

public:
	FORCEINLINE void SetGameStatus(const bool& _isGameRunning) { isGameRunning = _isGameRunning; }

public:
	Toolbar();

public:
	void Draw();
};