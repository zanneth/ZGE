/*
 * sprite_node.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/24/2014
 */

#include <zge/contrib/sprite_node.h>

ZGE_BEGIN_NAMESPACE

ZSpriteNode::ZSpriteNode(ZTextureRef texture) :
    _texture_material(nullptr),
    _color_material(nullptr),
    _texture(nullptr),
    _color(ZColor::white),
    _quad(new ZQuad),
    _size({0.0, 0.0}),
    _alpha(1.0),
    _rotation(0.0)
{
    set_geometry(_quad);
    set_texture(texture);
    set_color(ZColor::white);
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
    
    if (!_color_material) {
        _color_material = ZColorMaterialRef(new ZColorMaterial);
        _quad->add_material(_color_material);
    }
    
    _update_material_color();
}

void ZSpriteNode::set_alpha(float alpha)
{
    _alpha = alpha;
    _update_material_color();
}

void ZSpriteNode::set_size(const ZSize2D &size)
{
    _size = size;
    _quad->set_quad_rect({{0.0, 0.0}, size});
}

ZRect ZSpriteNode::get_texture_rect() const
{
    return _quad->get_texcoord_rect();
}

void ZSpriteNode::set_texture_rect(const ZRect &texture_rect)
{
    _quad->set_texcoord_rect(texture_rect);
}

void ZSpriteNode::set_rotation(float radians)
{
    float tx = _size.width / 2.0;
    float ty = _size.height / 2.0;
    ZMatrix transform = ZMatrix::translation(tx, ty, 0.0);
    transform = transform.rotate(radians, 0.0, 0.0, 1.0);
    transform = transform.translate(-tx, -ty, 0.0);
    
    set_transform(transform);
    _rotation = radians;
}

ZRect ZSpriteNode::get_bounds() const
{
    ZVector origin = this->get_position();
    return ZRect(
        ZPoint2D{origin.get_x(), origin.get_y()},
        _size
    );
}

void ZSpriteNode::set_bounds(const ZRect &bounds)
{
    set_position(bounds.origin);
    set_size(bounds.size);
}

ZTextureRef ZSpriteNode::get_texture() const { return _texture; }
ZColor ZSpriteNode::get_color() const { return _color; }
ZSize2D ZSpriteNode::get_size() const { return _size; }
float ZSpriteNode::get_alpha() const { return _alpha; }
float ZSpriteNode::get_rotation() const { return _rotation; }

bool ZSpriteNode::should_draw(ZRenderContextRef context)
{
    bool visible = (_alpha > 0.0 && _color.a > 0.0);
    return visible;
}

#pragma mark - Internal

void ZSpriteNode::_update_material_color()
{
    if (_color_material) {
        ZColor material_col = _color;
        material_col.a = std::min(material_col.a, _alpha);
        _color_material->set_color(material_col);
    }
}

ZGE_END_NAMESPACE
