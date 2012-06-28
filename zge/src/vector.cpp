/*
 * vector.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/24/2012
 */
 
#include "zge/vector.h"

#include <cmath>
#include <complex>
#include <cstring>
#include <sstream>

namespace zge {

template <unsigned S>
ZVec<S>::ZVec()
{
    memset(vec, 0, S * sizeof(float));
}

template <unsigned S>
ZVec<S>::ZVec(float arr[])
{
    for (unsigned i = 0; i < S; ++i) {
        vec[i] = arr[i];
    }
}

template <unsigned S>
ZVec<S>::ZVec(const ZVec<S> &copy)
{
    for (unsigned i = 0; i < S; ++i) {
        vec[i] = copy.vec[i];
    }
}

#pragma mark - Operators

template <unsigned S>
float ZVec<S>::operator[](int index)
{
    return vec[index];
}

template <unsigned S>
ZVec<S> ZVec<S>::operator+(const ZVec<S> &other)
{
    ZVec<S> sum;
    for (unsigned i = 0; i < S; ++i) {
        sum.vec[i] = vec[i] + other.vec[i];
    }
    return sum;
}

template <unsigned S>
ZVec<S> ZVec<S>::operator-(const ZVec<S> &other)
{
    ZVec<S> diff;
    for (unsigned i = 0; i < S; ++i) {
        diff.vec[i] = vec[i] - other.vec[i];
    }
    return diff;
}

template <unsigned S>
float ZVec<S>::operator*(const ZVec &other)
{
    float dot;
    for (unsigned i = 0; i < S; ++i) {
        dot += vec[i] * other.vec[i];
    }
    return dot;
}

template <unsigned S>
ZVec<S> ZVec<S>::operator*(float scalar)
{
    ZVec<S> result;
    for (unsigned i = 0; i < S; ++i) {
        result.vec[i] = scalar * vec[i];
    }
    return result;
}

template <unsigned S>
ZVec<S>& ZVec<S>::operator+=(const ZVec<S> &other)
{
    return (*this = (*this + other));
}

template <unsigned S>
ZVec<S>& ZVec<S>::operator-=(const ZVec<S> &other)
{
    return (*this = (*this - other));
}


#pragma mark - Math

template <unsigned S>
float ZVec<S>::length()
{
    float length = 0.0;
    for (unsigned i = 0; i < S; ++i) {
        length += (vec[i] * vec[i]);
    }
    
    return std::sqrt(length);
}

template <unsigned S>
ZVec<S> ZVec<S>::normalize()
{
    float length = this->length();
    if (length == 0.0) {
        return ZVec();
    }
    
    float scale = 1.0 / length;
    float arr[S];
    for (unsigned i = 0; i < S; ++i) {
        arr[i] = vec[i] * scale;
    }
    return ZVec(arr);
}

template <unsigned S>
ZVec<S> ZVec<S>::negate()
{
    ZVec<S> negated;
    for (unsigned i = 0; i < S; ++i) {
        negated.vec[i] = -vec[i];
    }
    return negated;
}

ZVec3 ZVec3::cross(const ZVec3 &other)
{
    return ZVec3(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}


#pragma mark - Description

template <unsigned S>
std::string ZVec<S>::getDescription()
{
    std::ostringstream oss;
    oss << "{ ";
    for (unsigned i = 0; i < S; ++i) {
        oss << vec[i];
        if (i != S - 1) {
            oss << ", ";
        }
    }
    oss << " }";
    return oss.str();
}


// To avoid linker errors
template class ZVec<2>;
template class ZVec<3>;
template class ZVec<4>;
template class ZVec<5>;
template class ZVec<6>;

} // namespace zge
