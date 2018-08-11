#pragma once

#include "gameobjects/GameObject.h"

class Bullet : public GameObject
{
public:
    Bullet();
    virtual ~Bullet();

    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(const HDC hdc) override;
};
