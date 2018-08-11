#include "stdafx.h"
#include "Bomb.h"
#include "Constants/Constant.h"
#include "gameobjects/Projectiles/Bullet.h"
#include "Utilities/CommonMacroFunction.h"

using Const = ConstantTable;

Bomb::Bomb() :
    GameObject()
{
}

Bomb::~Bomb()
{
}

void Bomb::Init()
{
    GameObject::Init();

    lifeTime = 2;
}

void Bomb::Update()
{
    GameObject::Update();

    Move();

    lifeTime -= deltaTime.count();

    if (lifeTime < 0)
    {
        Explode();
		if (destroyGameObject) destroyGameObject(this->GetId());
    }
}

void Bomb::Render(const HDC hdc)
{
    HPEN myPen = CreatePen(PS_SOLID, 1, Const::kBlue);
    HPEN oldPen = (HPEN)SelectObject(hdc, myPen);
    HBRUSH myBrush = CreateSolidBrush(Const::kBlue);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
    Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(myPen);
    DeleteObject(myBrush);
}

void Bomb::Explode()
{
    for (double i = 0.0; i < M_PI * 2.0; i += M_PI / 7.0)
    {
        auto bullet = new Bullet;
        bullet->SetTag(Tag::kEnemyBullet);
        bullet->SetRect(MakeRectCenter(0, 0, Const::kBulletWidth, Const::kBulletHeight));
        bullet->SetPosition((rect.left + rect.right) / 2.0, (rect.top + rect.bottom) / 2.0);
        bullet->SetVelocityX(5.0 * cos(i));
        bullet->SetVelocityY(5.0 * sin(i));
        bullet->Init();
		if (registerGameObject) registerGameObject(bullet);
    }
}
