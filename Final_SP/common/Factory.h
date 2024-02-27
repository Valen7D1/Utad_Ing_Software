#pragma once
#include "../swalib_example/rapidjson/document.h"
#include "../swalib_example/rapidjson/filereadstream.h"

class BaseLevel {

public:
    BaseLevel(const char* entitiesFile)
    {
        char readBuffer[1024];
        FILE* fp;
        fopen_s(&fp, entitiesFile, "rb");
        rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
        doc.ParseStream(is);
    }

    void CreatePlayer();
    virtual void CreateLevel() = 0;
    virtual BaseLevel* NextLevel() = 0;

public:
    rapidjson::Document doc;
    ~BaseLevel()
    {
    }
};


class LevelCreator : public BaseLevel {

public:
    LevelCreator(const char* file) : BaseLevel(file) {}
    virtual void CreateLevel() override;
    virtual BaseLevel* NextLevel() = 0;
};

class Level1 : public LevelCreator {

public:
    Level1() : LevelCreator("data/Level1.json") {}
    virtual BaseLevel* NextLevel() override;
};

class Level2 : public LevelCreator {

public:
    Level2() : LevelCreator("data/Level2.json") {}
    virtual BaseLevel* NextLevel() override;
};

class Level3 : public LevelCreator {

public:
    Level3() : LevelCreator("data/Level3.json") {}
    virtual BaseLevel* NextLevel() override;
};

class DeathMenu : public BaseLevel {

public:
    DeathMenu() : BaseLevel("data/scene.json") {}
    virtual void CreateLevel() override;
    virtual BaseLevel* NextLevel() override;
};

class WinMenu : public BaseLevel {

public:
    WinMenu() : BaseLevel("data/scene.json") {}
    virtual void CreateLevel() override;
    virtual BaseLevel* NextLevel() override;
};

class MainMenu : public BaseLevel {

public:
    MainMenu() : BaseLevel("data/scene.json") {}
    virtual void CreateLevel() override;
    virtual BaseLevel* NextLevel() override;
};