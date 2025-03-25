#pragma once
#include "../Utils/CoreMinimal.h"
#include "UIElement.h"

class UIImage : public UIElement
{

public:
	UIImage(World* _world, const string& _name);
	~UIImage();

public:
	virtual void Draw() override;
};