#pragma once

#include "Utilities/SingletonBase.h"

#define MAX_KEY 256
#define INPUT Input::GetInstance()

enum VK
{
    Q = 0x51,
    W = 0x57,
    E = 0x45,
    R = 0x52
};

class Input : public SingletonBase<Input>
{
public:
    Input();
    virtual ~Input() {}

    bool IsOnceKeyDown(int key);
    bool IsOnceKeyUp(int key);
    bool IsStayKeyDown(int key);
    bool IsToggleKey(int key);

protected:
    bitset<MAX_KEY> keyUp;
    bitset<MAX_KEY> keyDown;
};

