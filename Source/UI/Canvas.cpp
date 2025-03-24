#include "Canvas.h"

Canvas::Canvas(World* _world, const string& _name) : UIElement(_world,_name)
{
	allElements = vector<UIElement*>();
	layout = nullptr;
}

Canvas::~Canvas()
{
	delete layout;
}

void Canvas::Draw()
{
	if (isDraw)
	{
		Begin(name.c_str(), &isDraw, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
		for (UIElement* _element : allElements)
		{
			_element->Draw();
		}
		End();
	}
}
