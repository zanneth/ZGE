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
ZVecBase<S>::ZVecBase(float arr[])
{
    if (arr != nullptr) {
        for (unsigned i = 0; i < S; ++i) {
            vec[i] = arr[i];
        }
    } else {
        memset(vec, 0, S * sizeof(float));
    }
}

// Clang doesn't support initializer_lists yet.
#if 0
template <unsigned S>
ZVecBase<S>::ZVecBase(std::initializer_list list)
{
    unsigned c = 0;
    for (float n : list) {
        vec[c++] = n;
        if (c >= S) {
            break;
        }
    }
}
#endif

template <unsigned S>
ZVecBase<S>::ZVecBase(const ZVecBase<S> &copy)
{
    this->copy(copy);
}

template <unsigned S>
ZVecBase<S>::ZVecBase(ZVecBase<S> &&move)
{
    std::swap(vec, move.vec);
}

template <unsigned S>
ZVecBase<S>& ZVecBase<S>::operator=(const ZVecBase<S> &other)
{
    if (this != &other) {
        this->copy(other);
    }
    
    return *this;
}

template <unsigned S>
ZVecBase<S>& ZVecBase<S>::operator=(ZVecBase<S> &&other)
{
    if (this != &other) {
        std::swap(vec, other.vec);
    }
    
    return *this;
}

#pragma mark - Operators

template <unsigned S>
float ZVecBase<S>::operator[](int index)
{
    return vec[index];
}

template <unsigned S>
ZVecBase<S> ZVecBase<S>::operator+(const ZVecBase<S> &other)
{
    ZVecBase<S> sum;
    for (unsigned i = 0; i < S; ++i) {
        sum.vec[i] = vec[i] + other.vec[i];
    }
    return sum;
}

template <unsigned S>
ZVecBase<S> ZVecBase<S>::operator-(const ZVecBase<S> &other)
{
    ZVecBase<S> diff;
    for (unsigned i = 0; i < S; ++i) {
        diff.vec[i] = vec[i] - other.vec[i];
    }
    return diff;
}

template <unsigned S>
float ZVecBase<S>::operator*(const ZVecBase &other)
{
    float dot;
    for (unsigned i = 0; i < S; ++i) {
        dot += vec[i] * other.vec[i];
    }
    return dot;
}

template <unsigned S>
ZVecBase<S> ZVecBase<S>::operator*(float scalar)
{
    ZVecBase<S> result;
    for (unsigned i = 0; i < S; ++i) {
        result.vec[i] = scalar * vec[i];
    }
    return result;
}

template <unsigned S>
ZVecBase<S>& ZVecBase<S>::operator+=(const ZVecBase<S> &other)
{
    return (*this = (*this + other));
}

template <unsigned S>
ZVecBase<S>& ZVecBase<S>::operator-=(const ZVecBase<S> &other)
{
    return (*this = (*this - other));
}


#pragma mark - Data

template <unsigned S>
void ZVecBase<S>::copy(const ZVecBase<S> &copy)
{
    for (unsigned i = 0; i < S; ++i) {
        vec[i] = copy.vec[i];
    }
}


#pragma mark - Math

template <unsigned S>
float ZVecBase<S>::length()
{
    float length = 0.0;
    for (unsigned i = 0; i < S; ++i) {
        length += (vec[i] * vec[i]);
    }
    
    return std::sqrt(length);
}

template <unsigned S>
ZVecBase<S> ZVecBase<S>::normalize()
{
    float length = this->length();
    if (length == 0.0) {
        return ZVecBase();
    }
    
    float scale = 1.0 / length;
    float arr[S];
    for (unsigned i = 0; i < S; ++i) {
        arr[i] = vec[i] * scale;
    }
    return ZVecBase(arr);
}

template <unsigned S>
ZVecBase<S> ZVecBase<S>::negate()
{
    ZVecBase<S> negated;
    for (unsigned i = 0; i < S; ++i) {
        negated.vec[i] = -vec[i];
    }
    return negated;
}

ZVec<3> ZVec<3>::cross(const ZVec<3> &other)
{
    return ZVec<3>(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}


#pragma mark - Description

template <unsigned S>
std::string ZVecBase<S>::getDescription()
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
template class ZVecBase<2>;
template class ZVecBase<3>;
template class ZVecBase<4>;
template class ZVecBase<5>;
template class ZVecBase<6>;

} // namespace zge
