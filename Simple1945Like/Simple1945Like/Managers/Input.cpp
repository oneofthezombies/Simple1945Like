#include "stdafx.h"
#include "Input.h"

Input::Input()
{
    for (int i = 0; i < MAX_KEY; ++i)
    {
        keyUp.reset(i);
        keyDown.reset(i);
    }
}

bool Input::IsOnceKeyDown(int key)
{
    if (GetAsyncKeyState(key) & 0x8000)
    {
        if (!keyDown[key])
        {
            keyDown.set(key, true);
            return true;
        }
    }
    else
    {
        keyDown.reset(key);
    }

    return false;
}

bool Input::IsOnceKeyUp(int key)
{
    if (GetAsyncKeyState(key) & 0x8000)
    {
        keyUp.set(key, true);
    }
    else
    {
        if (keyUp[key])
        {
            keyUp.reset(key);
            return false;
        }
    }

    return false;
}

bool Input::IsStayKeyDown(int key)
{
    if (GetAsyncKeyState(key) & 0x8000)
    {
        return true;
    }

    return false;
}

bool Input::IsToggleKey(int key)
{
    if (GetKeyState(key) & 0x0001)
    {
        return true;
    }

    return false;
}
