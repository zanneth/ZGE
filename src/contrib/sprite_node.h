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

BEGIN_ZGE_NAMESPACE

class ZSpriteNode : public ZNode, ZNoncopyable {
public:
    ZSpriteNode(ZTextureRef texture = nullptr);
    ~ZSpriteNode() = default;
    
    ZTextureRef get_texture() const;
    void set_texture(ZTextureRef texture);
    
    ZColor get_color() const;
    void set_color(const ZColor &color);
    
    ZSize2D get_size() const;
    void set_size(const ZSize2D size);
    
    ZRect get_texture_rect() const;
    void set_texture_rect(const ZRect &texture_rect);
    
    float get_rotation() const;
    void set_rotation(float radians);
    
    ZRect get_frame() const;
    
private:
    ZTextureMaterialRef _texture_material;
    ZColorMaterialRef   _color_material;
    ZTextureRef         _texture;
    ZColor              _color;
    ZQuadRef            _quad;
    ZSize2D             _size;
    float               _rotation;
};

typedef std::shared_ptr<ZSpriteNode> ZSpriteNodeRef;

END_ZGE_NAMESPACE
