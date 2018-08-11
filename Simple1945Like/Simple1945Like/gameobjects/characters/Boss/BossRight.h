#pragma once

#include "gameobjects/characters/Enemy.h"

class BossRight : public Enemy
{
public:
    BossRight();
    virtual ~BossRight();

    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(const HDC hdc) override;
    virtual void OnCollisionEnter(GameObject* other) override;
};

class BossRightHand : public Enemy
{
public:
    BossRightHand();
    virtual ~BossRightHand();

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
