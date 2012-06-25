/*
 * geometry.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include <cmath>
#include <cstring>
#include <iostream>
#include <initializer_list>
#include <sstream>
#include <string>

#define DEGREES_TO_RADIANS(x) (x * (M_PI / 180.0))

namespace zge {

#pragma mark - ZVec

template <typename T>
struct ZVec {
    T x, y, z, w;
    
public:
    ZVec() : x(0), y(0), z(0), w(1) {}
    ZVec(T x_, T y_, T z_) :
        x(x_),
        y(y_),
        z(z_),
        w(1) {}
    ZVec(T x_, T y_) :
        x(x_),
        y(y_),
        z(0),
        w(1) {}
    ZVec(T array[4])
    {
        x = array[0];
        y = array[1];
        z = array[2];
        w = array[3];
    }
    
    bool operator==(const ZVec &other)
    {
        return x == other.x
            && y == other.y
            && z == other.z
            && w == other.w;
    }
    
    bool operator!=(const ZVec &other) { return !operator==(other); }
};

typedef ZVec<float> ZVecf;
typedef ZVec<int> ZVeci;


#pragma mark - ZMatrix

template <typename T>
struct ZMatrix {
    T m[16];
    
public:
    ZMatrix()
    {
        memset(m, 0, 16 * sizeof(T));
    }
    
    ZMatrix(const T a[16])
    {
        for (unsigned i = 0; i < 16; ++i) {
            m[i] = a[i];
        }
    }
    
    
    /** Custom Constructors **/
    
    static inline ZMatrix identityMatrix()
    {
        ZMatrix matrix;
        T m_[16] = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        };
        memcpy(matrix.m, m_, 16 * sizeof(T));
        
        return matrix;
    }
    
    static inline ZMatrix<float> perspectiveMatrix(float fovyRadians, float aspect, float nearZ, float farZ)
    {
        float cotan = 1.0f / tanf(fovyRadians / 2.0f);
        
        float m[16] = {
            cotan / aspect, 0.0, 0.0, 0.0,
            0.0, cotan, 0.0, 0.0,
            0.0, 0.0, (farZ + nearZ) / (nearZ - farZ), -1.0f,
            0.0, 0.0, (2.0f * farZ * nearZ) / (nearZ - farZ), 0.0
        };
        
        return ZMatrix<float>(m);
    }
    
    static inline ZMatrix translationMatrix(T tx, T ty, T tz)
    {
        ZMatrix m = identityMatrix();
        m.m[12] = tx;
        m.m[13] = ty;
        m.m[14] = tz;
        
        return m;
    }
    
    static inline ZMatrix scalingMatrix(T sx, T sy, T sz)
    {
        ZMatrix m = identityMatrix();
        m.m[0] = sx;
        m.m[5] = sy;
        m.m[10] = sz;
        
        return m;
    }
    
    
    /** Operators **/
    
    ZMatrix& operator=(const T a[16])
    {
        for (unsigned i = 0; i < 16; ++i) {
            m[i] = a[i];
        }
        return *this;
    }
    
    ZMatrix operator+(const ZMatrix &other)
    {
        ZMatrix result;
        for (unsigned i = 0; i < 16; ++i) {
            result.m[i] = m[i] + other.m[i];
        }
        return result;
    }
    
    ZMatrix& operator+=(const ZMatrix &other)
    {
        *this = (*this + other);
        return (*this);
    }
    
    ZMatrix operator-(const ZMatrix &other)
    {
        ZMatrix result;
        for (unsigned i = 0; i < 16; ++i) {
            result.m[i] = m[i] - other.m[i];
        }
        return result;
    }
    
    ZMatrix& operator-=(const ZMatrix &other)
    {
        *this = (*this - other);
        return (*this);
    }
    
    
    /** Other Methods **/
    
    std::string getDescription()
    {
        std::ostringstream oss;
        for (unsigned i = 0; i < 16; ++i) {
            if (i % 4 == 0) {
                oss << '|';
                if (i != 0) {
                    oss << std::endl << "|\t";
                } else {
                    oss << '\t';
                }
            }
            
            oss << m[i] << '\t';
        }
        
        oss << '|';
        return oss.str();
    }
};
typedef ZMatrix<float> ZMatrixf;
typedef ZMatrix<int> ZMatrixi;


} // namespace zge
