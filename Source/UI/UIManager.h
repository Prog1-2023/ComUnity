#pragma once

#include "../Utils/CoreMinimal.h"
#include "Singleton.h"
#include "Toolbar.h"

class Widget;

class UIManager : public Singleton<UIManager>
{
	map<string, Widget*> allWidgets;
	Toolbar toolbar;

public:
	UIManager();
	virtual ~UIManager();

private:
	void InitPanels();

public:
	void Init(GLFWwindow* _window);
	void StartLoop();
	void EndLoop();
	void Destroy();
	void RegisterWidget(const string& _widgetName, Widget* _widget);
	void DrawAll();
	void OpenPanel(const string& _widgetName);
	void ClosePanel(const string& _widgetName);
	void TogglePanel(const string& _widgetName);
};