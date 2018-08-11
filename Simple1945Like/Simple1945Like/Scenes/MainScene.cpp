#include "stdafx.h"
#include "MainScene.h"
#include "gameobjects/GameObject.h"
#include "Constants/Constant.h"
#include "Utilities/CommonMacroFunction.h"
#include "gameobjects/characters/Player.h"
#include "gameobjects/characters/Barrack.h"
#include "gameobjects/characters/Boss/Boss.h"
#include "gameobjects/characters/Boss/BossAnim.h"

using Const = ConstantTable;

bool IsFinished = false;

MainScene::MainScene() :
    hBit(nullptr),
    background(nullptr),
    isFinished(false),
    deltaTime(0.0),
    gameObjectId(0),
    isBeganPhaseTwo(false),
    isBeganBreakTime(false)
{
}

MainScene::~MainScene()
{
}

HRESULT MainScene::Init()
{
    LoadImages();

    collisionTags[Tag::kPlayer].push_back(Tag::kBoss);
    collisionTags[Tag::kPlayer].push_back(Tag::kBossLeft);
    collisionTags[Tag::kPlayer].push_back(Tag::kBossLeftHand);
    collisionTags[Tag::kPlayer].push_back(Tag::kBossRight);
    collisionTags[Tag::kPlayer].push_back(Tag::kBossRightHand);
    collisionTags[Tag::kPlayer].push_back(Tag::kEnemyBullet);
    collisionTags[Tag::kPlayer].push_back(Tag::kPawn);

    collisionTags[Tag::kIdle].push_back(Tag::kPlayersBullet);

    collisionTags[Tag::kBoss].push_back(Tag::kPlayersBullet);
    collisionTags[Tag::kBossLeft].push_back(Tag::kPlayersBullet);
    collisionTags[Tag::kBossLeftHand].push_back(Tag::kPlayersBullet);
    collisionTags[Tag::kBossRight].push_back(Tag::kPlayersBullet);
    collisionTags[Tag::kBossRightHand].push_back(Tag::kPlayersBullet);

    collisionTags[Tag::kPawn].push_back(Tag::kPlayersBullet);

    Reset();

    return S_OK;
}

void MainScene::Release()
{
    if (hBit)
    {
        DeleteObject(hBit);
    }

    if (background)
    {
        DeleteObject(background);
    }
}

void MainScene::Update()
{
    if (isFinished)
    {
        KillTimer(hWnd, 0);
    }

    auto currentTime = chrono::system_clock::now();
    deltaTime = currentTime - previousTime;
    previousTime = currentTime;

    chrono::duration<double> elapsedTime = currentTime - startTime;

    if (!isBeganBreakTime &&
        elapsedTime.count() > static_cast<double>(Const::kBreakTimeBegin))
    {
        BreakTimeInit();

        isBeganBreakTime = true;
    }

    if (isBeganBreakTime &&
        !isBeganPhaseTwo &&
        elapsedTime.count() > static_cast<double>(Const::kPhaseTwoBegin))
    {
        PhaseTwoInit();

        isBeganPhaseTwo = true;
    }

    for (auto go : gameObjects)
    {
		if (go)
		{
			go->Update();
			go->Action();
		}
    }

    ActCollisionEvent();
    GarbageCollect();

	deleteObjects();
}

void MainScene::Render(HDC hdc)
{
    DrawBackground(hdc, background);

    for (auto go : gameObjects)
    {
		if (go)
			go->Render(hdc);
    }

    HPEN myPen = CreatePen(PS_SOLID, 1, Const::kWhite);
    HPEN oldPen = (HPEN)SelectObject(hdc, myPen);
    HBRUSH myBrush = CreateSolidBrush(Const::kWhite);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
    DrawRectangle(hdc, 0, 0, 500, Const::kStatusHeight);
    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(myPen);
    DeleteObject(myBrush);

    HFONT myFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, "Malgun Gothic");
    HFONT oldfont = (HFONT)SelectObject(hdc, myFont);
    string timeText = "보스 체력 : ";
    auto boss = FindGameObjects(Tag::kBoss);
    if (!boss.empty())
    {
        timeText += to_string(boss.front()->GetHp());
    }
    //string timeText = "NUM OBJECTS : " + to_string(gameObjects.size());
    TextOut(hdc, 10, 0, timeText.c_str(), timeText.size());

    string manaText = "마나 : ";
    auto players = FindGameObjects(Tag::kPlayer);
    if (!players.empty())
    {
        Player* player = (Player*)players.front();
        manaText += to_string(player->GetMana());
    }
    else
    {
        manaText = "";
    }

    TextOut(hdc, WINDOW_WIDTH / 2 + 50, 0, manaText.c_str(), manaText.size());
    SelectObject(hdc, oldfont);
    DeleteObject(myFont);

    if (IsFinished)
    {
        KillTimer(hWnd, 0);
        auto boss = FindGameObjects(Tag::kBoss);
        if (boss.empty() && !FindGameObjects(Tag::kPlayer).empty())
        {
            timeText = "클리어!";
        }
        else
        {
            timeText = "게임 오버";
        }

        if (MessageBox(hWnd, timeText.c_str(), " ", MB_RETRYCANCEL) == IDRETRY)
        {
            Reset();
            SendMessage(hWnd, WM_CREATE, 0, 0);
        }
        else
        {
            SendMessage(hWnd, WM_DESTROY, 0, 0);
        }
    }
}

LRESULT MainScene::MainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return DefWindowProc(hWnd, message, wParam, lParam);
}

void MainScene::RenderProc(HWND hWnd, UINT message, UINT idEvent, DWORD time)
{
    Update();

    RECT crt;
    GetClientRect(hWnd, &crt);
    HDC hDC = GetDC(hWnd);
    if (hBit == nullptr)
    {
        hBit = CreateCompatibleBitmap(hDC, crt.right, crt.bottom);
    }

    HDC hMemDC = CreateCompatibleDC(hDC);
    HBITMAP oldBit = (HBITMAP)SelectObject(hMemDC, hBit);

    //FillRect(hMemDC, &crt, GetSysColorBrush(COLOR_WINDOW));
    SetBkMode(hMemDC, TRANSPARENT);

    Render(hMemDC);

    BitBlt(hDC, 0, 0, crt.right, crt.bottom, hMemDC, 0, 0, SRCCOPY);
    SelectObject(hMemDC, oldBit);
    DeleteDC(hMemDC);
    ReleaseDC(hWnd, hDC);
}

void MainScene::LoadImages()
{
    background = (HBITMAP)LoadImage(hInst, "assets\\Untitled.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void MainScene::Reset()
{
    deltaTime = chrono::duration<double>();
    IsFinished = false;
    isBeganPhaseTwo = false;
    isBeganBreakTime = false;
    gameObjectId = 0;
    gameObjects.resize(0);

    PhaseOneInit();

    startTime = chrono::system_clock::now();
    previousTime = chrono::system_clock::now();
}

void MainScene::DrawBackground(HDC hdc, HBITMAP hBit)
{
    HDC hMemDC = CreateCompatibleDC(hdc);
    HBITMAP oldBit = (HBITMAP)SelectObject(hMemDC, hBit);

    StretchBlt(hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hMemDC, 0, 0, 428, 600, SRCCOPY);

    SelectObject(hMemDC, oldBit);
    DeleteDC(hMemDC);
}

void MainScene::RegisterGameObject(GameObject* go)
{
    go->SetId(gameObjectId);
    ++gameObjectId;
    go->SetRegisterGameObjectCallback(bind(&MainScene::RegisterGameObject, this, placeholders::_1));
    go->SetDestroyGameObjectCallback(bind(&MainScene::DestroyGameObject, this, placeholders::_1));
    go->SetFindGameObjectsCallback(bind(&MainScene::FindGameObjects, this, placeholders::_1));
    gameObjects.push_back(go);
}

void MainScene::DestroyGameObject(int id)
{
    //auto it = gameObjects.begin();
    //for (; it != gameObjects.end(); ++it)
    //{
    //    if ((*it)->GetId() == id)
    //    {
    //        break;
    //    }
    //}

    //if (it != gameObjects.end())
    //{
    //    gameObjects.erase(it);
    //}

	for (auto go : toDeleteGameObjects)
	{
		if (go->GetId() == id)
		{
			return;
		}
	}

	for (auto go : gameObjects)
	{
		if (go->GetId() == id)
		{
			toDeleteGameObjects.emplace_back(go);
			return;
		}
	}
}

vector<GameObject*> MainScene::FindGameObjects(Tag tag)
{
    vector<GameObject*> gos;
    for (auto& go : gameObjects)
    {
        if (go->GetTag() == tag)
        {
            gos.push_back(go);
        }
    }

    return gos;
}

void MainScene::ActCollisionEvent()
{
    for (auto& tag : collisionTags)
    {
        ActCollisionEvent(tag.first);
    }
}

bool MainScene::HasCollision(GameObject* go1, GameObject* go2)
{
    RECT temp;

    if (IntersectRect(&temp, &go1->GetRect(), &go2->GetRect()))
    {
        return true;
    }

    return false;
}

void MainScene::GarbageCollect()
{
    for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
    {
        RECT rect = (*it)->GetRect();
        if (rect.left > WINDOW_WIDTH ||
            rect.top < (Const::kStatusHeight - 200) ||
            rect.right < 0 ||
            rect.bottom > WINDOW_HEIGHT)
        {
			DestroyGameObject((*it)->GetId());
        }
    }
}

void MainScene::PhaseOneInit()
{
    auto player = new Player;
    player->SetTag(Tag::kPlayer);
    player->SetRect(MakeRectCenter(Const::kPlayerStartPosX, Const::kPlayerStartPosY,
                                   Const::kPlayerWidth, Const::kPlayerHeight));
    player->SetVelocityX(10.0);
    player->SetVelocityY(10.0);
    RegisterGameObject(player);

    auto barrack = new Barrack;
    barrack->SetTag(Tag::kBarrack);
    barrack->SetRect(MakeRectCenter(Const::kBarrackStartPosX, Const::kBarrackStartPosY,
                                    Const::kBarrackWidth, Const::kBarrackHeight));
    RegisterGameObject(barrack);

    for (auto& go : gameObjects)
    {
        go->Init();
    }
}

void MainScene::PhaseTwoInit()
{
    auto boss = new Boss;
    boss->SetTag(Tag::kBoss);
    boss->SetRect(MakeRectCenter(Const::kBossStartPosX, Const::kBossStartPosY,
                                 Const::kBossWidth, Const::kBossHeight));
    RegisterGameObject(boss);
    boss->Init();

    for (auto go : FindGameObjects(Tag::kIdle))
    {
        DestroyGameObject(go->GetId());
    }
}

void MainScene::deleteObjects()
{
	for (auto it = toDeleteGameObjects.begin(); it != toDeleteGameObjects.end();)
	{
		GameObject* pGO = *it;
		if (pGO)
		{
			for (auto it2 = gameObjects.begin(); it != gameObjects.end();)
			{
				GameObject* pGO2 = *it2;
				if (pGO2 == pGO)
				{
					gameObjects.erase(it2);
					break;
				}
				else
				{
					++it2;
				}
			}

			delete pGO;
			it = toDeleteGameObjects.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void MainScene::BreakTimeInit()
{
    auto bossAnim = new BossAnim;
    bossAnim->SetTag(Tag::kIdle);
    bossAnim->SetRect(MakeRectCenter(Const::kBossStartPosX, 0,
                                     Const::kBossWidth, Const::kBossHeight));
    bossAnim->SetVelocityY(3.0);
    RegisterGameObject(bossAnim);
    bossAnim->Init();
}

void MainScene::ActCollisionEvent(Tag actorTag)
{
    vector<GameObject*> actors;
    for (auto& go : gameObjects)
    {
        if (go->GetTag() == actorTag)
        {
            actors.push_back(go);
        }
    }

    vector<GameObject*> others;
    for (auto& otherTag : collisionTags[actorTag])
    {
        for (auto& go : gameObjects)
        {
            if (go->GetTag() == otherTag)
            {
                others.push_back(go);
            }
        }
    }

    for (auto& actor : actors)
    {
        for (auto& other : others)
        {
            if (HasCollision(actor, other))
            {
                actor->OnCollisionEnter(other);
            }
        }
    }
}
