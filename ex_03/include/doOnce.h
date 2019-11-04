#ifndef _DO_ONCE_H_
#define _DO_ONCE_H_

struct S_DoOnce
{
private:
    bool lastState = false;
    
public:
    bool isOn = false;
    
    void input(bool b)
    {
        if (b && lastState != b)
        {
            isOn = !isOn;
        }
        lastState = b;
    }
};

#endif