#pragma once

class BaseLevel {
public:
    BaseLevel(){}
    void CreatePlayer();
    virtual void CreateLevel() = 0;
    virtual BaseLevel* NextLevel() = 0;
};

class MainMenu : public BaseLevel {

public:
    virtual void CreateLevel() override;
    virtual BaseLevel* NextLevel() override;
};

class Level1 : public BaseLevel {

public:
    virtual void CreateLevel() override;
    virtual BaseLevel* NextLevel() override;
};

class Level2 : public BaseLevel {

public:
    virtual void CreateLevel() override;
    virtual BaseLevel* NextLevel() override;
};

class DeathMenu : public BaseLevel {

public:
    virtual void CreateLevel() override;
    virtual BaseLevel* NextLevel() override;
};

class WinMenu : public BaseLevel {

public:
    virtual void CreateLevel() override;
    virtual BaseLevel* NextLevel() override;
};