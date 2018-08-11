#pragma once

#include "gameobjects/GameObject.h"

class PlayerAnim : public GameObject
{
public:
    PlayerAnim();
    virtual ~PlayerAnim();

    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(const HDC hdc) override;

    virtual void Move() override;
};

