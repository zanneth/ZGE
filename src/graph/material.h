/*
 * material.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 12/30/2013
 */

#pragma once

#include <zge/color.h>
#include <memory>

namespace zge {

class ZMaterial {
public:
    ZColor get_ambient() const;
    void   set_ambient(const ZColor &ambient);
    
private:
    ZColor _ambient;
};

typedef std::shared_ptr<ZMaterial> ZMaterialRef;

} // namespace zge
