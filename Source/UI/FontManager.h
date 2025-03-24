#pragma once

#include "Singleton.h"
#include <string>
#include "../IMGUI/imgui.h"

class FontManager : public Singleton<FontManager>
{
    map<string, ImFont*> fontList;

public:
    bool LoadFont(const string& _fontPath, float _fontSize);
    bool LoadFontTexture();
    void RenderText(const string& _fontName, const string& _text, float _x, float _y, float _scale, ImVec4 _color);

public:
    FontManager();
    ~FontManager();
};
