#ifndef _TIMELINE_H_
#define _TIMELINE_H_

#include <functional>
#include <cassert>
#include "macros.h"

#ifndef PI
#define PI 3.14
#endif

float lerp(float a, float b, float f)
{
    return a + f * (b - a);
}

float interpolate(float a, float b, float f, float duration = 1.f)
{
    assert(duration != 0.f);
    return a + ((cos(f * PI / duration) - 1.f) * (-1.f/2.f)) * (b - a);
}

struct TimeLine
{
    float startValue = 0.f;
    float endValue   = 0.f;

    float startTime  = 0.f;

    float interp(float time, float duration) const
    {
        return interpolate(startValue, endValue, time - startTime, duration);
    }

    void reset()
    {
        startValue = 0.f;
        endValue   = 0.f;

        startTime  = 0.f;
    }
};

#endif