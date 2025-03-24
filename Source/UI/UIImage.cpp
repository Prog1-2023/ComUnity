#include "UIImage.h"

UIImage::UIImage(World* _world, const string& _name) : UIElement(_world, _name)
{

}

UIImage::~UIImage()
{

}

void UIImage::Draw()
{
	ImGui::Image(0,ImVec2(100,100));
}