/*
 * color.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 08/17/2013
 */

#pragma once

#include <zge/defines.h>

BEGIN_ZGE_NAMESPACE

union ZColor {
    struct { float r, g, b, a; };
    float data[4];
    
    ZColor(float r = 0.0, float g = 0.0, float b = 0.0, float a = 0.0);
};

extern ZColor ZBlackColor;
extern ZColor ZWhiteColor;
extern ZColor ZClearColor;
extern ZColor ZRedColor;
extern ZColor ZGreenColor;
extern ZColor ZBlueColor;

extern ZColor ZColorRandom(float alpha);

END_ZGE_NAMESPACE
