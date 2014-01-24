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

ZMaterialProperty<ZColor>* ZMaterial::get_ambient()
{
    return &_ambient;
}

} // namespace zge
