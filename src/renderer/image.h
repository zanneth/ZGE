/*
 * image.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/08/2014
 */

#pragma once

#include <zge/foundation.h>
#include <zge/data.h>

BEGIN_ZGE_NAMESPACE

struct ZPixelFormat {
    uint8_t bytes_per_pixel;
};

class ZImage : ZNoncopyable {
public:
    ZImage(std::string path);
    virtual ~ZImage();
    
    ZSize2D      get_size() const;
    ZPixelFormat get_pixel_format() const;
    ZDataRef     get_pixel_data() const;
    
private:
    std::auto_ptr<struct _ZImageImpl> _impl;
};

typedef std::shared_ptr<ZImage> ZImageRef;

END_ZGE_NAMESPACE
