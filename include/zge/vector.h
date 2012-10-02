/*
 * vector.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/24/2012
 */

#pragma once

#include <algorithm>
#include <initializer_list>

namespace zge {

template <unsigned S>
class ZVecBase {
public:
    float array[S];
    
    /** Constructors **/
    ZVecBase(float arr[] = nullptr);
    ZVecBase(std::initializer_list<float> list); // Initializer lists unsupported in clang, arg!!
    ZVecBase(const ZVecBase &copy);
    ZVecBase(ZVecBase &&move);
    ZVecBase& operator=(const ZVecBase &other);
    ZVecBase& operator=(ZVecBase &&other);
    
    /** Operators **/
    float operator[](int index);
    ZVecBase operator+(const ZVecBase &other);
    ZVecBase operator-(const ZVecBase &other);
    float operator*(const ZVecBase &other);
    ZVecBase operator*(float scalar);
    
    ZVecBase& operator+=(const ZVecBase &other);
    ZVecBase& operator-=(const ZVecBase &other);
    
    /** Data **/
    void copy(const ZVecBase &copy);
    
    /** Math **/
    float length();
    ZVecBase normalize();
    ZVecBase negate();
    
    /** Description **/
    std::string get_description();
};

template <unsigned S>
class ZVec : public ZVecBase<S> {
public:
    ZVec(float arr[] = nullptr) : ZVecBase<S>(arr) {}
    ZVec(const ZVec &copy) : ZVecBase<S>(copy) {}
    ZVec(ZVec &&move) : ZVecBase<S>(move) {}
};

template <>
class ZVec<2> : public ZVecBase<2> {
public:
    float &x = this->array[0];
    float &y = this->array[1];
    
    ZVec<2>(float arr[] = nullptr) : ZVecBase<2>(arr) {}
    ZVec<2>(const ZVecBase &copy) : ZVecBase<2>(copy) {}
    ZVec<2>(ZVecBase &&move) : ZVecBase<2>(move) {}
    ZVec<2>& operator=(const ZVec<2> &other)
    {
        x = this->array[0]; y = this->array[1];
        if (this != &other) {
            copy(other);
        }
        return *this;
    }
    
    ZVec<2>(float x, float y)
    {
        array[0] = x; array[1] = y;
    }
};
typedef ZVec<2> ZVec2;

template <>
class ZVec<3> : public ZVecBase<3> {
public:
    float &x = this->array[0];
    float &y = this->array[1];
    float &z = this->array[2];
    
    ZVec<3>(float arr[] = nullptr) : ZVecBase(arr) {}
    ZVec<3>(const ZVecBase &copy) : ZVecBase(copy) {}
    ZVec<3>(ZVecBase &&move) : ZVecBase(move) {}
    ZVec<3>& operator=(const ZVec<3> &other)
    {
        x = this->array[0]; y = this->array[1]; z = this->array[2];
        if (this != &other) {
            copy(other);
        }
        return *this;
    }
    
    ZVec<3>(float x, float y, float z = 0.0)
    {
        array[0] = x; array[1] = y; array[2] = z;
    }
    
    /** Math **/
    ZVec<3> cross(const ZVec<3> &other);
};
typedef ZVec<3> ZVec3;

} // namespace zge
