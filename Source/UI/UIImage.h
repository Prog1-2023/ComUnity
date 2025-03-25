#pragma once

#include "../Utils/CoreMinimal.h"
#include "UIElement.h"

class UIImage : public UIElement
{
	ImVec2 imageSize;
	ImTextureID texture;

public:
	UIImage(const ImTextureID& _textureID, const ImVec2& _imageSize);
	virtual ~UIImage() = default;

public:
	virtual void Draw() override;
};
