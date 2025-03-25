#include "UIText.h"

UIText::UIText(FontManager* _fontManager, World* _world, const string& _name)
    : UIElement(_world, _name),
    fontManager(_fontManager), text(""), fontName(""), x(0), y(0), scale(1.0f), color(ImVec4(1, 1, 1, 1))
{
    if (fontName.empty()) 
    {
        fontManager->LoadFont(GetAbsolutePath() + "/Content/Fonts/DefaultSans-Regular.ttf", 20.0f);
        fontName = "DefaultSans-Regular.ttf"; 
    }
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

void UIText::Draw()
{
    if (fontManager)
    {
        fontManager->RenderText(fontName, text, x, y, scale, color);
    }
}
