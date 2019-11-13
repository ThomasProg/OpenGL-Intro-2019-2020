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



// class Timeline 
// {
// private:
//     bool bSet = false;
//     float startTime = 0.f;
//     std::function<void (float value)> tick;
//     std::function<float (float time)> curve = [=](float time)
//     {
//         return sin((time - startTime) * PI);
//     };

// public:
//     Timeline()
//     {
//     }

//     ~Timeline() {}

//     void setCurve(float (*curve)(float time)) //function used to calculate the curve relative to time
//     {
//         this->curve = curve;
//     }

//     //void start(void (*tickFunc)(float value)) //function running through the timeline
//     void start(std::function<void (float value)> tickFunc) //function running through the timeline
//     {
//         tick = tickFunc;
//         startTime = glfwGetTime();
//         bSet = true;
//     }

//     void run(float time)
//     {
//         if (bSet)
//             tick(curve(time));
//     }

//     void stop()
//     {
//        bSet = false; 
//     }
// };

#endif