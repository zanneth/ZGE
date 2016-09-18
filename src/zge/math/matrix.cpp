/*
 * matrix.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 12/17/2013
 */

#include <zge/math/matrix.h>
#include <zge/math/vector.h>
#include <zge/math/vector_private.h>
#include <Eigen/Eigen>
#include <ostream>

ZGE_BEGIN_NAMESPACE

struct ZMatrixImpl {
    Eigen::Matrix4f data;
};

#pragma mark -

ZMatrix::ZMatrix(std::initializer_list<float> list) :
    _impl(new ZMatrixImpl)
{
    unsigned idx = 0;
    size_t list_size = list.size();
    for (float f : list) {
        _impl->data(idx++) = f;
        if (idx >= list_size) {
            break;
        }
    }
}

ZMatrix::ZMatrix(const ZMatrix &cp) :
    _impl(new ZMatrixImpl)
{
    _impl->data = cp._impl->data;
}

ZMatrix::ZMatrix(ZMatrix &&mv) :
    _impl(mv._impl.release())
{}

ZMatrix::~ZMatrix()
{}

#pragma mark - Operators

ZMatrix& ZMatrix::operator=(const ZMatrix &rhs)
{
    if (this == &rhs) {
        return *this;
    }
    _impl->data = rhs._impl->data;
    return *this;
}

float& ZMatrix::operator[](unsigned idx)
{
    return _impl->data(idx);
}

bool ZMatrix::operator==(const ZMatrix &other) const
{
    return (_impl->data == other._impl->data);
}

bool ZMatrix::operator!=(const ZMatrix &other) const
{
    return (_impl->data != other._impl->data);
}

ZMatrix ZMatrix::operator*(const float scalar) const
{
    ZMatrix result;
    result._impl->data = (_impl->data * scalar);
    return result;
}

ZMatrix ZMatrix::operator*(const ZMatrix &other) const
{
    ZMatrix result;
    result._impl->data = (_impl->data * other._impl->data);
    return result;
}

ZVector ZMatrix::operator*(const ZVector &vector) const
{
    ZVector v;
    Eigen::Affine3f transform(_impl->data);
    v._impl->data = (transform * vector._impl->data);
    return v;
}

ZMatrix& ZMatrix::operator*=(const ZMatrix &other)
{
    _impl->data *= other._impl->data;
    return *this;
}

ZMatrix ZMatrix::operator+(const ZMatrix &other) const
{
    ZMatrix result;
    result._impl->data = (_impl->data + other._impl->data);
    return result;
}

ZMatrix& ZMatrix::operator+=(const ZMatrix &other)
{
    _impl->data += other._impl->data;
    return *this;
}

ZMatrix ZMatrix::operator-(const ZMatrix &other) const
{
    ZMatrix result;
    result._impl->data = (_impl->data - other._impl->data);
    return result;
}

ZMatrix& ZMatrix::operator-=(const ZMatrix &other)
{
    _impl->data -= other._impl->data;
    return *this;
}

ZMatrix ZMatrix::operator-() const
{
    ZMatrix result;
    result._impl->data = -(_impl->data);
    return result;
}

ZMatrix ZMatrix::operator/(const float scalar) const
{
    ZMatrix result;
    result._impl->data = (_impl->data / scalar);
    return result;
}

#pragma mark - API

ZMatrix ZMatrix::identity()
{
    static ZMatrix __identity;
    static std::once_flag __once;
    std::call_once(__once, [] {
        __identity._impl->data = Eigen::Matrix4f::Identity();
    });
    return __identity;
}

ZMatrix ZMatrix::translation(float tx, float ty, float tz)
{
    ZMatrix m = ZMatrix::identity();
    m[12] = tx;
    m[13] = ty;
    m[14] = tz;
    return m;
}

ZMatrix ZMatrix::scaling(float sx, float sy, float sz)
{
    ZMatrix m = ZMatrix::identity();
    m[0] = sx;
    m[5] = sy;
    m[10] = sz;
    return m;
}

ZMatrix ZMatrix::rotation(float radians, float x, float y, float z)
{
    ZVector v = ZVector({ x, y, z }).normalized();
    float cos = cosf(radians);
    float cosp = 1.0f - cos;
    float sin = sinf(radians);
    
    ZMatrix m = {
        cos + cosp * v[0] * v[0],
        cosp * v[0] * v[1] + v[2] * sin,
        cosp * v[0] * v[2] - v[1] * sin,
        0.0f,
        cosp * v[0] * v[1] - v[2] * sin,
        cos + cosp * v[1] * v[1],
        cosp * v[1] * v[2] + v[0] * sin,
        0.0f,
        cosp * v[0] * v[2] + v[1] * sin,
        cosp * v[1] * v[2] - v[0] * sin,
        cos + cosp * v[2] * v[2],
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        1.0f
    };
    
    return m;
}

ZMatrix ZMatrix::frustum(float left, float right, float bottom, float top, float nearZ, float farZ)
{
    float ral = right + left;
    float rsl = right - left;
    float tsb = top - bottom;
    float tab = top + bottom;
    float fan = farZ + nearZ;
    float fsn = farZ - nearZ;
    
    ZMatrix mat = {
        2.0f * nearZ / rsl, 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f * nearZ / tsb, 0.0f, 0.0f,
        ral / rsl, tab / tsb, -fan / fsn, -1.0f,
        0.0f, 0.0f, (-2.0f * farZ * nearZ) / fsn, 0.0f
    };
    return mat;
}

ZMatrix ZMatrix::perspective(float fovy, float aspect, float nearZ, float farZ)
{
    float fheight = std::tan(fovy / 360.0 * M_PI) * nearZ;
    float fwidth  = fheight * aspect;
    
    return frustum(-fwidth, fwidth, -fheight, fheight, nearZ, farZ);
}

ZMatrix ZMatrix::lookat(const ZVector &eye, const ZVector &center, const ZVector &up)
{
    ZVector n = (eye + -center).normalized();
    ZVector u = (up.cross(n)).normalized();
    ZVector v = n.cross(u);
    
    ZMatrix mat = {
        u[0], v[0], n[0], 0.0f,
        u[1], v[1], n[1], 0.0f,
        u[2], v[2], n[2], 0.0f,
        -u.dot(eye), -v.dot(eye), -n.dot(eye), 1.0f
    };
    return mat;
}

ZMatrix ZMatrix::ortho(float left, float right, float bottom, float top, float nearZ, float farZ)
{
    float ral = right + left;
    float rsl = right - left;
    float tab = top + bottom;
    float tsb = top - bottom;
    float fan = farZ + nearZ;
    float fsn = farZ - nearZ;
    
    ZMatrix mat = {
        2.0f / rsl, 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f / tsb, 0.0f, 0.0f,
        0.0f, 0.0f, -2.0f / fsn, 0.0f,
        -ral / rsl, -tab / tsb, -fan / fsn, 1.0f
    };
    return mat;
}

const float* ZMatrix::get_data() const
{
    return _impl->data.data();
}
    
ZMatrix ZMatrix::transpose() const
{
    ZMatrix transpose;
    transpose._impl->data = _impl->data.transpose();
    return transpose;
}

ZMatrix ZMatrix::translate(float tx, float ty, float tz)
{
    return (*this * ZMatrix::translation(tx, ty, tz));
}
    
ZMatrix ZMatrix::translate(const ZVector &tv)
{
    return (*this * ZMatrix::translation(tv.get_x(), tv.get_y(), tv.get_z()));
}

ZMatrix ZMatrix::scale(float sx, float sy, float sz)
{
    return (*this * ZMatrix::scaling(sx, sy, sz));
}

ZMatrix ZMatrix::rotate(float radians, float x, float y, float z)
{
    return (*this * ZMatrix::rotation(radians, x, y, z));
}

float ZMatrix::determinant() const
{
    return _impl->data.determinant();
}

std::string ZMatrix::get_description() const
{
    Eigen::IOFormat format(Eigen::StreamPrecision, Eigen::DontAlignCols, ", ", ",", "", "", "{", "}");
    std::ostringstream stream;
    stream << _impl->data.format(format);
    return stream.str();
}

ZGE_END_NAMESPACE
