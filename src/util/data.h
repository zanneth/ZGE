/*
 * data.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 03/02/2014
 */

#pragma once

#include <zge/defines.h>
#include <zge/describable.h>
#include <memory>

ZGE_BEGIN_NAMESPACE

class ZData : public ZDescribable {
public:
    ZData(const void *data = nullptr, size_t length = 0);
    ZData(const ZData &cp);
    ZData(ZData &&mv);
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZData);
    
    ZData& operator=(const ZData &cp);
    ZData& operator=(ZData &&mv);
    
    uint8_t& operator[](unsigned long off);
    uint8_t operator[](unsigned long off) const;
    
    const void* get_data() const;
    size_t get_length() const;
    
    void set_data(const void *data, size_t length);
    void append_data(const void *data, size_t length);
    void clear_data();
    
    // describable overrides
    std::string get_class_name() const override;
    std::vector<std::string> get_description_attributes() const override;

private:
    void _move(ZData &&mv);
    void _realloc_data(size_t new_size);
    
private:
    size_t _length;
    size_t _capacity;
    std::auto_ptr<uint8_t> _data;
};

ZGE_DEFINE_SREF_TYPE(ZData);

ZGE_END_NAMESPACE
