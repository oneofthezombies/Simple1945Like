#pragma once

inline RECT MakeRect(int x, int y, int width, int height)
{
    return RECT { x, y, x + width, y + height };
}

inline RECT MakeRectCenter(int x, int y, int width, int height)
{
    return RECT { x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2) };
}

inline void DrawLine(HDC& hdc, int x1, int y1, int x2, int y2)
{
    MoveToEx(hdc, x1, y1, NULL);
    LineTo(hdc, x2, y2);
}

inline void DrawRectangle(HDC& hdc, int x, int y, int width, int height)
{
    Rectangle(hdc, x, y, x + width, y + height);
}

inline void DrawRectangleCenter(HDC& hdc, int x, int y, int width, int height)
{
    Rectangle(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

inline void DrawEllipse(HDC& hdc, int x, int y, int width, int height)
{
    Ellipse(hdc, x, y, x + width, y + height);
}

inline void DrawEllipseCenter(HDC& hdc, int x, int y, int width, int height)
{
    Ellipse(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

inline void DrawCircleCenter(HDC& hdc, int x, int y, int radius)
{
    Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
}

inline double GetAngle(double x1, double y1, double x2, double y2)
{
    double x = x2 - x1;
    double y = y2 - y1;
    //두점 사이의 거리를 구하는 공식
    double distance = sqrt(x * x + y *y);
    //두점 사이의 각도 구하는 공식
    double angle = acos(x / distance);

    if (y2 > y1)
    {
        angle = -angle;

        if (angle >= 2.0 * M_PI) angle -= 2.0 * M_PI;
    }

    return angle;
}

inline double GetDistance(double x1, double y1, double x2, double y2)
{
    double x = abs(x2 - x1);
    double y = abs(y2 - y1);

    return hypot(x, y);
}