#pragma once

#include "gameobjects/GameObject.h"

class Player : public GameObject
{
public:
    Player();
    virtual ~Player();

    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(const HDC hdc) override;
    virtual void OnCollisionEnter(GameObject* other) override;

    void FireBullet();
    void FireLaser();
    void FireHomingMissile();
    void SelfExplosion();

    void Barrier();

    int GetMana();

private:
    double fireBulletCoolDown;
    int mana;
    bool onBarrier;
    RECT barrier;
};

