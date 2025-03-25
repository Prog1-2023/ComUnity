#include "UIImage.h"

UIImage::UIImage(const ImTextureID& _textureID, const ImVec2& _imageSize)
{
	texture = _textureID;
	imageSize = _imageSize;
}

void UIImage::Draw()
{
	Image(texture, imageSize);
}