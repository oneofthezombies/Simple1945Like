#include "stdafx.h"
#include "Pawn.h"
#include "Constants/Constant.h"

using Const = ConstantTable;

Pawn::Pawn() :
    Enemy(),
    angle(0.0)
{
}

Pawn::~Pawn()
{
}

void Pawn::Init()
{
    Enemy::Init();
}

void Pawn::Update()
{
    Enemy::Update();

    Patrol();
    Move();
}

void Pawn::Render(HDC hdc)
{
    HPEN myPen = CreatePen(PS_SOLID, 1, Const::kCyan);
    HPEN oldPen = (HPEN)SelectObject(hdc, myPen);
    HBRUSH myBrush = CreateSolidBrush(Const::kCyan);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
    Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(myPen);
    DeleteObject(myBrush);
}

void Pawn::OnCollisionEnter(GameObject* other)
{
    switch (other->GetTag())
    {
        case Tag::kPlayersBullet:
        {
            if (rect.top > 100)
            {
				if (destroyGameObject) destroyGameObject(GetId());
            }
        }
        break;
        default:
        {
        }
        break;
    }
}

void Pawn::Patrol()
{
    velocityX = Const::kPawnVelocityX * cos(angle);

    angle += M_PI / 36.0;
    if (angle >= M_PI * 2)
    {
        angle -= M_PI * 2;
    }
}
