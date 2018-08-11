#include "stdafx.h"
#include "Barrack.h"
#include "../../Constants/Constant.h"
#include "../../Utilities/Random.h"
#include "Pawn.h"
#include "Utilities/CommonMacroFunction.h"

using Const = ConstantTable;

Barrack::Barrack() :
    GameObject(),
    pawnGenCoolDown(0.0)
{
}

Barrack::~Barrack()
{
}

void Barrack::Init()
{
    GameObject::Init();
}

void Barrack::Update()
{
    GameObject::Update();

    pawnGenCoolDown -= deltaTime.count();
    if (pawnGenCoolDown < 0.0)
    {
        GeneratePawn();
    }
}

void Barrack::Render(const HDC hdc)
{
}

void Barrack::GeneratePawn()
{
    int pawnGenPosX = RANDOM->GetIntFromTo(rect.left, rect.right);

    auto pawn = new Pawn;
    pawn->SetTag(Tag::kPawn);
    pawn->SetRect(MakeRectCenter(pawnGenPosX, rect.top, Const::kPawnWidth, Const::kPawnHeight));
    pawn->SetVelocityY(Const::kPawnVelocityY);
    pawn->Init();
	if (registerGameObject) registerGameObject(pawn);

    pawnGenCoolDown = 0.7;
}
