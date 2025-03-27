#pragma once

#include "FontManager.h"
#include "../Utils/CoreMinimal.h"
#include "UIElement.h"

class World;

class UIText : public UIElement
{
    string text;
    string fontName;
    float x;
    float y;
    float scale;
    ImVec4 color;

public:
    UIText(); 
    UIText(const string& _text);
    UIText(const string& _text, const string& _fontName);
    UIText(const string& _text, const string& _fontName, float _x, float _y);
    UIText(const string& _text, const string& _fontName, float _x, float _y, float _scale);
    UIText(const string& _text, const string& _fontName, float _x, float _y, float _scale, const ImVec4& _color);
    ~UIText();

    void SetText(const string& _text);
    void SetFont(const string& _fontName);
    void SetPosition(float _x, float _y);
    void SetScale(float _scale);
    void SetColor(const ImVec4& _color);
    void Construct();

    virtual void Draw() override; 
};