#pragma once

#include "../GameObject.h"

class Barrack : public GameObject
{
public:
    Barrack();
    virtual ~Barrack();

    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(const HDC hdc) override;

    void GeneratePawn();

private:
    double pawnGenCoolDown;
};

