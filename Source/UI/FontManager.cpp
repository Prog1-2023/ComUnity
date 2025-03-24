#include "FontManager.h"
#include <iostream>

FontManager::FontManager()
{
}

FontManager::~FontManager()
{
    for (auto& [key, font] : fontList)
    {
        if (ImGui::GetIO().Fonts->TexID) {
            GLuint texID = (GLuint)(intptr_t)ImGui::GetIO().Fonts->TexID;
            glDeleteTextures(1, &texID);
        }
    }
    fontList.clear();
}

bool FontManager::LoadFont(const string& _fontPath, float _fontSize)
{
    string _fontKey = _fontPath + to_string(_fontSize);
    ImGuiIO& _io = ImGui::GetIO();

    if (fontList.find(_fontKey) != fontList.end()) 
    {
        cout << "Font already loaded, reloading texture: " << _fontPath << " (size: " << _fontSize << ")" << endl;
        return LoadFontTexture();
    }

    ImFont* _font = _io.Fonts->AddFontFromFileTTF(_fontPath.c_str(), _fontSize);
    if (!_font) 
    {
        cerr << "Error: Impossible to load font " << _fontPath << endl;
        return false;
    }

    fontList.emplace(_fontKey, _font);

    cout << "Font loaded: " << _fontPath << " (size: " << _fontSize << ")" << endl;
    return LoadFontTexture();
}

bool FontManager::LoadFontTexture()
{
    ImGuiIO& _io = ImGui::GetIO();

    unsigned char* _pixels;
    int _width, _height;
    _io.Fonts->GetTexDataAsRGBA32(&_pixels, &_width, &_height);

    if (_io.Fonts->TexID) 
    {
        GLuint _oldTexture = (GLuint)(intptr_t)_io.Fonts->TexID;
        glDeleteTextures(1, &_oldTexture);
    }

    GLuint _fontTexture;
    glGenTextures(1, &_fontTexture);
    glBindTexture(GL_TEXTURE_2D, _fontTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    _io.Fonts->TexID = (ImTextureID)(intptr_t)_fontTexture;

    return true;
}

void FontManager::RenderText(const string& _fontName, const string& _text, float _x, float _y, float _scale, ImVec4 _color)
{
    map<string, ImFont*>::iterator it = fontList.find(_fontName);
    if (it == fontList.end()) 
    {
        cerr << "Error: Font not found - " << _fontName << endl;
        return;
    }

    ImFont* _font = it->second;

    ImDrawList* _drawList = ImGui::GetForegroundDrawList();
    _drawList->AddText(
        _font,
        _font->FontSize * _scale,
        ImVec2(_x, _y),
        ImColor(_color),
        _text.c_str()
    );
}
