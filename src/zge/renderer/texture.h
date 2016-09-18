/*
 * texture.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/08/2014
 */

#pragma once

#include <zge/util/data.h>
#include <zge/core/foundation.h>
#include <zge/renderer/image.h>

ZGE_BEGIN_NAMESPACE

class ZTexture : ZNoncopyable {
public:
    virtual ~ZTexture();
    
    uint32_t get_texture_name() const;
    ZSize2D  get_size() const;
    ZRect    get_texture_rect() const;
    
protected:
    /// Only ZRenderContext may create textures.
    ZTexture(uint32_t name, ZImageRef image, const std::function<void(uint32_t)> &deleter);
    friend class ZRenderContext;
    
private:
    uint32_t                        _name;
    std::function<void(uint32_t)>   _deleter;
    ZSize2D                         _size;
    ZRect                           _coordinate_rect;
};

ZGE_DEFINE_SREF_TYPE(ZTexture);

ZGE_END_NAMESPACE
