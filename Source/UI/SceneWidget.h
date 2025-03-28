#pragma once

#include "../Utils/CoreMinimal.h"
#include "Widget.h"
#include "../Utils/Event.h"

class SceneWidget : public Widget
{
	Event<void, int> onDroppedElement;
	unsigned int textureColorBuffer;

public:
	FORCEINLINE Event<void, int>& OnDroppedElement() { return onDroppedElement; }
	FORCEINLINE void SetTextureColorBuffer(unsigned int _tcb) { textureColorBuffer = _tcb; }

public:
	SceneWidget(const bool& _openedByDefault);
	void UpdateFocus(bool _gameStatus);
	virtual ~SceneWidget() = default;

public:
	void Draw() override;
};