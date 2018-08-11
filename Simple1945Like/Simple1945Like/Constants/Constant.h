#pragma once

struct ConstantTable
{
    static const COLORREF kWhite = RGB(255, 255, 255);
    static const COLORREF kBlack = RGB(0, 0, 0);
    static const COLORREF kRed = RGB(255, 0, 0);
    static const COLORREF kGreen = RGB(0, 255, 0);
    static const COLORREF kBlue = RGB(0, 0, 255);
    static const COLORREF kCyan = RGB(0, 255, 255);
    static const COLORREF kMagenta = RGB(255, 0, 255);
    static const COLORREF kYellow = RGB(255, 255, 0);

    static const int kPlayerStartPosX = WINDOW_WIDTH / 2;
    static const int kPlayerStartPosY = WINDOW_HEIGHT / 2 + 200;
    static const int kPlayerWidth = 20;
    static const int kPlayerHeight = kPlayerWidth;

    static const int kBulletWidth = 8;
    static const int kBulletHeight = kBulletWidth;
    static const int kBulletSpeed = 6;

    static const int kBossStartPosX = WINDOW_WIDTH / 2;
    static const int kBossStartPosY = WINDOW_HEIGHT / 2 - 200;
    static const int kBossWidth = 100;
    static const int kBossHeight = 100;

    static const int kBossLeftStartPosX = kBossStartPosX - 100;
    static const int kBossLeftStartPosY = kBossStartPosY;
    static const int kBossLeftWidth = 70;
    static const int kBossLeftHeight = 70;
    static const int kBossLeftOffset = kBossLeftWidth / 7;

    static const int kBossLeftHandStartPosX = kBossLeftStartPosX - 50;
    static const int kBossLeftHandStartPosY = kBossLeftStartPosY + 70;
    static const int kBossLeftHandWidth = 50;
    static const int kBossLeftHandHeight = 50;
    static const int kBossLeftHandOffset = kBossLeftHandWidth / 5;

    static const int kBossRightStartPosX = kBossStartPosX + 100;
    static const int kBossRightStartPosY = kBossStartPosY;
    static const int kBossRightWidth = 70;
    static const int kBossRightHeight = 70;
    static const int kBossRightOffset = kBossRightWidth / 7;

    static const int kBossRightHandStartPosX = kBossRightStartPosX + 50;
    static const int kBossRightHandStartPosY = kBossRightStartPosY + 70;
    static const int kBossRightHandWidth = 50;
    static const int kBossRightHandHeight = 50;
    static const int kBossRightHandOffset = kBossRightHandWidth / 5;

    static const int kStatusHeight = 50;

    static const int kBombWidth = 10;
    static const int kBombHeight = kBombWidth;

    static const int kBarrackStartPosX = WINDOW_WIDTH / 2;
    static const int kBarrackStartPosY = 20;
    static const int kBarrackWidth = WINDOW_WIDTH - 100;
    static const int kBarrackHeight = 10;

    static const int kPawnWidth = 15;
    static const int kPawnHeight = kPawnWidth;
    static const int kPawnVelocityY = 3;
    static const int kPawnVelocityX = 3;

    static const int kBreakTimeBegin = 5;
    static const int kPhaseTwoBegin = kBreakTimeBegin + 4;
};
