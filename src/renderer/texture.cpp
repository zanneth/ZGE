/*
 * texture.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/08/2014
 */

#include <zge/texture.h>
#include <zge/glutil.h>

ZGE_BEGIN_NAMESPACE

ZTexture::ZTexture(uint32_t name, ZImageRef image, const std::function<void(uint32_t)> &deleter) :
    _name(name),
    _deleter(deleter),
    _size(image->get_size()),
    _coordinate_rect({{0.0, 0.0}, {1.0, 1.0}})
{}

ZTexture::~ZTexture()
{
    _deleter(_name);
}

#pragma mark -

uint32_t ZTexture::get_texture_name() const
{
    return _name;
}

ZSize2D ZTexture::get_size() const
{
    return _size;
}

ZRect ZTexture::get_texture_rect() const
{
    return _coordinate_rect;
}

ZGE_END_NAMESPACE
