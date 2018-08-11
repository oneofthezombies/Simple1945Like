#include "stdafx.h"
#include "Player.h"
#include "Constants/Constant.h"
#include "Utilities/CommonMacroFunction.h"
#include "Managers/Input.h"
#include "gameobjects/Projectiles/Bullet.h"

using Const = ConstantTable;

Player::Player() :
    GameObject(),
    fireBulletCoolDown(0.0),
    mana(100),
    onBarrier(false)
{
}

Player::~Player()
{
}

void Player::Init()
{
    GameObject::Init();
}

void Player::Update()
{
    GameObject::Update();

    fireBulletCoolDown -= deltaTime.count();

    if (INPUT->IsStayKeyDown(VK_LEFT))
    {
        MoveX(-velocityX);
        if (rect.left < 0)
        {
            rect.left = 0;
            rect.right = Const::kPlayerWidth;
        }
    }

    if (INPUT->IsStayKeyDown(VK_RIGHT))
    {
        MoveX(velocityX);
        if (rect.right > WINDOW_WIDTH)
        {
            rect.right = WINDOW_WIDTH;
            rect.left = rect.right - Const::kPlayerWidth;
        }
    }

    if (INPUT->IsStayKeyDown(VK_UP))
    {
        MoveY(-velocityY);
        if (rect.top < Const::kStatusHeight)
        {
            rect.top = Const::kStatusHeight;
            rect.bottom = rect.top + Const::kPlayerHeight;
        }
    }

    if (INPUT->IsStayKeyDown(VK_DOWN))
    {
        MoveY(velocityY);
        if (rect.bottom > WINDOW_HEIGHT)
        {
            rect.bottom = WINDOW_HEIGHT;
            rect.top = rect.bottom - Const::kPlayerHeight;
        }
    }

    if (INPUT->IsStayKeyDown(VK::Q))
    {
        if (fireBulletCoolDown < 0)
        {
            FireBullet();
        }
    }


    if (INPUT->IsStayKeyDown(VK::W))
    {
        if (mana > 0)
        {
            Barrier();
        }
    }
    else
    {
        onBarrier = false;
        barrier.top = rect.top + 15;
        barrier.bottom = rect.bottom - 15;
        barrier.left = rect.left + 15;
        barrier.right = rect.right - 15;

        if (mana < 100)
        {
            mana++;
        }
    }

    if (INPUT->IsOnceKeyDown(VK::E))
    {
        //FireHomingMissile();
    }

    if (INPUT->IsOnceKeyDown(VK::R))
    {
        //SelfExplosion();
    }
}

void Player::Render(HDC hdc)
{
    if (onBarrier && mana > 0)
    {
        HPEN myPen = CreatePen(PS_SOLID, 10, Const::kCyan);
        HPEN oldPen = (HPEN)SelectObject(hdc, myPen);
        Rectangle(hdc, barrier.left, barrier.top, barrier.right, barrier.bottom);
        SelectObject(hdc, oldPen);
        DeleteObject(myPen);
    }

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

void Player::OnCollisionEnter(GameObject* other)
{
    switch (other->GetTag())
    {
        case Tag::kBoss:
        case Tag::kBossLeft:
        case Tag::kBossRight:
        case Tag::kBossLeftHand:
        case Tag::kBossRightHand:
        case Tag::kPawn:
        {
			// CHEAT KEY
			//IsFinished = true;
			//if (destroyGameObject) destroyGameObject(GetId());
        }
        break;
        case Tag::kEnemyBullet:
        {
            if (onBarrier)
            {
                if (mana >= 10)
                {
                    mana -= 10;
                }

				if (destroyGameObject) destroyGameObject(other->GetId());
            }
            else
            {
				// CHEAT KEY
                //IsFinished = true;
                //if (destroyGameObject) destroyGameObject(GetId());
            }
        }
        break;
        default:
        {
        }
        break;
    }
}

void Player::FireBullet()
{
    auto bullet1 = new Bullet;
    bullet1->SetTag(Tag::kPlayersBullet);
    bullet1->SetRect(MakeRectCenter((rect.left + rect.right) / 2, rect.top - 5, 
                                   Const::kBulletWidth, Const::kBulletHeight));
    bullet1->SetVelocityY(-11.0);
    bullet1->Init();
    if (registerGameObject) registerGameObject(bullet1);

    auto bullet2 = new Bullet;
    bullet2->SetTag(Tag::kPlayersBullet);
    bullet2->SetRect(MakeRectCenter((rect.left + rect.right) / 2 - Const::kBulletWidth * 2, rect.top - 5,
                                   Const::kBulletWidth, Const::kBulletHeight));
    bullet2->SetVelocityX(-1.0);
    bullet2->SetVelocityY(-10.0);
    bullet2->Init();
	if (registerGameObject) registerGameObject(bullet2);

    auto bullet3 = new Bullet;
    bullet3->SetTag(Tag::kPlayersBullet);
    bullet3->SetRect(MakeRectCenter((rect.left + rect.right) / 2 + Const::kBulletWidth * 2, rect.top - 5,
                                   Const::kBulletWidth, Const::kBulletHeight));
    bullet3->SetVelocityX(1.0);
    bullet3->SetVelocityY(-10.0);
    bullet3->Init();
	if (registerGameObject) registerGameObject(bullet3);

    fireBulletCoolDown = 0.2;
}

void Player::FireLaser()
{

}

void Player::FireHomingMissile()
{

}

void Player::SelfExplosion()
{

}

void Player::Barrier()
{
    onBarrier = true;
    barrier.top = rect.top - 2;
    barrier.bottom = rect.bottom + 2;
    barrier.left = rect.left - 2;
    barrier.right = rect.right + 2;
    mana--;
}

int Player::GetMana()
{
    return mana;
}
