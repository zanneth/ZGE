/*
 * light.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 01/23/2014
 */

#include "light.h"
#include <zge/exception.h>
#include <zge/util.h>

BEGIN_ZGE_NAMESPACE

static std::string _uniform_name_for_type(ZLightType type);

ZLight::ZLight(ZLightType type) :
    _type(type),
    _uniform_name(_uniform_name_for_type(_type))
{}

#pragma mark - Accessors

ZLightType ZLight::get_type() const { return _type; }

ZColor ZLight::get_color() const { return _color; }

void ZLight::set_color(const ZColor &color) { _color = color; }

#pragma mark - Internal

#warning this is not going to be as simple as using a name to refer to the light\
         data. we'll need to setup uniform blocks for lights to work efficiently.
std::string _uniform_name_for_type(ZLightType type)
{
    std::string name;
    switch (type) {
        case ZLIGHT_TYPE_AMBIENT:
            name = "ambient";
            break;
        default: {
            ZException e(ZASSERTION_EXCEPTION_CODE);
            e.extra_info = ZUtil::format("Light of type '%d' not supported.", type);
            throw e;
            break;
        }
    }
    return name;
}

END_ZGE_NAMESPACE
