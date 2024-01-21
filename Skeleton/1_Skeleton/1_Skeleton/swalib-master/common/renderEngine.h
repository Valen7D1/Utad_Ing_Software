#pragma once
#include "stdafx.h"
#include "core.h"
#include "sys.h"
#include "font.h"

class RenderEngine {
private:
    static RenderEngine* instance;

public:
    static RenderEngine* getInstance();

    void TexturesSetting();
    void RenderSetUp();
    void RenderObjects();
    void RenderText();

    GLuint texbkg;
    GLuint texsmallball;
};


//class Sprite {
//private:
//    GLuint texbkg;
//    GLuint texsmallball;
//public:
//
//    GLuint getTexbkg();
//    GLuint getTexsmallball();
//
//    void setTexbkg(GLuint Texbkg);
//    void setTexsmallball(GLuint texsmallball);
//};
