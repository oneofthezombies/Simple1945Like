#include "stdafx.h"
#include "BossRight.h"
#include "Constants/Constant.h"
#include "Utilities/CommonMacroFunction.h"
#include "gameobjects/Projectiles/Bullet.h"

using Const = ConstantTable;

BossRight::BossRight() :
    Enemy()
{
}

BossRight::~BossRight()
{
}

void BossRight::Init()
{
    Enemy::Init();

    auto rightHand = new BossRightHand;
    rightHand->SetTag(Tag::kBossRightHand);
    rightHand->SetRect(MakeRectCenter(Const::kBossRightHandStartPosX, Const::kBossRightHandStartPosY,
                                      Const::kBossRightHandWidth, Const::kBossRightHandHeight));
	if (registerGameObject) registerGameObject(rightHand);
    rightHand->Init();
}

void BossRight::Update()
{
    GameObject::Update();
}

void BossRight::Render(const HDC hdc)
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

void BossRight::OnCollisionEnter(GameObject* other)
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

BossRightHand::BossRightHand() :
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

BossRightHand::~BossRightHand()
{
}

void BossRightHand::Init()
{
    Enemy::Init();

    hp = 30;
}

void BossRightHand::Update()
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
			if (playersRect.right < rect.left)
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
                                   Const::kBossRightHandStartPosX, Const::kBossRightHandStartPosY) < 50.0)
    {
        rect = MakeRectCenter(Const::kBossRightHandStartPosX, Const::kBossRightHandStartPosY,
                              Const::kBossRightHandWidth, Const::kBossRightHandHeight);
        velocityX = 0;
        velocityY = 0;
        isPunched = false;
        isReturning = false;
        punchCoolDown = 3.0;
    }

    Move();
}

void BossRightHand::Render(const HDC hdc)
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

void BossRightHand::OnCollisionEnter(GameObject* other)
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
					auto rights = findGameObjects(Tag::kBossRight);
					if (!rights.empty())
					{
						for (auto & right : rights)
						{
							if (destroyGameObject) destroyGameObject(right->GetId());
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

void BossRightHand::Punch()
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

void BossRightHand::Return()
{
    auto angle = GetAngle((rect.left + rect.right) / 2, (rect.top + rect.bottom) / 2,
                          Const::kBossRightHandStartPosX, Const::kBossRightHandStartPosY);
    velocityX = 5.0 * cos(angle);
    velocityY = 5.0 * -sin(angle);
    targetX = Const::kBossRightHandStartPosX;
    targetY = Const::kBossRightHandStartPosY;

    isReturning = true;
}

void BossRightHand::FirePizza()
{
    double i = M_PI * 2 - M_PI / 3;
    for (; i > M_PI; i -= M_PI / 24.0)
    {
        auto bullet = new Bullet;
        bullet->SetTag(Tag::kEnemyBullet);
        bullet->SetRect(MakeRectCenter((rect.left + rect.right) / 2, (rect.top + rect.bottom) / 2,
                                       Const::kBulletWidth, Const::kBulletHeight));
        bullet->SetVelocityX((pizzaSpeed + (i - M_PI / 3) * 5) * cos(i));
        bullet->SetVelocityY((pizzaSpeed + (i - M_PI / 3) * 3) * -sin(i));
        bullet->Init();
		if (registerGameObject) registerGameObject(bullet);
    }
}
