#include "stdafx.h"
#include "BossLeft.h"
#include "Constants/Constant.h"
#include "Utilities/CommonMacroFunction.h"
#include "gameobjects/Projectiles/Bullet.h"

using Const = ConstantTable;

BossLeft::BossLeft() :
    Enemy()
{
}

BossLeft::~BossLeft()
{
}

void BossLeft::Init()
{
    Enemy::Init();

    auto leftHand = new BossLeftHand;
    leftHand->SetTag(Tag::kBossLeftHand);
    leftHand->SetRect(MakeRectCenter(Const::kBossLeftHandStartPosX, Const::kBossLeftHandStartPosY,
                                      Const::kBossLeftHandWidth, Const::kBossLeftHandHeight));
	if (registerGameObject) registerGameObject(leftHand);
    leftHand->Init();
}

void BossLeft::Update()
{
    GameObject::Update();
}

void BossLeft::Render(const HDC hdc)
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

void BossLeft::OnCollisionEnter(GameObject* other)
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

BossLeftHand::BossLeftHand() :
    Enemy(),
    distance(500.0),
    punchCoolDown(3.0),
    isPunched(false),
    targetX(0.0),
    targetY(0.0),
    isReturning(false),
    returnCoolDown(0.0),
    pizzaSpeed(3.0)
{
}

BossLeftHand::~BossLeftHand()
{
}

void BossLeftHand::Init()
{
    Enemy::Init();

    hp = 30;
}

void BossLeftHand::Update()
{
    GameObject::Update();

    punchCoolDown -= deltaTime.count();
    returnCoolDown -= deltaTime.count();

	if (findGameObjects)
	{
		auto players = findGameObjects(Tag::kPlayer);
		if (!players.empty())
		{
			auto playersRect = players.front()->GetRect();
			if (playersRect.left > rect.right)
			{
				if (punchCoolDown < 0.0 && !isPunched)
				{
					Punch();
				}
			}
		}
	}

    if (isPunched && returnCoolDown < 0.0)
    {
        Return();
    }

    if (isReturning && GetDistance((rect.left + rect.right) / 2, (rect.top + rect.bottom) / 2, 
                                   Const::kBossLeftHandStartPosX, Const::kBossLeftHandStartPosY) < 50.0)
    {
        rect = MakeRectCenter(Const::kBossLeftHandStartPosX, Const::kBossLeftHandStartPosY,
                              Const::kBossLeftHandWidth, Const::kBossLeftHandHeight);
        velocityX = 0;
        velocityY = 0;
        isPunched = false;
        isReturning = false;
        punchCoolDown = 3.0;
    }

    Move();
}

void BossLeftHand::Render(const HDC hdc)
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

void BossLeftHand::OnCollisionEnter(GameObject* other)
{
    switch (other->GetTag())
    {
        case Tag::kPlayersBullet:
        {
				if (destroyGameObject) destroyGameObject(other->GetId());

            hp--;
            if (hp < 0)
            {
                FirePizza();
				if (destroyGameObject) destroyGameObject(GetId());

				if (findGameObjects)
				{
					auto lefts = findGameObjects(Tag::kBossLeft);
					if (!lefts.empty())
					{
						for (auto & left : lefts)
						{
							if (destroyGameObject) destroyGameObject(left->GetId());
						}
					}
				}
            }
        }
        break;
        default:
        {
        }
        break;
    }
}

void BossLeftHand::Punch()
{
	if (findGameObjects)
	{
		auto players = findGameObjects(Tag::kPlayer);
		if (!players.empty())
		{
			auto playersRect = players.front()->GetRect();
			auto angle = GetAngle(rect.left, rect.top, playersRect.left, playersRect.top);
			velocityX = 10.0 * cos(angle);
			velocityY = 10.0 * -sin(angle);
			targetX = distance * cos(angle);
			targetY = distance * -sin(angle);

			isPunched = true;
			returnCoolDown = 1.0;
		}
	}
}

void BossLeftHand::Return()
{
    auto angle = GetAngle((rect.left + rect.right) / 2, (rect.top + rect.bottom) / 2, 
                          Const::kBossLeftHandStartPosX, Const::kBossLeftHandStartPosY);
    velocityX = 5.0 * cos(angle);
    velocityY = 5.0 * -sin(angle);
    targetX = Const::kBossLeftHandStartPosX;
    targetY = Const::kBossLeftHandStartPosY;

    isReturning = true;
}

void BossLeftHand::FirePizza()
{
    double i = M_PI + M_PI / 3;
    for (; i < M_PI * 2; i += M_PI / 24.0)
    {
        auto bullet = new Bullet;
        bullet->SetTag(Tag::kEnemyBullet);
        bullet->SetRect(MakeRectCenter((rect.left + rect.right) / 2, (rect.top + rect.bottom) / 2,
                                       Const::kBulletWidth, Const::kBulletHeight));
        bullet->SetVelocityX((pizzaSpeed + i * 5) * cos(i));
        bullet->SetVelocityY((pizzaSpeed + i * 3) * -sin(i));
        bullet->Init();
		if (registerGameObject) registerGameObject(bullet);
    }
}
