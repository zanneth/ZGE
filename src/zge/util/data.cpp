/*
 * data.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 03/02/2014
 */

#include <zge/util/data.h>
#include <algorithm>
#include <cstring>

#define REALLOC_EXTRA 256

ZGE_BEGIN_NAMESPACE

ZData::ZData() :
    _length(0),
    _capacity(0),
    _data(nullptr),
    _copied(false)
{}

ZData::ZData(const void *data, size_t length, bool copy) :
    _length(length),
    _capacity(length),
    _data(length > 0 && copy ? new uint8_t[length] : nullptr),
    _copied(copy)
{
    if (copy) {
        if (data != nullptr) {
            memcpy(_data, data, length);
        } else {
            memset(_data, 0, length);
        }
    } else {
        _data = (uint8_t *)data;
    }
}

ZData::ZData(const ZData &cp) : ZData(cp._data, cp._length, true)
{}

ZData::ZData(ZData &&mv)
{
    _move(std::move(mv));
}

ZData::~ZData()
{
    if (_copied) {
        delete[] _data;
    }
}

ZData& ZData::operator=(const ZData &cp)
{
    if (this != &cp) {
        if (_data && _copied) {
            delete[] _data;
        }
        
        size_t cap = cp._length;
        _data = new uint8_t[cap];
        _length = cap;
        _capacity = cap;
        _copied = true;
        
        memcpy(_data, cp._data, cp._length);
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
    return *(_data + off);
}

uint8_t ZData::operator[](unsigned long off) const
{
    return _data[off];
}

bool ZData::operator==(const ZData &rhs) const
{
    if (rhs.get_length() != get_length()) return false;
    return (memcmp(_data, rhs._data, get_length()) == 0);
}

bool ZData::operator!=(const ZData &rhs) const
{
    return !(*this == rhs);
}

int ZData::compare(const ZData &rhs) const
{
    size_t rhs_len = rhs.get_length();
    const void *rhs_bytes = rhs.get_bytes();
    
    size_t len = std::min(_length, rhs_len);
    int cmp = memcmp(_data, rhs_bytes, len);
    if (cmp == 0 && _length != rhs_len) {
        cmp = (_length > rhs_len) ? 1 : -1;
    }
    return cmp;
}

ZData::operator bool() const
{
    return (_length > 0);
}

const void* ZData::get_bytes() const
{
    return _data;
}

size_t ZData::get_length() const
{
    return _length;
}

std::ostream& operator<<(std::ostream &stream, const ZData &data)
{
    const char *bytes = reinterpret_cast<const char *>(data.get_bytes());
    stream.write(bytes, data.get_length());
    return stream;
}

std::istream& operator>>(std::istream &stream, ZData &data)
{
    const size_t chunksz = 1024;
    std::vector<char> buffer;
    size_t bytes_read = 0;
    
    while (stream.good()) {
        size_t cur_buff_sz = buffer.size();
        buffer.resize(cur_buff_sz + chunksz);
        
        auto beginitr = buffer.begin() + cur_buff_sz;
        char *begin = &*beginitr;
        stream.read(begin, chunksz);
        
        bytes_read += stream.gcount();
    }
    
    data.append_bytes(buffer.data(), bytes_read);
    return stream;
}

void ZData::set_bytes(const void *data, size_t length)
{
    clear();
    append_bytes(data, length);
}

void ZData::append_bytes(const void *data, size_t length)
{
    _ensure_capacity(_length + length);
    
    uint8_t *cur_byte_ptr = _data;
    if (cur_byte_ptr != nullptr) {
        memcpy(cur_byte_ptr + _length, data, length);
    }
    
    _length += length;
}

void ZData::append(const ZData &data)
{
    if (data.get_length() > 0) {
        append_bytes(data.get_bytes(), data.get_length());
    }
}


void ZData::clear()
{
    _length = 0;
}

#pragma mark - Internal

void ZData::_move(ZData &&mv)
{
    _data = mv._data;
    mv._data = nullptr;
    
    _length = mv._length;
    mv._length = 0;
    
    _capacity = mv._capacity;
    mv._capacity = 0;
    
    _copied = mv._copied;
}

void ZData::_ensure_capacity(size_t new_size)
{
    if (_capacity >= new_size) {
        // TODO: Consider shrinking here if newSize is sufficiently smaller.
        return;
    }
    
    size_t new_capacity = new_size + REALLOC_EXTRA;
    uint8_t *new_data = new uint8_t[new_capacity];
    memcpy(new_data, _data, _length);
    
    _data = new_data;
    _capacity = new_capacity;
    _copied = true;
}

ZGE_END_NAMESPACE
