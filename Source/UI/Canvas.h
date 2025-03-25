#pragma once
#include "../Utils/CoreMinimal.h"
#include "UIElement.h"

class UILayout;

class Canvas : public UIElement
{
	vector<UIElement*> allElements;
	UILayout* layout;
	bool isVisible;
	string canvasName;

public:
	Canvas(const string& _canvasName);
	virtual ~Canvas();

public:
	void Add(UIElement* _element)
	{
		if (_element == this) return;

		allElements.push_back(_element);
	}
	void Remove(UIElement* _elementToDestroy)
	{
		for (vector<UIElement*>::iterator _it = allElements.begin(); _it != allElements.end(); _it++)
		{
			if (*_it == _elementToDestroy)
			{
				allElements.erase(_it);
				return;
			}
		}
	}

public:
	virtual void Draw() override;
};