/*
 * data.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 03/02/2014
 */

#pragma once

#include <zge/defines.h>
#include <memory>

BEGIN_ZGE_NAMESPACE

class ZData {
protected:
    size_t _length;
    std::auto_ptr<uint8_t> _data;
    
public:
    ZData(const void *data, size_t length);
    ZData(const ZData &cp);
    ZData(ZData &&mv);
    
    ZData& operator=(const ZData &cp);
    ZData& operator=(ZData &&mv);
    
    const void* get_data() const;
    size_t get_length() const;

private:
    void _move(ZData &&mv);
};

typedef std::shared_ptr<ZData> ZDataRef;

class ZMutableData : public ZData {
protected:
    size_t _capacity;
    
public:
    ZMutableData(const void *data = nullptr, size_t length = 0);
    ZMutableData(const ZData &cp);
    ZMutableData(ZData &&mv);
    
    ZMutableData& operator=(const ZData &cp);
    ZMutableData& operator=(ZData &&mv);
    
    void set_data(const void *data, size_t length);
    void append_data(const void *data, size_t length);
    void clear_data();
    
private:
    void _realloc_data(size_t new_size);
};

typedef std::shared_ptr<ZMutableData> ZMutableDataRef;

END_ZGE_NAMESPACE
