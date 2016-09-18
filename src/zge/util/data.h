/*
 * data.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 03/02/2014
 */

#pragma once

#include <zge/core/defines.h>
#include <zge/util/describable.h>
#include <memory>

ZGE_BEGIN_NAMESPACE

class ZData {
public:
    ZData();
    ZData(const void *data, size_t length, bool copy = true);
    ZData(const ZData &cp);
    ZData(ZData &&mv);
    ~ZData();
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZData);
    
    ZData& operator=(const ZData &cp);
    ZData& operator=(ZData &&mv);
    
    uint8_t& operator[](unsigned long off);
    uint8_t operator[](unsigned long off) const;
    
    bool operator==(const ZData &rhs) const;
    bool operator!=(const ZData &rhs) const;
    int compare(const ZData &rhs) const;
    
    /// Returns true if length is 0.
    operator bool() const;
    
    const void* get_bytes() const;
    size_t      get_length() const;
    
    friend std::ostream& operator<<(std::ostream &stream, const ZData &data);
    friend std::istream& operator>>(std::istream &stream, ZData &data);
    
    // non-const methods
    void set_bytes(const void *data, size_t length);
    void append_bytes(const void *data, size_t length);
    void append(const ZData &data);
    void clear();
    
private:
    void _ensure_capacity(size_t newSize);
    
private:
    size_t   _length;
    size_t   _capacity;
    uint8_t *_data;
    bool     _copied;
    
private:
    void _move(ZData &&mv);
};

ZGE_DEFINE_SREF_TYPE(ZData);

ZGE_END_NAMESPACE
