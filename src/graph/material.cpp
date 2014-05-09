/*
 * material.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 12/30/2013
 */

#include "material.h"

BEGIN_ZGE_NAMESPACE

ZMaterial::ZMaterial() :
    _color("materialColor"),
    _texture("materialTexture")
{
    _color.set_contents(ZWhiteColor);
}

ZMaterial::~ZMaterial()
{}

const ZMaterialProperty<ZColor>& ZMaterial::get_color() const
{
    return _color;
}

void ZMaterial::set_color(const ZColor &color)
{
    _color.set_contents(color);
}

const ZMaterialProperty<ZTextureRef>& ZMaterial::get_texture() const
{
    return _texture;
}

void ZMaterial::set_texture(ZTextureRef texture)
{
    _texture.set_contents(texture);
}

END_ZGE_NAMESPACE
