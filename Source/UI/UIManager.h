#pragma once

#include "../Utils/CoreMinimal.h"
#include "../Manager/Singleton.h"
#include "Toolbar.h"
//#include "..\Editor\World.h"
#include "../Manager/Level.h"

class Widget;

class UIManager : public Singleton<UIManager>
{
	map<string, Widget*> allWidgets;
	Toolbar toolbar;
	GLFWwindow* window;
	Level* level;

public:	
	FORCEINLINE Level* GetLevel() const { return level; }
	FORCEINLINE GLFWwindow* GetWindow() const { return window; }
	FORCEINLINE Toolbar& GetToolbar() { return toolbar; }

public:
	UIManager();
	virtual ~UIManager();

private:
	void InitPanels();
	void InitDockingPositions();

public:
	void Init(GLFWwindow* _window, Level* _level);
	void StartLoop();
	void EndLoop();
	void Destroy();
	void RegisterWidget(const string& _widgetName, Widget* _widget);
	void DrawAll();
	void OpenPanel(const string& _widgetName);
	void ClosePanel(const string& _widgetName);
	void TogglePanel(const string& _widgetName);
	template<typename Type>
	Type* GetWidgetOfType()
	{
		for (const pair<string, Widget*>& _pair : allWidgets)
			if (Type* _widget = dynamic_cast<Type*>(_pair.second))
				return _widget;
		return nullptr;
	}
};