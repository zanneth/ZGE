/*
 * texture.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/08/2014
 */

#pragma once

#include <zge/data.h>
#include <zge/foundation.h>
#include <zge/image.h>

BEGIN_ZGE_NAMESPACE

class ZTexture : ZNoncopyable {
public:
    ZTexture(ZImageRef image);
    ~ZTexture();
    
    ZSize2D get_size() const;
    ZRect   get_texture_rect() const;
    
    // private
    uint32_t _get_texture_name() const;
    
private:
    void _bind();
    
private:
    std::auto_ptr<struct _ZTextureImpl> _impl;
};

typedef std::shared_ptr<ZTexture> ZTextureRef;

END_ZGE_NAMESPACE
