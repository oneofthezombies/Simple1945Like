#include "stdafx.h"
#include "Boss.h"
#include "Constants/Constant.h"
#include "BossLeft.h"
#include "BossRight.h"
#include "Utilities/CommonMacroFunction.h"
#include "Utilities/Random.h"
#include "gameobjects/Projectiles/Bullet.h"
#include "gameobjects/Projectiles/Bomb.h"

using Const = ConstantTable;

Boss::Boss() :
    Enemy(),
    pizzaSpeed(5.0),
    pizzaCoolDown(0.0),
    laserCoolDown(3.0),
    laserSpeed(4.0),
    bombCoolDown(3.0),
    moveCoolDown(2.0)
{
}

Boss::~Boss()
{
}

void Boss::Init()
{
    GameObject::Init();

    hp = 100;

    auto bossLeft = new BossLeft;
    bossLeft->SetTag(Tag::kBossLeft);
    bossLeft->SetRect(MakeRectCenter(Const::kBossLeftStartPosX, Const::kBossLeftStartPosY, 
                                     Const::kBossLeftWidth, Const::kBossLeftHeight));
	if (registerGameObject) registerGameObject(bossLeft);
    bossLeft->Init();

    auto bossRight = new BossRight;
    bossRight->SetTag(Tag::kBossRight);
    bossRight->SetRect(MakeRectCenter(Const::kBossRightStartPosX, Const::kBossRightStartPosY,
                                     Const::kBossRightWidth, Const::kBossRightHeight));
	if (registerGameObject) registerGameObject(bossRight);
    bossRight->Init();
}

void Boss::Update()
{
    GameObject::Update();

	if (findGameObjects)
	{
		auto lefts = findGameObjects(Tag::kBossLeftHand);
		auto rights = findGameObjects(Tag::kBossRightHand);

		if (lefts.empty() && rights.empty())
		{
			bombCoolDown -= deltaTime.count();
			if (bombCoolDown < 0.0)
			{
				FireBomb();
			}

			laserCoolDown -= deltaTime.count();
			if (laserCoolDown < 0.0)
			{
				FireLaser();
			}

			moveCoolDown -= deltaTime.count();
			if (moveCoolDown < 0.0)
			{
				velocityX = RANDOM->GetDoubleFromTo(-4.0, 4.0);
				velocityY = RANDOM->GetDoubleFromTo(-4.0, 4.0);
				moveCoolDown = 2.0;
			}

			Move();

			if (rect.left < 10)
			{
				rect.left = 10;
				rect.right = rect.left + Const::kBossWidth;
			}

			if (rect.right > WINDOW_WIDTH - 10)
			{
				rect.right = WINDOW_WIDTH - 10;
				rect.left = rect.right - Const::kBossWidth;
			}

			if (rect.bottom > WINDOW_HEIGHT / 2)
			{
				rect.bottom = WINDOW_HEIGHT / 2;
				rect.top = rect.bottom - Const::kBossHeight;
			}

			if (rect.top < Const::kStatusHeight + 10)
			{
				rect.top = Const::kStatusHeight + 10;
				rect.bottom = rect.top + Const::kBossHeight;
			}
		}

		pizzaCoolDown -= deltaTime.count();
		if (pizzaCoolDown < 0.0)
		{
			//FirePizza();
		}

		laserCoolDown -= deltaTime.count();
		if (laserCoolDown < 0.0)
		{
			//FireLaser();
		}
	}
}

void Boss::Render(const HDC hdc)
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

void Boss::OnCollisionEnter(GameObject* other)
{
    switch (other->GetTag())
    {
        case Tag::kPlayersBullet:
        {
			if (destroyGameObject) destroyGameObject(other->GetId());

			if (findGameObjects)
			{
				auto lefts = findGameObjects(Tag::kBossLeftHand);
				auto rights = findGameObjects(Tag::kBossRightHand);
				if (lefts.empty() && rights.empty())
				{
					hp--;
					if (hp < 0)
					{
						IsFinished = true;
						if (destroyGameObject) destroyGameObject(GetId());
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

void Boss::FirePizza()
{
    double i = M_PI / 6.0;
    for (; i < M_PI * 5.0 / 6.0; i += M_PI / 24.0)
    {
        auto bullet = new Bullet;
        bullet->SetTag(Tag::kEnemyBullet);
        bullet->SetRect(MakeRectCenter((rect.left + rect.right) / 2, rect.bottom,
                                       Const::kBulletWidth, Const::kBulletHeight));
        bullet->SetPosition(200, rect.bottom);
        bullet->SetVelocityX(pizzaSpeed * cos(i));
        bullet->SetVelocityY((pizzaSpeed + i * 5) * sin(i));
        bullet->Init();
		if (registerGameObject) registerGameObject(bullet);
    }

    pizzaCoolDown = 9999.0;
}

void Boss::FireLaser()
{
    double i = 0.0;
    for (; i < M_PI * 2; i += M_PI / 12.0)
    {
        for (int j = 0; j < 3; ++j)
        {
            auto bullet = new Bullet;
            bullet->SetTag(Tag::kEnemyBullet);
            bullet->SetRect(MakeRectCenter((rect.left + rect.right) / 2, rect.bottom,
                                           Const::kBulletWidth, Const::kBulletHeight));
            bullet->SetVelocityX(laserSpeed * cos(i) * RANDOM->GetDoubleFromTo(1.0, 2.0));
            bullet->SetVelocityY(laserSpeed * sin(i) * RANDOM->GetDoubleFromTo(1.0, 2.0));
            bullet->Init();
			if (registerGameObject) registerGameObject(bullet);
        }
    }

    laserCoolDown = 5.0;
}

void Boss::FireBomb()
{
    auto bomb = new Bomb;

    bomb->SetTag(Tag::kEnemyBullet);
    bomb->SetRect(MakeRectCenter((rect.left + rect.right) / 2, rect.bottom,
                                 Const::kBombWidth, Const::kBombHeight));
    double direction = -1.0;
    if (RANDOM->GetInt(2))
    {
        direction = 1.0;
    }
    bomb->SetVelocityX(direction * RANDOM->GetDoubleFromTo(1.0, 3.0));
    bomb->SetVelocityY(RANDOM->GetDoubleFromTo(1.0, 5.0));
    bomb->Init();
	if (registerGameObject) registerGameObject(bomb);

    bombCoolDown = 2.0;
}
