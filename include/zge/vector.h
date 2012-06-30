/*
 * vector.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/24/2012
 */

#pragma once

#include <initializer_list>
#include <string>

namespace zge {

template <unsigned S>
class ZVec {
public:
    float vec[S];
    
    /** Constructors **/
    explicit ZVec(float arr[] = nullptr);
    // ZVec(std::initializer_list<float> list); // Initializer lists unsupported in clang, arg!!
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
    float &x = this->vec[0];
    float &y = this->vec[1];
    
    using ZVec<2>::ZVec;
};

class ZVec3 : public ZVec<3> {
public:
    float &x = this->vec[0];
    float &y = this->vec[1];
    float &z = this->vec[2];
    
    // FIXME: These constructors are here so that I can initialize a 3D vector
    // in one line without initializer_lists. As of writing this, clang++ doesn't
    // support initializer_lists but this should be updated once it does.
    // using ZVec<3>::ZVec;
    ZVec3(float arr[] = nullptr) : ZVec(arr) {}
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
