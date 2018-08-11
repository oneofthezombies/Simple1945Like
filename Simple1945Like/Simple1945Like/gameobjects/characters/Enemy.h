#pragma once

#include"gameobjects/GameObject.h"

class Enemy : public GameObject
{
public:
    Enemy();
    virtual ~Enemy();

    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(const HDC hdc) override;
    virtual void OnCollisionEnter(GameObject* other) override;

    virtual void FireBullet() final;

protected:
    double fireBulletCoolDown;
};

