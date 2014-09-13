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
    
    static ZColor random_color(float alpha = 1.0);
    
    static const ZColor black;
    static const ZColor white;
    static const ZColor clear;
    static const ZColor red;
    static const ZColor green;
    static const ZColor blue;
};

union ZColorb {
    struct { uint8_t r, g, b, a; };
    uint8_t data[4];
};

END_ZGE_NAMESPACE
