#include "stdafx.h"
#include "Enemy.h"
#include "Constants/Constant.h"
#include "gameobjects/Projectiles/Bullet.h"
#include "Utilities/CommonMacroFunction.h"

using Const = ConstantTable;

Enemy::Enemy() : 
    GameObject(), 
    fireBulletCoolDown(0.0)
{
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
    GameObject::Init();
}

void Enemy::Update()
{
    GameObject::Update();

    fireBulletCoolDown -= deltaTime.count();
    if (fireBulletCoolDown < 0)
    {
        FireBullet();
    }
}

void Enemy::Render(const HDC hdc)
{
}

void Enemy::OnCollisionEnter(GameObject* other)
{
}

void Enemy::FireBullet()
{
    auto bullet = new Bullet;
    bullet->SetTag(Tag::kEnemyBullet);
    bullet->SetRect(MakeRectCenter((rect.left + rect.right) / 2, rect.bottom + 10,
                                    Const::kBulletWidth, Const::kBulletHeight));
    auto players = findGameObjects(Tag::kPlayer);
    if (!players.empty())
    {
        auto playersRect = players.front()->GetRect();

        if (rect.top > playersRect.top)
        {
            bullet->SetVelocityY(Const::kBulletSpeed);
        }
        else
        {
            double angle = GetAngle(rect.left, rect.top, playersRect.left, playersRect.top);
            bullet->SetVelocityX(Const::kBulletSpeed * cos(angle));
            bullet->SetVelocityY(Const::kBulletSpeed * -sin(angle));
        }
    }
    else
    {
        bullet->SetVelocityY(Const::kBulletSpeed);
    }

    bullet->Init();
	if (registerGameObject) registerGameObject(bullet);

    fireBulletCoolDown = 2.0;
}
