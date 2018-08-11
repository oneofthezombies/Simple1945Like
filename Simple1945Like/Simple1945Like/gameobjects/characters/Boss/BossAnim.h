#pragma once

#include "gameobjects/characters/Enemy.h"

class BossAnim : public Enemy
{
public:
    BossAnim();
    virtual ~BossAnim();

    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(const HDC hdc) override;
    virtual void OnCollisionEnter(GameObject* other) override;

    virtual void Move() override;

    void CreateArms();

private:
    bool isBeganCreateArms;
};

class BossLeftAnim : public Enemy
{
public:
    BossLeftAnim();
    virtual ~BossLeftAnim();

    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(const HDC hdc) override;
    virtual void OnCollisionEnter(GameObject* other) override;

    virtual void Move() override;

    void CreateHand();

private:
    bool isBeganCreateHand;
};

class BossLeftHandAnim : public Enemy
{
public:
    BossLeftHandAnim();
    virtual ~BossLeftHandAnim();

    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(const HDC hdc) override;
    virtual void OnCollisionEnter(GameObject* other) override;

    virtual void Move() override;
};

class BossRightAnim : public Enemy
{
public:
    BossRightAnim();
    virtual ~BossRightAnim();

    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(const HDC hdc) override;
    virtual void OnCollisionEnter(GameObject* other) override;

    virtual void Move() override;

    void CreateHand();

private:
    bool isBeganCreateHand;
};

class BossRightHandAnim : public Enemy
{
public:
    BossRightHandAnim();
    virtual ~BossRightHandAnim();

    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(const HDC hdc) override;
    virtual void OnCollisionEnter(GameObject* other) override;

    virtual void Move() override;
};