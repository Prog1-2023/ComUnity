#include "Canvas.h"

Canvas::Canvas(const string& _canvasName) : UIElement()
{
	allElements = vector<UIElement*>();
	layout = nullptr;
	canvasName = _canvasName;
}

Canvas::~Canvas()
{
	delete layout;
}

void Canvas::Draw()
{
	if (isVisible)
	{
		Begin(canvasName.c_str(), &isVisible, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
		for (UIElement* _element : allElements)
			_element->Draw();
		End();
	}
}
