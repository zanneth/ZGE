/*
 * color.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 08/17/2013
 */

#include <zge/color.h>

ZGE_BEGIN_NAMESPACE

const ZColor ZColor::black = ZColor(0.0, 0.0, 0.0, 1.0);
const ZColor ZColor::white = ZColor(1.0, 1.0, 1.0, 1.0);
const ZColor ZColor::clear = ZColor(0.0, 0.0, 0.0, 0.0);
const ZColor ZColor::red = ZColor(1.0, 0.0, 0.0, 1.0);
const ZColor ZColor::green = ZColor(0.0, 1.0, 0.0, 1.0);
const ZColor ZColor::blue = ZColor(0.0, 0.0, 1.0, 1.0);

ZColor::ZColor(float r, float g, float b, float a) :
    r(r),
    g(g),
    b(b),
    a(a)
{}

ZColor::ZColor(const ZColor &cp, float alpha) :
    r(cp.r),
    g(cp.g),
    b(cp.b),
    a(alpha)
{}

ZColor ZColor::random_color(float alpha)
{
    ZColor color;
    color.r = (float)arc4random() / (float)UINT32_MAX;
    color.g = (float)arc4random() / (float)UINT32_MAX;
    color.b = (float)arc4random() / (float)UINT32_MAX;
    color.a = alpha;
    return color;
}

ZGE_END_NAMESPACE
