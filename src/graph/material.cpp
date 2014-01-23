/*
 * material.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 12/30/2013
 */

#include "material.h"

namespace zge {

ZMaterial::ZMaterial() :
    _ambient("ambientColor")
{}

ZMaterial::~ZMaterial()
{}

bool ZMaterial::is_dirty() const
{
    bool dirty = true;
    dirty &= _ambient.is_dirty();
    
    return dirty;
}

void ZMaterial::clear_dirty()
{
    _ambient.clear_dirty();
}

ZMaterialProperty<ZColor>* ZMaterial::get_ambient()
{
    return &_ambient;
}

} // namespace zge
