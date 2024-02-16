#pragma once
#include "stdafx.h"
#include "core.h"
#include "sys.h"
#include "font.h"

// deprecated class
class Sprite {
private:
    GLuint m_backgroundSprite;
    GLuint m_tile;

public:

    GLuint getBackgroundSprite() { return m_backgroundSprite; }
    GLuint getTileSprite() { return m_tile; }

    void setBackgroundSprite(GLuint _backgroundSprite) { m_backgroundSprite = _backgroundSprite; }
    void setTileSprite(GLuint _tile) { m_tile = _tile; }
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