/*
 * vector.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 12/19/2013
 */

#pragma once

#include <initializer_list>
#include <memory>
#include <zge/defines.h>

BEGIN_ZGE_NAMESPACE

class ZVector {
private:
    std::auto_ptr<struct ZVectorImpl> _impl;
    
public:
    ZVector(std::initializer_list<float> list = {});
    ZVector(const ZVector&);
    ZVector(ZVector&&);
    ~ZVector();
    
    /// creates a new unit vector on the X axis.
    static ZVector unit_x();
    
    /// creates a new unit vector on the Y axis.
    static ZVector unit_y();
    
    /// creates a new unit vector on the Z axis.
    static ZVector unit_z();
    
    /// the zero vector
    static const ZVector zero;
    
    // accessors
    float& x();
    float get_x() const;
    float& y();
    float get_y() const;
    float& z();
    float get_z() const;
    
    /// returns a pointer to the internal data for this vector.
    const float* get_data() const;
    
    // operators
    ZVector& operator=(const ZVector &rhs);
    float&   operator[](unsigned idx);
    bool     operator==(const ZVector &other) const;
    bool     operator!=(const ZVector &other) const;
    ZVector  operator*(const float scalar) const;
    ZVector  operator*(const ZVector &other) const; // cross product
    ZVector  operator+(const ZVector &other) const;
    ZVector& operator+=(const ZVector &other);
    ZVector  operator-(const ZVector &other) const;
    ZVector& operator-=(const ZVector &other);
    ZVector  operator/(const float scalar) const;
    ZVector  operator-() const;
    
    /// returns dot product of two vectors.
    float dot(const ZVector &other) const;
    
    /// returns the cross product of two vectors.
    ZVector cross(const ZVector &other) const;
    
    /// returns a normalized version of the vector.
    ZVector normalized() const;
    
    friend class ZMatrix;
};

END_ZGE_NAMESPACE
