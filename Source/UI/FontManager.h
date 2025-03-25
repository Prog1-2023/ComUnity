#pragma once

#include "Singleton.h"
#include "../IMGUI/imgui.h"
#include "../Utils/CoreMinimal.h"

using namespace std;

class FontManager : public Singleton<FontManager>
{
    map<string, ImFont*> fontList; 

private:
        ImFont* defaultFont = nullptr;

public:
    FontManager();
    ~FontManager();

public:
    bool LoadFont(const string& _fontPath, float _fontSize);
    bool LoadFontTexture();
    void RenderText(const string& _fontName, const string& _text, float _x, float _y, float _scale, ImVec4 _color);
};
