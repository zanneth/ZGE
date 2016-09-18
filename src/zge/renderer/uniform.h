/*
 * uniform.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 01/10/2014
 */

#pragma once

#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <zge/core/defines.h>
#include <zge/core/observable.h>

ZGE_BEGIN_NAMESPACE

class ZUniformBase {
public:
    ZUniformBase(std::string name, int32_t location, uint32_t type);
    virtual ~ZUniformBase();
    
    std::string get_name() const;
    int32_t     get_location() const;
    uint32_t    get_type() const;
    
    bool        is_dirty() const;
    void        set_dirty(bool dirty);
    
    virtual const void* get_data(size_t *out_length) const = 0;
    virtual void set_data(const void *data) = 0;
    
protected:
    std::string _name;
    int32_t     _location;
    uint32_t    _type;
    bool        _dirty;
};

using ZUniformRef = std::shared_ptr<ZUniformBase>;
using ZUniformWeakRef = std::weak_ptr<ZUniformBase>;
using ZUniformConstRef = std::shared_ptr<const ZUniformBase>;

// -----------------------------------------------------------------------------

template <typename T, unsigned count>
class ZUniform : public ZUniformBase {
public:
    ZUniform(std::string name, int32_t location, uint32_t type);
    ZUniform(const ZUniform &cp);
    ZUniform(ZUniform&&);
    ~ZUniform();
    
    const void* get_data(size_t *out_length) const override;
    void set_data(const void *data) override;
    
private:
    T _values[count];
};

ZGE_END_NAMESPACE

#include <zge/renderer/uniform.hpp>
