/*
 * color.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 08/17/2013
 */

#include <zge/color.h>

namespace zge {

ZColor::ZColor(float r, float g, float b, float a) :
    r(r),
    g(g),
    b(b),
    a(a)
{}

ZColor ZBlackColor = ZColor(0.0, 0.0, 0.0, 1.0);
ZColor ZWhiteColor = ZColor(1.0, 1.0, 1.0, 1.0);
ZColor ZClearColor = ZColor(0.0, 0.0, 0.0, 0.0);
ZColor ZRedColor   = ZColor(1.0, 0.0, 0.0, 1.0);
ZColor ZGreenColor = ZColor(0.0, 1.0, 0.0, 1.0);
ZColor ZBlueColor  = ZColor(0.0, 0.0, 1.0, 1.0);

} // namespace zge
