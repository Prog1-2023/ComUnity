#include "FontManager.h"
#include <GL/glew.h>
#include "FileManager.h"

FontManager::FontManager()
{
    LoadFont(FileManager::GetInstance().GetContentPath() + "/Fonts/DefaultSans-Regular.ttf", 20.0f);
    defaultFont = fontList["DefaultSans-Regular.ttf"];
}

bool FontManager::LoadFont(const string& _fontPath, float _fontSize)
{
    string _fontKey = _fontPath.substr(_fontPath.find_last_of("/\\") + 1);

    ImGuiIO& _io = GetIO();

    if (fontList.find(_fontKey) != fontList.end())
    {
        LOG("Font already loaded, reloading texture: " + _fontKey + " (size: " + to_string(_fontSize) + ")");
        return LoadFontTexture();
    }

    ImFont* _font = _io.Fonts->AddFontFromFileTTF(_fontPath.c_str(), _fontSize);
    if (!_font)
    {
        LOG_ERROR("Error: Impossible to load font " + _fontPath);
        return false;
    }

    fontList.emplace(_fontKey, _font);
    LOG("Font loaded: " + _fontKey + " (size: " + to_string(_fontSize) + ")");
    return LoadFontTexture();
}

bool FontManager::LoadFontTexture()
{
    ImGuiIO& _io = GetIO();

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
    ImFont* _font = nullptr;

    if (!_fontName.empty()) {
        auto it = fontList.find(_fontName);
        if (it != fontList.end()) {
            _font = it->second;
        }
    }

    if (!_font) {
        _font = defaultFont;
        if (!_font) {
            LOG_ERROR("Error: No font available to render text");
            return;
        }
    }

    ImDrawList* _drawList = GetForegroundDrawList();
    _drawList->AddText(
        _font,
        _font->FontSize * _scale,
        ImVec2(_x, _y),
        ImColor(_color),
        _text.c_str()
    );
}
