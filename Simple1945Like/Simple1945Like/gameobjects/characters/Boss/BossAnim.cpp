#include "stdafx.h"
#include "BossAnim.h"
#include "Constants/Constant.h"
#include "Utilities/CommonMacroFunction.h"

using Const = ConstantTable;

BossAnim::BossAnim() :
    Enemy(),
    isBeganCreateArms(false)
{
}

BossAnim::~BossAnim()
{
}

void BossAnim::Init()
{
    GameObject::Init();
}

void BossAnim::Update()
{
    GameObject::Update();

    Move();
}

void BossAnim::Render(const HDC hdc)
{
    HPEN myPen = CreatePen(PS_SOLID, 1, Const::kGreen);
    HPEN oldPen = (HPEN)SelectObject(hdc, myPen);
    HBRUSH myBrush = CreateSolidBrush(Const::kGreen);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
    Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(myPen);
    DeleteObject(myBrush);
}

void BossAnim::Move()
{
    rect.top += static_cast<LONG>(velocityY);
    rect.bottom += static_cast<LONG>(velocityY);

    if ((rect.top + rect.bottom) / 2 >= Const::kBossStartPosY)
    {
        rect = MakeRectCenter(Const::kBossStartPosX, Const::kBossStartPosY,
                              Const::kBossWidth, Const::kBossHeight);

        if (!isBeganCreateArms)
        {
            CreateArms();
            isBeganCreateArms = true;
        }
    }
}

void BossAnim::CreateArms()
{
    auto bossLeftAnim = new BossLeftAnim;
    bossLeftAnim->SetTag(Tag::kIdle);
    bossLeftAnim->SetRect(MakeRectCenter(Const::kBossStartPosX, Const::kBossLeftStartPosY,
                                         Const::kBossLeftWidth, Const::kBossLeftHeight));
    bossLeftAnim->SetVelocityX(-5.0);
    bossLeftAnim->Init();
	if (registerGameObject) registerGameObject(bossLeftAnim);

    auto bossRightAnim = new BossRightAnim;
    bossRightAnim->SetTag(Tag::kIdle);
    bossRightAnim->SetRect(MakeRectCenter(Const::kBossStartPosX, Const::kBossRightStartPosY,
                                          Const::kBossRightWidth, Const::kBossRightHeight));
    bossRightAnim->SetVelocityX(5.0);
    bossRightAnim->Init();
	if (registerGameObject) registerGameObject(bossRightAnim);
}

void BossAnim::OnCollisionEnter(GameObject* other)
{
    switch (other->GetTag())
    {
        case Tag::kPlayersBullet:
        {
				if (destroyGameObject) destroyGameObject(other->GetId());
        }
        break;
        default:
        {
        }
        break;
    }
}

BossLeftAnim::BossLeftAnim() :
    Enemy(),
    isBeganCreateHand(false)
{
}

BossLeftAnim::~BossLeftAnim()
{
}

void BossLeftAnim::Init()
{
    GameObject::Init();
}

void BossLeftAnim::Update()
{
    GameObject::Update();

    Move();
}

void BossLeftAnim::Render(const HDC hdc)
{
    HPEN myPen = CreatePen(PS_SOLID, 1, Const::kGreen);
    HPEN oldPen = (HPEN)SelectObject(hdc, myPen);
    HBRUSH myBrush = CreateSolidBrush(Const::kGreen);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
    Ellipse(hdc, rect.left - Const::kBossLeftOffset, 
            rect.top - Const::kBossLeftOffset, 
            rect.right + Const::kBossLeftOffset, 
            rect.bottom + Const::kBossLeftOffset);
    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(myPen);
    DeleteObject(myBrush);
}

void BossLeftAnim::Move()
{
    rect.left += static_cast<LONG>(velocityX);
    rect.right += static_cast<LONG>(velocityX);

    if ((rect.left + rect.right) / 2 <= Const::kBossLeftStartPosX)
    {
        rect = MakeRectCenter(Const::kBossLeftStartPosX, Const::kBossLeftStartPosY,
                              Const::kBossLeftWidth, Const::kBossLeftHeight);

        if (!isBeganCreateHand)
        {
            CreateHand();
            isBeganCreateHand = true;
        }
    }
}

void BossLeftAnim::CreateHand()
{
    auto leftHand = new BossLeftHandAnim;
    leftHand->SetTag(Tag::kIdle);
    leftHand->SetRect(MakeRectCenter(Const::kBossLeftHandStartPosX, Const::kBossLeftStartPosY,
                                     Const::kBossLeftHandWidth, Const::kBossLeftHandHeight));
    leftHand->SetVelocityY(2.0);
    leftHand->Init();
	if (registerGameObject) registerGameObject(leftHand);
}

void BossLeftAnim::OnCollisionEnter(GameObject* other)
{
    switch (other->GetTag())
    {
        case Tag::kPlayersBullet:
        {
				if (destroyGameObject) destroyGameObject(other->GetId());
        }
        break;
        default:
        {
        }
        break;
    }
}

BossRightAnim::BossRightAnim() :
    Enemy(),
    isBeganCreateHand(false)
{
}

BossRightAnim::~BossRightAnim()
{
}

void BossRightAnim::Init()
{
    GameObject::Init();
}

void BossRightAnim::Update()
{
    GameObject::Update();

    Move();
}

void BossRightAnim::Render(const HDC hdc)
{
    HPEN myPen = CreatePen(PS_SOLID, 1, Const::kGreen);
    HPEN oldPen = (HPEN)SelectObject(hdc, myPen);
    HBRUSH myBrush = CreateSolidBrush(Const::kGreen);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
    Ellipse(hdc, rect.left - Const::kBossRightOffset, 
            rect.top - Const::kBossRightOffset, 
            rect.right + Const::kBossRightOffset, 
            rect.bottom + Const::kBossRightOffset);
    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(myPen);
    DeleteObject(myBrush);
}

void BossRightAnim::Move()
{
    rect.left += static_cast<LONG>(velocityX);
    rect.right += static_cast<LONG>(velocityX);

    if ((rect.left + rect.right) / 2 >= Const::kBossRightStartPosX)
    {
        rect = MakeRectCenter(Const::kBossRightStartPosX, Const::kBossRightStartPosY,
                              Const::kBossRightWidth, Const::kBossRightHeight);

        if (!isBeganCreateHand)
        {
            CreateHand();
            isBeganCreateHand = true;
        }
    }
}

void BossRightAnim::CreateHand()
{
    auto rightHand = new BossRightHandAnim;
    rightHand->SetTag(Tag::kIdle);
    rightHand->SetRect(MakeRectCenter(Const::kBossRightHandStartPosX, Const::kBossRightStartPosY,
                                     Const::kBossRightHandWidth, Const::kBossRightHandHeight));
    rightHand->SetVelocityY(2.0);
    rightHand->Init();
	if (registerGameObject) registerGameObject(rightHand);
}

void BossRightAnim::OnCollisionEnter(GameObject* other)
{
    switch (other->GetTag())
    {
        case Tag::kPlayersBullet:
        {
				if (destroyGameObject) destroyGameObject(other->GetId());
        }
        break;
        default:
        {
        }
        break;
    }
}

BossLeftHandAnim::BossLeftHandAnim() :
    Enemy()
{
}

BossLeftHandAnim::~BossLeftHandAnim()
{
}

void BossLeftHandAnim::Init()
{
    Enemy::Init();
}

void BossLeftHandAnim::Update()
{
    GameObject::Update();

    Move();
}

void BossLeftHandAnim::Render(const HDC hdc)
{
    HPEN myPen = CreatePen(PS_SOLID, 1, Const::kWhite);
    HPEN oldPen = (HPEN)SelectObject(hdc, myPen);
    HBRUSH myBrush = CreateSolidBrush(Const::kWhite);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
    Ellipse(hdc, rect.left - Const::kBossLeftHandOffset, 
            rect.top - Const::kBossLeftHandOffset, 
            rect.right + Const::kBossLeftHandOffset, 
            rect.bottom + Const::kBossLeftHandOffset);
    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(myPen);
    DeleteObject(myBrush);
}

void BossLeftHandAnim::Move()
{
    rect.top += static_cast<LONG>(velocityY);
    rect.bottom += static_cast<LONG>(velocityY);

    if ((rect.top + rect.bottom) / 2 >= Const::kBossLeftHandStartPosY)
    {
        rect = MakeRectCenter(Const::kBossLeftHandStartPosX, Const::kBossLeftHandStartPosY,
                              Const::kBossLeftHandWidth, Const::kBossLeftHandHeight);
    }
}

void BossLeftHandAnim::OnCollisionEnter(GameObject* other)
{
    switch (other->GetTag())
    {
        case Tag::kPlayersBullet:
        {
				if (destroyGameObject) destroyGameObject(other->GetId());
        }
        break;
        default:
        {
        }
        break;
    }
}

BossRightHandAnim::BossRightHandAnim() :
    Enemy()
{
}

BossRightHandAnim::~BossRightHandAnim()
{
}

void BossRightHandAnim::Init()
{
    GameObject::Init();
}

void BossRightHandAnim::Update()
{
    GameObject::Update();

    Move();
}

void BossRightHandAnim::Render(const HDC hdc)
{
    HPEN myPen = CreatePen(PS_SOLID, 1, Const::kWhite);
    HPEN oldPen = (HPEN)SelectObject(hdc, myPen);
    HBRUSH myBrush = CreateSolidBrush(Const::kWhite);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
    Ellipse(hdc, rect.left - Const::kBossRightHandOffset, 
            rect.top - Const::kBossRightHandOffset, 
            rect.right + Const::kBossRightHandOffset, 
            rect.bottom + Const::kBossRightHandOffset);
    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(myPen);
    DeleteObject(myBrush);
}

void BossRightHandAnim::Move()
{
    rect.top += static_cast<LONG>(velocityY);
    rect.bottom += static_cast<LONG>(velocityY);

    if ((rect.top + rect.bottom) / 2 >= Const::kBossRightHandStartPosY)
    {
        rect = MakeRectCenter(Const::kBossRightHandStartPosX, Const::kBossRightHandStartPosY,
                              Const::kBossRightHandWidth, Const::kBossRightHandHeight);
    }
}


void BossRightHandAnim::OnCollisionEnter(GameObject* other)
{
    switch (other->GetTag())
    {
        case Tag::kPlayersBullet:
        {
				if (destroyGameObject) destroyGameObject(other->GetId());
        }
        break;
        default:
        {
        }
        break;
    }
}
