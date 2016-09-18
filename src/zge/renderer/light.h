/*
 * light.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/14/2014
 */

#pragma once

#include <zge/core/defines.h>
#include <zge/core/color.h>
#include <zge/graph/node.h>
#include <zge/core/types.h>
#include <memory>

ZGE_BEGIN_NAMESPACE

class ZLight : public ZNode {
public:
    ZLight(ZLightType type = ZLIGHT_TYPE_POINT);
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZLight);
    
    ZLightType get_type() const;
    void set_type(ZLightType type);
    
    ZColor get_color() const;
    void set_color(const ZColor &color);
    
private:
    ZLightType _type;
    ZColor     _color;
};

ZGE_DEFINE_SREF_TYPE(ZLight);

ZGE_END_NAMESPACE
