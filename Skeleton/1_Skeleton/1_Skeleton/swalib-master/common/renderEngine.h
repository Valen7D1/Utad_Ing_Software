#pragma once
#include "stdafx.h"
#include "core.h"
#include "sys.h"
#include "font.h"

// deprecated class
class Sprite {
private:
    GLuint texbkg;
    GLuint texsmallball;
public:

    GLuint getTexbkg();
    GLuint getTexsmallball();

    void setTexbkg(GLuint Texbkg);
    void setTexsmallball(GLuint texsmallball);
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

    Sprite* GetSprite();

    //GLuint texbkg;
    //GLuint texsmallball;
};