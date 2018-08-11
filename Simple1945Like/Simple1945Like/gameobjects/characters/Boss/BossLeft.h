#pragma once

#include "gameobjects/characters/Enemy.h"

class BossLeft : public Enemy
{
public:
    BossLeft();
    virtual ~BossLeft();

    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(const HDC hdc) override;
    virtual void OnCollisionEnter(GameObject* other) override;
};

class BossLeftHand : public Enemy
{
public:
    BossLeftHand();
    virtual ~BossLeftHand();

    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(const HDC hdc) override;
    virtual void OnCollisionEnter(GameObject* other) override;

    void Punch();
    void Return();
    void FirePizza();

private:
    double distance;
    double punchCoolDown;
    double returnCoolDown;
    bool isPunched;
    bool isReturning;
    double targetX;
    double targetY;
    double pizzaSpeed;
};
