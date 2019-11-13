#include "score.h"
#include "macros.h"

#include <cassert>

void S_Digit::draw(float offsetX, float offsetY, float size)
{
    for (unsigned int i = 0; i < 8; i++)
    {
        if (this->letter.test(i))
        {
            switch (i)
            {
                case 7 :
                    glVertex2d(offsetX, -offsetY);
                    glVertex2d(offsetX + size, -offsetY);
                    break;

                case 6 :
                    glVertex2d(offsetX, -(offsetY));
                    glVertex2d(offsetX, -(offsetY + size));
                    break;

                case 5 :
                    glVertex2d(offsetX + size, -offsetY);
                    glVertex2d(offsetX + size, -(offsetY + size));
                    break;

                case 4 :
                    glVertex2d(offsetX, -(offsetY + size));
                    glVertex2d(offsetX + size, -(offsetY + size));
                    break;

                case 3 :
                    glVertex2d(offsetX, -(offsetY + size));
                    glVertex2d(offsetX, -(offsetY + size * 2));
                    break;

                case 2 :
                    glVertex2d(offsetX + size, -(offsetY + size));
                    glVertex2d(offsetX + size, -(offsetY + size * 2));
                    break;

                case 1 :
                    glVertex2d(offsetX, -(offsetY + size * 2));
                    glVertex2d(offsetX + size, -(offsetY + size * 2));
                    break;

                case 0 :
                    glVertex2d(offsetX, -(offsetY + size * 2.5f));
                    glVertex2d(offsetX + size, -(offsetY + size * 2.5f));
                    break;
                default:;
            }
        }
    }
}

void Score::addDigit(unsigned char digit)
{
    S_Digit digitLines;
    switch (digit)
    {
        case 0:
            digitLines.letter = 0b11101110 & 0b11111111;
            break;
        case 1:
            digitLines.letter = 0b00100100 & 0b11111111;
            break;
        case 2:
            digitLines.letter = 0b10111010 & 0b11111111;
            break;
        case 3:
            digitLines.letter = 0b10110110 & 0b11111111;
            break;
        case 4:
            digitLines.letter = 0b01110100 & 0b11111111;
            break;
        case 5:
            digitLines.letter = 0b11010110 & 0b11111111;
            break;
        case 6:
            digitLines.letter = 0b11011110 & 0b11111111;
            break;
        case 7:
            digitLines.letter = 0b10100100 & 0b11111111;
            break;
        case 8:
            digitLines.letter = 0b11111110 & 0b11111111;
            break;
        case 9:
            digitLines.letter = 0b11110110 & 0b11111111;
            break;
        default:
            assert(digit < 10); //must be a digit
    }
    string.push_back(digitLines);
}

void Score::addNumber(unsigned int n)
{
    // unsigned int pow10 = 10;
    // unsigned int div = 1;
    // unsigned int digit;
    // while (div != 0)
    // {
    //     div    = char(n / pow10);
    //     pow10 *= 10; 
    // }

    // while (pow10 != 1)
    // {
    //     pow10 /= 10;
    //     digit = n / pow10;
    //     std::cout << digit << std::endl;
    //     this->addDigit(digit);
    //     n -= digit;
    // }

    while (n != 0)
    {
        this->addDigit(n % 10);
        n /= 10;
    }
}

void Score::setNumber(unsigned int n)
{
    string.clear();
    addNumber(n);
}

void Score::draw()
{
    glColor4f(1.f, 1.f, 1.f, 1.f);
    glBegin(GL_LINES);
    unsigned int i = string.size();
    for (S_Digit digit : string)
    {
        i--;
        digit.draw(0.15 * i - 0.15 * string.size()/2, -0.8, 0.1);
        //S_Digit dig;
        //dig.letter = 0b1111111 & 0b1111111;
        //dig.draw(-1 + 0.3 * i, 0, 0.2);
    }
    glEnd();
}