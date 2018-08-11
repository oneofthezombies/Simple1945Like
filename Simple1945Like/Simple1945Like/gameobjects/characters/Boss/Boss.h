#pragma once

#include "gameobjects/characters/Enemy.h"

class Boss : public Enemy
{
public:
    Boss();
    ~Boss();

    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(const HDC hdc) override;
    virtual void OnCollisionEnter(GameObject* other) override;

    void FirePizza();
    void FireLaser();
    void FireBomb();

private:
    double pizzaSpeed;
    double pizzaCoolDown;
    
    double laserSpeed;
    double laserCoolDown;

    double bombCoolDown;

    double moveCoolDown;
};

