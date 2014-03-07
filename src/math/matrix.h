/*
 * matrix.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 12/17/2013
 */

#pragma once

#include <initializer_list>
#include <memory>
#include <string>
#include <zge/defines.h>
#include <zge/vector.h>

BEGIN_ZGE_NAMESPACE

class ZMatrix {
    std::auto_ptr<struct ZMatrixImpl> _impl;

public:
    ZMatrix(std::initializer_list<float> list = {});
    ZMatrix(const ZMatrix&);
    ZMatrix(ZMatrix&&);
    ~ZMatrix();
    
    /// creates a new identity matrix.
    static ZMatrix identity();
    
    /// creates a transform matrix for a translation.
    static ZMatrix translation(float tx, float ty, float tz);
    
    /// creates a transform matrix for a scale.
    static ZMatrix scaling(float sx, float sy, float sz);
    
    /// creates a transform matrix for an angle-axis rotation.
    static ZMatrix rotation(float radians, float x, float y, float z);
    
    /// creates a frustum transformation matrix.
    static ZMatrix frustum(float left, float right, float bottom, float top, float nearZ, float farZ);
    
    /// creates a perspective matrix.
    static ZMatrix perspective(float fovy, float aspect, float nearZ, float farZ);
    
    /// creates a look-at transformation matrix.
    static ZMatrix lookat(const ZVector &eye, const ZVector &center, const ZVector &up);
    
    /// creates an orthogonal transformation matrix.
    static ZMatrix ortho(float left, float right, float bottom, float top, float nearZ, float farZ);
    
    // operators
    ZMatrix& operator=(const ZMatrix &rhs);
    float&   operator[](unsigned idx);
    bool     operator==(const ZMatrix &other) const;
    bool     operator!=(const ZMatrix &other) const;
    ZMatrix  operator*(const float scalar) const;
    ZMatrix  operator*(const ZMatrix &other) const;
    ZVector  operator*(const ZVector &vector) const;
    ZMatrix& operator*=(const ZMatrix &other);
    ZMatrix  operator+(const ZMatrix &other) const;
    ZMatrix& operator+=(const ZMatrix &other);
    ZMatrix  operator-(const ZMatrix &other) const;
    ZMatrix& operator-=(const ZMatrix &other);
    ZMatrix  operator-() const;
    ZMatrix  operator/(const float scalar) const;
    
    /// returns a pointer to the internal data for this matrix.
    const float* get_data() const;
    
    /// returns transpose of this matrix.
    ZMatrix transpose() const;
    
    /// returns the matrix concatenated with a translation transform.
    ZMatrix translate(float tx, float ty, float tz);
    ZMatrix translate(const ZVector &tv);
    
    /// returns the matrix concatenated with a scaling transform.
    ZMatrix scale(float sx, float sy, float sz);
    
    /// returns the matrix concatenated with a rotation transform.
    ZMatrix rotate(float radians, float x, float y, float z);
    
    /// returns the determinant of this matrix.
    float determinant() const;
    
    /// string representation of this matrix.
    std::string get_description() const;
};

END_ZGE_NAMESPACE
