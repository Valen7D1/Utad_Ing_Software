#pragma once

class BaseLevel {
public:
    BaseLevel(){}
    void CreatePlayer();
    virtual void CreateLevel() = 0;
};

class Level1 : public BaseLevel {

public:
    virtual void CreateLevel() override;
};

class Level2 : public BaseLevel {

public:
    virtual void CreateLevel() override;
};