/*
 * light.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/14/2014
 */

#include "light.h"

ZGE_BEGIN_NAMESPACE

ZLight::ZLight(ZLightType type) :
    _type(type),
    _color(ZColor::white)
{}

#pragma mark - Accessors

ZLightType ZLight::get_type() const { return _type; }

void ZLight::set_type(ZLightType type) { _type = type; }

ZColor ZLight::get_color() const { return _color; }

void ZLight::set_color(const ZColor &color) { _color = color; }

ZGE_END_NAMESPACE
