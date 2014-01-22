/*
 * material.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 12/30/2013
 */

#include "material.h"

namespace zge {

ZColor ZMaterial::get_ambient() const { return _ambient; }
void ZMaterial::set_ambient(const ZColor &ambient) { _ambient = ambient; }

} // namespace zge
