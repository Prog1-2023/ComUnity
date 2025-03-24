#include "UIElement.h"

UIElement::UIElement(World* _world, const string& _name) : Actor(_world)
{
	name = _name;
	transform = new TransformComponent(this);
}

UIElement::~UIElement()
{

}
