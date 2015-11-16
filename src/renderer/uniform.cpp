/*
 * uniform.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 01/21/2014
 */

#include <zge/uniform.h>

ZGE_BEGIN_NAMESPACE
    
ZUniformBase::ZUniformBase(std::string name, int32_t location, uint32_t type) :
    _name(name),
    _location(location),
    _type(type),
    _dirty(false)
{}

ZUniformBase::~ZUniformBase()
{}

std::string ZUniformBase::get_name() const { return _name; }

int32_t ZUniformBase::get_location() const { return _location; }

uint32_t ZUniformBase::get_type() const { return _type; }

bool ZUniformBase::is_dirty() const { return _dirty; }

void ZUniformBase::set_dirty(bool dirty) { _dirty = dirty; }

ZGE_END_NAMESPACE
