/*
 * light.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 01/23/2014
 */

#pragma once

#include <zge/color.h>
#include <zge/node.h>
#include <string>

BEGIN_ZGE_NAMESPACE

enum ZLightType {
    ZLIGHT_TYPE_AMBIENT
};

class ZLight : public ZNode {
public:
    ZLight(ZLightType type);
    
    ZLightType get_type() const;
    
    ZColor get_color() const;
    void set_color(const ZColor &color);

protected:
    std::string _get_uniform_name();
    
private:
    ZLightType _type;
    ZColor _color;
    std::string _uniform_name;
};

END_ZGE_NAMESPACE

