#pragma once

#include "Tags/Tag.h"

class GameObject;

class MainScene
{
public:
    MainScene();
    virtual ~MainScene();

    virtual HRESULT Init();
    virtual void Release();
    virtual void Update();
    virtual void Render(HDC hdc);

    LRESULT MainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    void RenderProc(HWND hWnd, UINT message, UINT idEvent, DWORD time);

    void LoadImages();
    void DrawBackground(HDC hdc, HBITMAP hBit);
    void Reset();

    void RegisterGameObject(GameObject* go);
    void DestroyGameObject(int id);
    vector<GameObject*> FindGameObjects(Tag tag);

    void ActCollisionEvent();
    void ActCollisionEvent(Tag actorTag);
    bool HasCollision(GameObject* go1, GameObject* go2);

    void GarbageCollect();

    void PhaseOneInit();
    void BreakTimeInit();
    void PhaseTwoInit();

private:
	void deleteObjects();

private:
    HBITMAP hBit;
    HBITMAP background;

    chrono::time_point<chrono::system_clock> startTime;
    chrono::time_point<chrono::system_clock> previousTime;
    chrono::duration<double> deltaTime;
    bool isFinished;

    vector<GameObject*> gameObjects;
	vector<GameObject*> toDeleteGameObjects;
    map<Tag, vector<Tag>> collisionTags;
    int gameObjectId;

    bool isBeganPhaseTwo;
    bool isBeganBreakTime;
};
