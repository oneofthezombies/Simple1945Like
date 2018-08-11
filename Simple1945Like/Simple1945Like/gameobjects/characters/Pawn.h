#pragma once

#include "Enemy.h"

class Pawn : public Enemy
{
public:
    Pawn();
    virtual ~Pawn();

    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(const HDC hdc) override;
    virtual void OnCollisionEnter(GameObject* other) override;

    void Patrol();

private:
    double angle;
};

