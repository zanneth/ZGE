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
vec_base<S>::vec_base(float arr[])
{
    if (arr != nullptr) {
        for (unsigned i = 0; i < S; ++i) {
            array[i] = arr[i];
        }
    } else {
        memset(array, 0, S * sizeof(float));
    }
}

// Clang doesn't support initializer_lists yet.
#if 0
template <unsigned S>
vec_base<S>::vec_base(std::initializer_list list)
{
    unsigned c = 0;
    for (float n : list) {
        array[c++] = n;
        if (c >= S) {
            break;
        }
    }
}
#endif

template <unsigned S>
vec_base<S>::vec_base(const vec_base<S> &copy)
{
    this->copy(copy);
}

template <unsigned S>
vec_base<S>::vec_base(vec_base<S> &&move)
{
    std::swap(array, move.array);
}

template <unsigned S>
vec_base<S>& vec_base<S>::operator=(const vec_base<S> &other)
{
    if (this != &other) {
        this->copy(other);
    }
    
    return *this;
}

template <unsigned S>
vec_base<S>& vec_base<S>::operator=(vec_base<S> &&other)
{
    if (this != &other) {
        std::swap(array, other.array);
    }
    
    return *this;
}

#pragma mark - Operators

template <unsigned S>
float vec_base<S>::operator[](int index)
{
    return array[index];
}

template <unsigned S>
vec_base<S> vec_base<S>::operator+(const vec_base<S> &other)
{
    vec_base<S> sum;
    for (unsigned i = 0; i < S; ++i) {
        sum.array[i] = array[i] + other.array[i];
    }
    return sum;
}

template <unsigned S>
vec_base<S> vec_base<S>::operator-(const vec_base<S> &other)
{
    vec_base<S> diff;
    for (unsigned i = 0; i < S; ++i) {
        diff.array[i] = array[i] - other.array[i];
    }
    return diff;
}

template <unsigned S>
float vec_base<S>::operator*(const vec_base &other)
{
    float dot;
    for (unsigned i = 0; i < S; ++i) {
        dot += array[i] * other.array[i];
    }
    return dot;
}

template <unsigned S>
vec_base<S> vec_base<S>::operator*(float scalar)
{
    vec_base<S> result;
    for (unsigned i = 0; i < S; ++i) {
        result.array[i] = scalar * array[i];
    }
    return result;
}

template <unsigned S>
vec_base<S>& vec_base<S>::operator+=(const vec_base<S> &other)
{
    return (*this = (*this + other));
}

template <unsigned S>
vec_base<S>& vec_base<S>::operator-=(const vec_base<S> &other)
{
    return (*this = (*this - other));
}


#pragma mark - Data

template <unsigned S>
void vec_base<S>::copy(const vec_base<S> &copy)
{
    for (unsigned i = 0; i < S; ++i) {
        array[i] = copy.array[i];
    }
}


#pragma mark - Math

template <unsigned S>
float vec_base<S>::length()
{
    float length = 0.0;
    for (unsigned i = 0; i < S; ++i) {
        length += (array[i] * array[i]);
    }
    
    return std::sqrt(length);
}

template <unsigned S>
vec_base<S> vec_base<S>::normalize()
{
    float length = this->length();
    if (length == 0.0) {
        return vec_base();
    }
    
    float scale = 1.0 / length;
    float arr[S];
    for (unsigned i = 0; i < S; ++i) {
        arr[i] = array[i] * scale;
    }
    return vec_base(arr);
}

template <unsigned S>
vec_base<S> vec_base<S>::negate()
{
    vec_base<S> negated;
    for (unsigned i = 0; i < S; ++i) {
        negated.array[i] = -array[i];
    }
    return negated;
}

vec<3> vec<3>::cross(const vec<3> &other)
{
    return vec<3>(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}


#pragma mark - Description

template <unsigned S>
std::string vec_base<S>::get_description()
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
template class vec_base<2>;
template class vec_base<3>;
template class vec_base<4>;
template class vec_base<5>;
template class vec_base<6>;

} // namespace zge
