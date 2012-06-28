/*
 * vector.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/24/2012
 */
 
#pragma once

namespace zge {

class ZVec2 {
public:
    float x;
    float y;
    
    /** Constructors **/
    ZVec2();
    ZVec2(const ZVec2&) = default;
    ZVec2(float x, float y);
    
    /** Operators **/
    float operator[](int index) const;
    ZVec2 operator-() const;
    ZVec2 operator*(float a) const;
    float operator*(const ZVec2 &a) const;
};

}
