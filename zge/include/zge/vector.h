/*
 * vector.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/24/2012
 */
 
#pragma once

#include <string>

namespace zge {

template <unsigned S>
class ZVec {
public:
    float vec[S];
    
    /** Constructors **/
    ZVec();
    ZVec(float arr[]);
    ZVec(const ZVec &copy);
    
    /** Operators **/
    float operator[](int index);
    ZVec operator+(const ZVec &other);
    ZVec operator-(const ZVec &other);
    float operator*(const ZVec &other);
    ZVec operator*(float scalar);
    
    ZVec& operator+=(const ZVec &other);
    ZVec& operator-=(const ZVec &other);
    
    /** Math **/
    float length();
    ZVec normalize();
    ZVec negate();
    
    /** Description **/
    std::string getDescription();
};

class ZVec2 : public ZVec<2> {
public:
    float &x = vec[0];
    float &y = vec[1];
    
    // FIXME: Inheriting constructors not supported in gcc at the time of writing
    // this code. Replace with inheriting syntax once support is added.
    ZVec2() : ZVec() {}
    ZVec2(float arr[]) : ZVec(arr) {}
    ZVec2(const ZVec &copy) : ZVec(copy) {}
    
    ZVec2(float x, float y)
    {
        vec[0] = x;
        vec[1] = y;
    }
};

class ZVec3 : public ZVec<3> {
public:
    float &x = vec[0];
    float &y = vec[1];
    float &z = vec[2];
    
    // FIXME: Inheriting constructors not supported in gcc at the time of writing
    // this code. Replace with inheriting syntax once support is added.
    ZVec3() : ZVec() {}
    ZVec3(float arr[]) : ZVec(arr) {}
    ZVec3(const ZVec &copy) : ZVec(copy) {}
    
    ZVec3(float x, float y, float z = 0.0)
    {
        vec[0] = x;
        vec[1] = y;
        vec[2] = z;
    }
    
    /** Math **/
    ZVec3 cross(const ZVec3 &other);
};

} // namespace zge
