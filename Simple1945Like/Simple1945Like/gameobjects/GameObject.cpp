#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject() : 
    //registerGameObject(function<void(GameObject*)>()),
    //destroyGameObject(function<void(int)>()),
    //findGameObjects(function<vector<GameObject*>(Tag)>()),
    //action(function<void()>()), 
    parent(nullptr),
    rect(RECT()),
    tag(Tag::kIdle),
    hp(0),
    lifeTime(0.0),
    velocityX(0.0),
    velocityY(0.0),
    id(-1),
    deltaTime(chrono::duration<double>()),
    image(nullptr)
{
}

GameObject::~GameObject()
{
}

void GameObject::Init()
{
    previousTime = chrono::system_clock::now();

    action = bind(&GameObject::DoNothing, this);

    for (auto& child : children)
    {
        child->Init();
    }
}

void GameObject::Update()
{
    deltaTime = chrono::system_clock::now() - previousTime;
    previousTime = chrono::system_clock::now();

    for (auto& child : children)
    {
        child->Update();
    }
}

void GameObject::Render(const HDC hdc)
{
    for (auto& child : children)
    {
        child->Render(hdc);
    }
}

void GameObject::OnCollisionEnter(GameObject* other)
{
}

void GameObject::SetRegisterGameObjectCallback(function<void(GameObject*)> method)
{
	if (method)
		registerGameObject = method;
}

void GameObject::SetDestroyGameObjectCallback(function<void(int)> method)
{
	if (method)
		destroyGameObject = method;
}

void GameObject::SetFindGameObjectsCallback(function<vector<GameObject*>(Tag)> method)
{
	if (method)
		findGameObjects = method;
}

void GameObject::DoNothing()
{
}

void GameObject::Action()
{
    if (action)
    {
        action();
    }
}

void GameObject::Move()
{
    rect.left += static_cast<LONG>(velocityX);
    rect.right += static_cast<LONG>(velocityX);
    rect.top += static_cast<LONG>(velocityY);
    rect.bottom += static_cast<LONG>(velocityY);
}

void GameObject::MoveX(double velocity)
{
    rect.left += static_cast<LONG>(velocity);
    rect.right += static_cast<LONG>(velocity);
}

void GameObject::MoveY(double velocity)
{
    rect.top += static_cast<LONG>(velocity);
    rect.bottom += static_cast<LONG>(velocity);
}

void GameObject::SetPosition(const int x, const int y)
{
    LONG width = rect.right - rect.left;
    LONG height = rect.bottom - rect.top;

    rect.left = static_cast<LONG>(x);
    rect.top = static_cast<LONG>(y);
    rect.right = rect.left + width;
    rect.bottom = rect.top + height;
}

void GameObject::SetRect(const RECT rect)
{
    this->rect.left = rect.left;
    this->rect.top = rect.top;
    this->rect.right = rect.right;
    this->rect.bottom = rect.bottom;
}

RECT GameObject::GetRect() const
{
    return rect;
}

void GameObject::SetVelocityX(const double velocity)
{
    velocityX = velocity;
}

void GameObject::SetVelocityY(const double velocity)
{
    velocityY = velocity;
}

double GameObject::GetVelocityX()
{
    return velocityX;
}

double GameObject::GetVelocityY()
{
    return velocityY;
}

void GameObject::IncDecHp(const int value)
{
    hp += value;
}

void GameObject::IncDecLifeTime(const int value)
{
    lifeTime += value;
}

void GameObject::SetTag(const Tag tag)
{
    this->tag = tag;
}

Tag GameObject::GetTag() const
{
    return tag;
}

void GameObject::SetId(const int id)
{
    this->id = id;
}

int GameObject::GetId() const
{
    return id;
}

void GameObject::SetParent(GameObject* parent)
{
    this->parent = parent;
}

void GameObject::SetChild(GameObject* child)
{
    child->SetParent(this);
    children.push_back(child);
}

int GameObject::GetHp() const
{
    return hp;
}
