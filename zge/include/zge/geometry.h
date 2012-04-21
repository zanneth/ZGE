/*
 * geometry.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

namespace zge {

template <typename T>
struct ZVec {
public:
    T x, y, z;
    
public:
    ZVec() = default;
    ZVec(T x_, T y_, T z_) :
        x(x_),
        y(y_),
        z(z_) {}
    ZVec(T x_, T y_) :
        x(x_),
        y(y_),
        z(0) {}
    
    bool operator==(const ZVec &other)
    {
        return x == other.x
            && y == other.y
            && z == other.z;
    }
    
    bool operator!=(const ZVec &other) { return !operator==(other); }
};

typedef ZVec<float> ZVecf;
typedef ZVec<int> ZVeci;

} // namespace zge
