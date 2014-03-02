/*
 * uniform.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 01/21/2014
 */

#include <zge/uniform.h>

BEGIN_ZGE_NAMESPACE
    
ZUniformBase::ZUniformBase(std::string name, GLint location, GLenum type) :
    _name(name),
    _location(location),
    _type(type)
{}

ZUniformBase::~ZUniformBase()
{}

std::string ZUniformBase::get_name() const { return _name; }

GLenum ZUniformBase::get_type() const { return _type; }

GLint ZUniformBase::_get_location() const { return _location; }

END_ZGE_NAMESPACE
