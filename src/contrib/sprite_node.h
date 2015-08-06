/*
 * sprite_node.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/24/2014
 */

#pragma once

#include <zge/foundation.h>
#include <zge/color.h>
#include <zge/material.h>
#include <zge/node.h>
#include <zge/quad.h>
#include <zge/texture.h>

ZGE_BEGIN_NAMESPACE

class ZSpriteNode : public ZNode, ZNoncopyable {
public:
    ZSpriteNode(ZTextureRef texture = nullptr);
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZSpriteNode);
    
    ZTextureRef get_texture() const;
    void set_texture(ZTextureRef texture);
    
    ZColor get_color() const;
    void set_color(const ZColor &color);
    
    float get_alpha() const;
    void set_alpha(float alpha);
    
    ZSize2D get_size() const;
    void set_size(const ZSize2D &size);
    
    ZRect get_texture_rect() const;
    void set_texture_rect(const ZRect &texture_rect);
    
    float get_rotation() const;
    void set_rotation(float radians);
    
    /* Node Overrides */
    bool should_draw(ZRenderContextRef context) override;
    
    /* Layout Overrides */
    ZRect get_bounds() const override;
    void set_bounds(const ZRect &bounds) override;
    
private:
    void _update_material_color();
    
private:
    ZTextureMaterialRef _texture_material;
    ZColorMaterialRef   _color_material;
    ZTextureRef         _texture;
    ZColor              _color;
    ZQuadRef            _quad;
    ZSize2D             _size;
    float               _alpha;
    float               _rotation;
};

ZGE_DEFINE_SREF_TYPE(ZSpriteNode);

ZGE_END_NAMESPACE
