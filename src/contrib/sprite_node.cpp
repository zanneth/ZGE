/*
 * sprite_node.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/24/2014
 */

#include <zge/sprite_node.h>

BEGIN_ZGE_NAMESPACE

ZSpriteNode::ZSpriteNode(ZTextureRef texture) :
    _quad(new ZQuad)
{
    set_geometry(_quad);
    set_texture(texture);
}

#pragma mark - Accessors

void ZSpriteNode::set_texture(ZTextureRef texture)
{
    _texture = texture;
    
    if (_texture.get()) {
        if (!_texture_material.get()) {
            _texture_material = ZTextureMaterialRef(new ZTextureMaterial);
            _quad->add_material(_texture_material);
        }
    }
    
    if (_texture_material.get()) {
        _texture_material->set_texture(_texture);
    }
}

void ZSpriteNode::set_color(const ZColor &color)
{
    _color = color;
    
    if (!_color_material.get()) {
        _color_material = ZColorMaterialRef(new ZColorMaterial);
        _quad->add_material(_color_material);
    }
    
    _color_material->set_color(_color);
}

void ZSpriteNode::set_size(const ZSize2D size)
{
    _size = size;
    _quad->set_quad_rect({{0.0, 0.0}, size});
}

ZTextureRef ZSpriteNode::get_texture() const { return _texture; }
ZColor ZSpriteNode::get_color() const { return _color; }
ZSize2D ZSpriteNode::get_size() const { return _size; }

END_ZGE_NAMESPACE
