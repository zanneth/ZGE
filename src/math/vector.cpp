/*
 * vector.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 12/19/2013
 */

#include <zge/vector.h>
#include <zge/vector_private.h>
#include <zge/logger.h>

BEGIN_ZGE_NAMESPACE

ZVector::ZVector(std::initializer_list<float> list) :
    _impl(new ZVectorImpl)
{
    unsigned idx = 0;
    for (float f : list) {
        _impl->data[idx++] = f;
        if (idx >= 3) {
            break;
        }
    }
}

ZVector::ZVector(const ZVector &cp) :
    _impl(new ZVectorImpl{cp._impl->data})
{}

ZVector::ZVector(ZVector &&mv) :
    _impl(mv._impl.release())
{}

ZVector::~ZVector()
{}

#pragma mark - Accessors

float& ZVector::x()
{
    return _impl->data.x();
}

float ZVector::get_x() const
{
    return _impl->data.x();
}

float& ZVector::y()
{
    return _impl->data.y();
}

float ZVector::get_y() const
{
    return _impl->data.y();
}

float& ZVector::z()
{
    return _impl->data.z();
}

float ZVector::get_z() const
{
    return _impl->data.z();
}

#pragma mark - Operators

ZVector& ZVector::operator=(const ZVector &rhs)
{
    if (this != &rhs) {
        _impl->data = rhs._impl->data;
    }
    return *this;
}

float& ZVector::operator[](unsigned idx)
{
    return _impl->data[idx];
}

bool ZVector::operator==(const ZVector &other) const
{
    return (_impl->data == other._impl->data);
}

bool ZVector::operator!=(const ZVector &other) const
{
    return (_impl->data != other._impl->data);
}

ZVector ZVector::operator*(const float scalar) const
{
    ZVector v;
    v._impl->data = (_impl->data * scalar);
    return v;
}

ZVector ZVector::operator*(const ZVector &other) const
{
    ZVector v;
    v._impl->data = _impl->data.cross(other._impl->data);
    return v;
}

ZVector ZVector::operator+(const ZVector &other) const
{
    ZVector v;
    v._impl->data = (_impl->data + other._impl->data);
    return v;
}

ZVector& ZVector::operator+=(const ZVector &other)
{
    _impl->data += other._impl->data;
    return *this;
}

ZVector ZVector::operator-(const ZVector &other) const
{
    ZVector v;
    v._impl->data = (_impl->data - other._impl->data);
    return v;
}

ZVector& ZVector::operator-=(const ZVector &other)
{
    _impl->data -= other._impl->data;
    return *this;
}

ZVector ZVector::operator/(const float scalar) const
{
    ZVector v;
    v._impl->data = (_impl->data / scalar);
    return v;
}

ZVector ZVector::operator-() const
{
    ZVector v;
    v._impl->data = -(_impl->data);
    return v;
}

#pragma mark - API

ZVector ZVector::unit_x()
{
    return { 1.0, 0.0, 0.0 };
}

ZVector ZVector::unit_y()
{
    return { 0.0, 1.0, 0.0 };
}

ZVector ZVector::unit_z()
{
    return { 0.0, 0.0, 1.0 };
}

float ZVector::dot(const ZVector &other) const
{
    return _impl->data.dot(other._impl->data);
}

ZVector ZVector::cross(const ZVector &other) const
{
    ZVector v;
    v._impl->data = _impl->data.cross(other._impl->data);
    return v;
}

ZVector ZVector::normalized() const
{
    ZVector v;
    v._impl->data = _impl->data.normalized();
    return v;
}

END_ZGE_NAMESPACE
