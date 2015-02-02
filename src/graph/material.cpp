/*
 * material.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 12/30/2013
 */

#include "material.h"

ZGE_BEGIN_NAMESPACE

ZMaterial::~ZMaterial()
{}

void ZMaterial::prepare_for_draw(ZRenderContextRef context)
{}

void ZMaterial::finalize_draw(ZRenderContextRef context)
{}

#pragma mark - ZColorMaterial

ZColorMaterial::ZColorMaterial(const ZColor &col) :
    _color(col)
{}

ZColor ZColorMaterial::get_color() const { return _color; }
void ZColorMaterial::set_color(const ZColor &color) { _color = color; }

std::string ZColorMaterial::get_shader_name() const
{
    return "material.color";
}

const void* ZColorMaterial::get_contents_data() const
{
    return (const void *)_color.data;
}

#pragma mark - ZTextureMaterial

ZTextureMaterial::ZTextureMaterial(ZTextureRef texture) :
    _texture(texture)
{
    _cached_texture_name = _texture->_get_texture_name();
}

ZTextureRef ZTextureMaterial::get_texture() const { return _texture; }
void ZTextureMaterial::set_texture(ZTextureRef texture)
{
    _texture = texture;
    _cached_texture_name = _texture->_get_texture_name();
}

std::string ZTextureMaterial::get_shader_name() const
{
    return "material.texture";
}

const void* ZTextureMaterial::get_contents_data() const
{
    return &_cached_texture_name;
}

void ZTextureMaterial::prepare_for_draw(ZRenderContextRef context)
{
    if (_texture.get()) {
        context->bind_texture(_texture);
    }
}

void ZTextureMaterial::finalize_draw(ZRenderContextRef context)
{
    context->unbind_texture();
}

ZGE_END_NAMESPACE
