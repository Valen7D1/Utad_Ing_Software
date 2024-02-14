#pragma once
#include "stdafx.h"
#include "core.h"
#include "sys.h"
#include "font.h"

// deprecated class
class Sprite {
private:
    GLuint m_backgroundSprite;
public:

    GLuint getBackgroundSprite() { return m_backgroundSprite; }

    void setBackgroundSprite(GLuint _backgroundSprite) { m_backgroundSprite = _backgroundSprite; }
};

class RenderEngine {
private:
    static RenderEngine* instance;
    Sprite sprite;

public:
    static RenderEngine* getInstance();

    void TexturesSetting();
    void RenderSetUp();
    void RenderObjects();
    void RenderText();

    Sprite* GetSprite() { return &sprite; }
};