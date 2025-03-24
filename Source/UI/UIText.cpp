#include "UIText.h"
#include <iostream>

UIText::UIText(FontManager* fontManager)
    : fontManager(fontManager),
    text(""),
    fontName(""),
    x(0.0f),
    y(0.0f),
    scale(1.0f),
    color(ImVec4(1.0f, 1.0f, 1.0f, 1.0f))
{
}

UIText::~UIText()
{
}

void UIText::SetText(const std::string& _text)
{
    text = _text;
}

void UIText::SetFont(const std::string& _fontName)
{
    if (fontManager->LoadFont(_fontName, 24.0f)) {
        fontName = _fontName;
    }
    else {
        cerr << "Failed to load font: " << _fontName << endl;
    }
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

void UIText::Render()
{
    if (fontName.empty() || text.empty()) {
        cerr << "Error: Missing font or text!" << endl;
        return;
    }

    fontManager->RenderText(fontName, text, x, y, scale, color);
}
