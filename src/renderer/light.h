/*
 * light.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/14/2014
 */

#pragma once

#include <zge/defines.h>
#include <zge/color.h>
#include <zge/node.h>
#include <memory>

BEGIN_ZGE_NAMESPACE

enum ZLightType {
    ZLIGHT_TYPE_OMNIDIRECTIONAL
};

class ZLight : public ZNode {
public:
    ZLight();
    
    ZLightType get_type() const;
    void set_type(ZLightType type);
    
    ZColor get_color() const;
    void set_color(const ZColor &color);
    
private:
    ZLightType _type;
    ZColor     _color;
};

typedef std::shared_ptr<ZLight> ZLightRef;

END_ZGE_NAMESPACE
