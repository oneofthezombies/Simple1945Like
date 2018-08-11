#include "stdafx.h"
#include "Bullet.h"
#include "Constants/Constant.h"

using Const = ConstantTable;

Bullet::Bullet() :
    GameObject()
{
}

Bullet::~Bullet()
{
}

void Bullet::Init()
{
    GameObject::Init();
}

void Bullet::Update()
{
    Move();
}

void Bullet::Render(const HDC hdc)
{
    if (tag == Tag::kPlayersBullet)
    {
        HPEN myPen = CreatePen(PS_SOLID, 1, Const::kMagenta);
        HPEN oldPen = (HPEN)SelectObject(hdc, myPen);
        HBRUSH myBrush = CreateSolidBrush(Const::kMagenta);
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
        Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
        SelectObject(hdc, oldPen);
        SelectObject(hdc, oldBrush);
        DeleteObject(myPen);
        DeleteObject(myBrush);
    }
    else if (tag == Tag::kEnemyBullet)
    {
        HPEN myPen = CreatePen(PS_SOLID, 1, Const::kYellow);
        HPEN oldPen = (HPEN)SelectObject(hdc, myPen);
        HBRUSH myBrush = CreateSolidBrush(Const::kYellow);
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
        Ellipse(hdc, rect.left - 1, rect.top - 1, rect.right + 1, rect.bottom + 1);
        SelectObject(hdc, oldPen);
        SelectObject(hdc, oldBrush);
        DeleteObject(myPen);
        DeleteObject(myBrush);
    }
}
