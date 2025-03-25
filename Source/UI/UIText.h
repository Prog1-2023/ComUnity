#pragma once

#include "FontManager.h"
#include "../Utils/CoreMinimal.h"
#include "UIElement.h"

class UIText : public UIElement
{
    FontManager* fontManager;
    string text;
    string fontName;
    float x;
    float y;
    float scale;
    ImVec4 color;

public:
    UIText(FontManager* _fontManager, World* _world, const string& _name = "UIText");
    ~UIText();

    void SetText(const string& _text);
    void SetFont(const string& _fontName);
    void SetPosition(float _x, float _y);
    void SetScale(float _scale);
    void SetColor(const ImVec4& _color);

    void Draw(); 
};