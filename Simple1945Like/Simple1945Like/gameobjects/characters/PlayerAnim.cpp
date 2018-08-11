#include "stdafx.h"
#include "PlayerAnim.h"
#include "Constants/Constant.h"
#include "Utilities/CommonMacroFunction.h"

using Const = ConstantTable;

PlayerAnim::PlayerAnim()
{
}

PlayerAnim::~PlayerAnim()
{
}

void PlayerAnim::Init()
{
    GameObject::Init();
}

void PlayerAnim::Update()
{
    GameObject::Update();

    Move();
}

void PlayerAnim::Render(const HDC hdc)
{
    HPEN myPen = CreatePen(PS_SOLID, 1, Const::kRed);
    HPEN oldPen = (HPEN)SelectObject(hdc, myPen);
    HBRUSH myBrush = CreateSolidBrush(Const::kRed);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
    Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(myPen);
    DeleteObject(myBrush);
}

void PlayerAnim::Move()
{
    rect.top += static_cast<LONG>(velocityY);
    rect.bottom += static_cast<LONG>(velocityY);

    if ((rect.top + rect.bottom) / 2 <= Const::kPlayerStartPosY)
    {
        rect = MakeRectCenter(Const::kPlayerStartPosX, Const::kPlayerStartPosY,
                              Const::kPlayerWidth, Const::kPlayerHeight);
    }
}
