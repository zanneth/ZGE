/*
 * material.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 12/30/2013
 */

#include "material.h"

namespace zge {

ZMaterial::ZMaterial() :
    _color("materialColor")
{}

ZMaterial::~ZMaterial()
{}

ZMaterialProperty<ZColor>* ZMaterial::get_color()
{
    return &_color;
}

} // namespace zge
