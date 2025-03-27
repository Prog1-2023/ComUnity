#include "UIText.h"
#include "FileManager.h"

UIText::UIText() 
	: UIElement(),
	text(""), fontName(""), x(0), y(0), scale(1.0f), color(ImVec4(1, 1, 1, 1))
{
	Construct();
}

UIText::UIText(const string& _text)
	: UIElement(),
	text(_text), fontName(""), x(0), y(0), scale(1.0f), color(ImVec4(1, 1, 1, 1))
{
	Construct();
}

UIText::UIText(const string& _text, const string& _fontName)
	: UIElement(),
	text(_text), fontName(_fontName), x(0), y(0), scale(1.0f), color(ImVec4(1, 1, 1, 1))
{
	Construct();
}

UIText::UIText(const string& _text, const string& _fontName, float _x, float _y)
	: UIElement(),
	text(_text), fontName(_fontName), x(_x), y(_y), scale(1.0f), color(ImVec4(1, 1, 1, 1))
{
	Construct();
}

UIText::UIText(const string& _text, const string& _fontName, float _x, float _y, float _scale)
	: UIElement(),
	text(_text), fontName(_fontName), x(_x), y(_y), scale(_scale), color(ImVec4(1, 1, 1, 1))
{
	Construct();
}

UIText::UIText(const string& _text, const string& _fontName, float _x, float _y, float _scale, const ImVec4& _color)
	: UIElement(),
	text(_text), fontName(_fontName), x(_x), y(_y), scale(_scale), color(_color)
{
	Construct();
}

UIText::~UIText()
{
}

void UIText::SetText(const string& _text)
{
	text = _text;
}

void UIText::SetFont(const string& _fontName)
{
	fontName = _fontName;
}

void UIText::SetPosition(float _x, float _y)
{
	x = _x;
	y = _y;
}

void UIText::SetScale(float _scale)
{
	scale = _scale;
}

void UIText::SetColor(const ImVec4& _color)
{
	color = _color;
}

void UIText::Construct()
{

	if (fontName.empty())
	{
		FontManager::GetInstance().LoadFont(FileManager::GetInstance().GetContentPath() + "/Fonts/DefaultSans-Regular.ttf", 20.0f);
		fontName = "DefaultSans-Regular.ttf";
	}
}

void UIText::Draw()
{
	FontManager::GetInstance().RenderText(fontName, text, x, y, scale, color);
}
