/*
 * vector.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/24/2012
 */
 
#include "zge/vector.h"

namespace zge {

ZVec2::ZVec2() :
    ZVec2(0.0, 0.0)
{}

ZVec2::ZVec2(float x_, float y_) :
    x(x_),
    y(y_)
{}


#pragma mark - Operators

float ZVec2::operator[](int index) const
{
    return (&x)[index];
}

ZVec2 ZVec2::operator-() const
{
    return ZVec2(-x, -y);
}

ZVec2 ZVec2::operator*(float a) const
{
    return ZVec2(x * a, y * a);
}

}
