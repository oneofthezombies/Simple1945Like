#pragma once

#include "gameobjects/GameObject.h"

class Bomb : public GameObject
{
public:
    Bomb();
    virtual ~Bomb();

    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(const HDC hdc) override;

    void Explode();
};
