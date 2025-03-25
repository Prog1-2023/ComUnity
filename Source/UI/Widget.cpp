#include "Widget.h"

#include "UIManager.h"

Widget::Widget(const string& _widgetName, const bool& _openedByDefault)
{
	widgetName = _widgetName;
	isActive = _openedByDefault;
	Register();
}

void Widget::Register()
{
	UIManager::GetInstance().RegisterWidget(widgetName, this);
}
