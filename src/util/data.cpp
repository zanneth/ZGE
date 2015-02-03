/*
 * data.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 03/02/2014
 */

#include <zge/data.h>
#include <algorithm>

#define REALLOC_EXTRA 256

ZGE_BEGIN_NAMESPACE

#pragma mark - ZData

ZData::ZData(const void *data, size_t length) :
    _length(length),
    _capacity(length),
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

uint8_t& ZData::operator[](unsigned long off)
{
    return *(_data.get() + off);
}

uint8_t ZData::operator[](unsigned long off) const
{
    return _data.get()[off];
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

void ZData::set_data(const void *data, size_t length)
{
    clear_data();
    append_data(data, length);
}

void ZData::append_data(const void *data, size_t length)
{
    if (_capacity < _length + length) {
        _realloc_data(_length + length + REALLOC_EXTRA);
    }
    
    memcpy(_data.get() + _length, data, length);
    _length += length;
}

void ZData::clear_data()
{
    _length = 0;
}

std::string ZData::get_class_name() const
{
    return "ZData";
}

std::vector<std::string> ZData::get_description_attributes() const
{
    std::vector<std::string> byte_strs;
    char buf[8];
    
    for (unsigned long i = 0; i < _length; ++i) {
        uint8_t byte = _data.get()[i];
        std::sprintf(buf, "%02x", byte);
        byte_strs.push_back(buf);
    }
    
    return byte_strs;
}

#pragma mark - Internal

void ZData::_realloc_data(size_t new_size)
{
    uint8_t *new_data = new uint8_t[new_size];
    uint8_t *current_data = _data.get();
    if (current_data != nullptr) {
        memcpy(new_data, current_data, std::min(_length, new_size));
    }
    
    _data = std::auto_ptr<uint8_t>(new_data);
    _capacity = new_size;
}

ZGE_END_NAMESPACE
