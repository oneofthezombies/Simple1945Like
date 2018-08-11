#pragma once

#include "Utilities/SingletonBase.h"

#define RANDOM Random::GetInstance()

class Random : public SingletonBase<Random>
{
public:
    Random()
    {
        srand(GetTickCount());
    }

    virtual ~Random() {}

    inline int GetInt(int num)
    {
        return rand() % num;
    }

    inline int GetIntFromTo(int from, int to)
    {
        return rand() % (to - from + 1) + from;
    }

    inline double GetDoubleFromTo(double fMin, double fMax)
    {
        double f = (double)rand() / RAND_MAX;
        return fMin + f * (fMax - fMin);
    }
};
