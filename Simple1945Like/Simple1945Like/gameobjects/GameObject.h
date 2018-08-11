#pragma once

#include "../Tags/Tag.h"

class MainScene;

class GameObject
{
public:
    GameObject();
    virtual ~GameObject();

    virtual void Init();
    virtual void Update();
    virtual void Render(const HDC hdc);
    virtual void OnCollisionEnter(GameObject* other);

    virtual void SetRegisterGameObjectCallback(function<void(GameObject*)> method) final;
    virtual void SetDestroyGameObjectCallback(function<void(int)> method) final;
    virtual void SetFindGameObjectsCallback(function<vector<GameObject*>(Tag)> method) final;

    virtual void DoNothing() final;
    virtual void Action() final;

    virtual void Move();
    virtual void MoveX(const double velocity) final;
    virtual void MoveY(const double velocity) final;

    virtual void SetPosition(const int x, const int y) final;
    
    virtual void SetRect(const RECT rect) final;
    virtual RECT GetRect() const final;

    virtual void SetVelocityX(const double velocity) final;
    virtual void SetVelocityY(const double velocity) final;
    virtual double GetVelocityX() final;
    virtual double GetVelocityY() final;

    virtual void IncDecHp(const int value) final;
    virtual void IncDecLifeTime(const int value) final;

    virtual void SetTag(const Tag tag) final;
    virtual Tag GetTag() const final;

    virtual void SetId(const int id) final;
    virtual int GetId() const final;

    virtual void SetParent(GameObject* parent) final;
    virtual void SetChild(GameObject* child) final;

    virtual int GetHp() const final;

protected:
    function<void(GameObject*)> registerGameObject;
    function<void(int)> destroyGameObject;
    function<vector<GameObject*>(Tag)> findGameObjects;

    GameObject* parent;
    vector<GameObject*> children;

    Tag tag;
    function<void()> action;
    RECT rect;
    int hp;
    double lifeTime;
    double velocityX;
    double velocityY;
    int id;

    chrono::time_point<chrono::system_clock> previousTime;
    chrono::duration<double> deltaTime;

    HBITMAP image;
};

