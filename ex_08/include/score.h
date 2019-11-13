#ifndef _SCORE_H_ 
#define _SCORE_H_

#include <bitset>
#include <vector>

struct S_Digit
{
    std::bitset<8> letter;

    //each bit is equivalent to a line
    //if the bit is on (true), then vertex is activated
    // .__0__.
    // |     |
    // 1     2
    // .__3__.
    // |     |
    // 4     5
    // .__6__.
    // ___7___  //underline
    // 

    void draw(float offsetX, float offsetY, float size);
};

class Score
{
public:
    std::vector<S_Digit> string;
    float size;
public:
    void addDigit(unsigned char digit);
    void addNumber(unsigned int n);
    void setNumber(unsigned int n);
    void draw();
};

#endif