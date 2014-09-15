/*
 * light.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/14/2014
 */

#include "light.h"

BEGIN_ZGE_NAMESPACE

ZLight::ZLight() :
    _type(ZLIGHT_TYPE_OMNIDIRECTIONAL),
    _color(ZColor::white)
{}

#pragma mark - Accessors

ZLightType ZLight::get_type() const { return _type; }

void ZLight::set_type(ZLightType type) { _type = type; }

ZColor ZLight::get_color() const { return _color; }

void ZLight::set_color(const ZColor &color) { _color = color; }

END_ZGE_NAMESPACE
