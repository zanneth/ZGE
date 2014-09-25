/*
 * data.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 03/02/2014
 */

#include <zge/data.h>
#include <algorithm>

#define REALLOC_EXTRA 256

BEGIN_ZGE_NAMESPACE

#pragma mark - ZData

ZData::ZData(const void *data, size_t length) :
    _length(length),
    _data(length > 0 ? new uint8_t[length] : nullptr)
{
    if (data != nullptr) {
        memcpy(_data.get(), data, length);
    } else {
        memset(_data.get(), 0, length);
    }
}

ZData::ZData(const ZData &cp) : ZData(cp._data.get(), cp._length)
{}

ZData::ZData(ZData &&mv)
{
    _move(std::move(mv));
}

ZData& ZData::operator=(const ZData &cp)
{
    if (this != &cp) {
        memcpy(_data.get(), cp._data.get(), cp._length);
    }
    return *this;
}

ZData& ZData::operator=(ZData &&mv)
{
    if (this != &mv) {
        _move(std::move(mv));
    }
    return *this;
}

const void* ZData::get_data() const
{
    return _data.get();
}

size_t ZData::get_length() const
{
    return _length;
}

void ZData::_move(ZData &&mv)
{
    // auto_ptr transfers ownership
    _data = mv._data;
    
    _length = mv._length;
    mv._length = 0;
}

#pragma mark - ZMutableData

ZMutableData::ZMutableData(const void *data, size_t length) : ZData(data, length),
    _capacity(length)
{}

ZMutableData::ZMutableData(const ZData &cp) : ZData(cp),
    _capacity(cp.get_length())
{}

ZMutableData::ZMutableData(ZData &&mv) : ZData(mv),
    _capacity(mv.get_length())
{}

ZMutableData& ZMutableData::operator=(const ZData &cp)
{
    if (this != &cp) {
        ZData::operator=(cp);
        _capacity = cp.get_length();
    }
    return *this;
}

ZMutableData& ZMutableData::operator=(ZData &&mv)
{
    if (this != &mv) {
        ZData::operator=(std::move(mv));
        _capacity = mv.get_length();
    }
    return *this;
}

void ZMutableData::set_data(const void *data, size_t length)
{
    clear_data();
    append_data(data, length);
}

void ZMutableData::append_data(const void *data, size_t length)
{
    if (_capacity < _length + length) {
        _realloc_data(_length + length + REALLOC_EXTRA);
    }
    
    memcpy(_data.get() + _length, data, length);
    _length += length;
}

void ZMutableData::clear_data()
{
    _length = 0;
}

void ZMutableData::_realloc_data(size_t new_size)
{
    uint8_t *new_data = new uint8_t[new_size];
    uint8_t *current_data = _data.get();
    if (current_data != nullptr) {
        memcpy(new_data, current_data, std::min(_length, new_size));
    }
    
    _data = std::auto_ptr<uint8_t>(new_data);
    _capacity = new_size;
}

END_ZGE_NAMESPACE
