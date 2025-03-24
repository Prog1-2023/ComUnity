#include "Widget.h"

#include "UIManager.h"

Widget::Widget(const string& _widgetName)
{
	widgetName = _widgetName;
	Register();
}

void Widget::Register()
{
	UIManager::GetInstance().RegisterWidget(widgetName, this);
}
