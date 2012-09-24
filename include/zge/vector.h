/*
 * vector.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/24/2012
 */

#pragma once

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <string>

namespace zge {

template <unsigned S>
class vec_base {
public:
    float array[S];
    
    /** Constructors **/
    vec_base(float arr[] = nullptr);
//    vec_base(std::initializer_list<float> list); // Initializer lists unsupported in clang, arg!!
    vec_base(const vec_base &copy);
    vec_base(vec_base &&move);
    vec_base& operator=(const vec_base &other);
    vec_base& operator=(vec_base &&other);
    
    /** Operators **/
    float operator[](int index);
    vec_base operator+(const vec_base &other);
    vec_base operator-(const vec_base &other);
    float operator*(const vec_base &other);
    vec_base operator*(float scalar);
    
    vec_base& operator+=(const vec_base &other);
    vec_base& operator-=(const vec_base &other);
    
    /** Data **/
    void copy(const vec_base &copy);
    
    /** Math **/
    float length();
    vec_base normalize();
    vec_base negate();
    
    /** Description **/
    std::string get_description();
};

template <unsigned S>
class vec : public vec_base<S> {
public:
    vec(float arr[] = nullptr) : vec_base<S>(arr) {}
    vec(const vec &copy) : vec_base<S>(copy) {}
    vec(vec &&move) : vec_base<S>(move) {}
};

template <>
class vec<2> : public vec_base<2> {
public:
    float &x = this->array[0];
    float &y = this->array[1];
    
    vec<2>(float arr[] = nullptr) : vec_base<2>(arr) {}
    vec<2>(const vec_base &copy) : vec_base<2>(copy) {}
    vec<2>(vec_base &&move) : vec_base<2>(move) {}
    vec<2>& operator=(const vec<2> &other)
    {
        x = this->array[0]; y = this->array[1];
        if (this != &other) {
            copy(other);
        }
        return *this;
    }
    
    vec<2>(float x, float y)
    {
        array[0] = x; array[1] = y;
    }
};
typedef vec<2> vec2;

template <>
class vec<3> : public vec_base<3> {
public:
    float &x = this->array[0];
    float &y = this->array[1];
    float &z = this->array[2];
    
    vec<3>(float arr[] = nullptr) : vec_base(arr) {}
    vec<3>(const vec_base &copy) : vec_base(copy) {}
    vec<3>(vec_base &&move) : vec_base(move) {}
    vec<3>& operator=(const vec<3> &other)
    {
        x = this->array[0]; y = this->array[1]; z = this->array[2];
        if (this != &other) {
            copy(other);
        }
        return *this;
    }
    
    vec<3>(float x, float y, float z = 0.0)
    {
        array[0] = x; array[1] = y; array[2] = z;
    }
    
    /** Math **/
    vec<3> cross(const vec<3> &other);
};
typedef vec<3> vec3;

} // namespace zge
