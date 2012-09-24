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
            array[i] = arr[i];
        }
    } else {
        memset(array, 0, S * sizeof(float));
    }
}

template <unsigned S>
ZVecBase<S>::ZVecBase(std::initializer_list<float> list)
{
    unsigned c = 0;
    for (float n : list) {
        array[c++] = n;
        if (c >= S) {
            break;
        }
    }
}

template <unsigned S>
ZVecBase<S>::ZVecBase(const ZVecBase<S> &copy)
{
    this->copy(copy);
}

template <unsigned S>
ZVecBase<S>::ZVecBase(ZVecBase<S> &&move)
{
    std::swap(array, move.array);
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
        std::swap(array, other.array);
    }
    
    return *this;
}

#pragma mark - Operators

template <unsigned S>
float ZVecBase<S>::operator[](int index)
{
    return array[index];
}

template <unsigned S>
ZVecBase<S> ZVecBase<S>::operator+(const ZVecBase<S> &other)
{
    ZVecBase<S> sum;
    for (unsigned i = 0; i < S; ++i) {
        sum.array[i] = array[i] + other.array[i];
    }
    return sum;
}

template <unsigned S>
ZVecBase<S> ZVecBase<S>::operator-(const ZVecBase<S> &other)
{
    ZVecBase<S> diff;
    for (unsigned i = 0; i < S; ++i) {
        diff.array[i] = array[i] - other.array[i];
    }
    return diff;
}

template <unsigned S>
float ZVecBase<S>::operator*(const ZVecBase &other)
{
    float dot;
    for (unsigned i = 0; i < S; ++i) {
        dot += array[i] * other.array[i];
    }
    return dot;
}

template <unsigned S>
ZVecBase<S> ZVecBase<S>::operator*(float scalar)
{
    ZVecBase<S> result;
    for (unsigned i = 0; i < S; ++i) {
        result.array[i] = scalar * array[i];
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
        array[i] = copy.array[i];
    }
}


#pragma mark - Math

template <unsigned S>
float ZVecBase<S>::length()
{
    float length = 0.0;
    for (unsigned i = 0; i < S; ++i) {
        length += (array[i] * array[i]);
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
        arr[i] = array[i] * scale;
    }
    return ZVecBase(arr);
}

template <unsigned S>
ZVecBase<S> ZVecBase<S>::negate()
{
    ZVecBase<S> negated;
    for (unsigned i = 0; i < S; ++i) {
        negated.array[i] = -array[i];
    }
    return negated;
}

ZVec<3> ZVec<3>::cross(const ZVec<3> &other)
{
    return {
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    };
}


#pragma mark - Description

template <unsigned S>
std::string ZVecBase<S>::get_description()
{
    std::ostringstream oss;
    oss << "{ ";
    for (unsigned i = 0; i < S; ++i) {
        oss << array[i];
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
