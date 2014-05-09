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
    virtual ~ZImage();
    
    virtual ZSize2D      get_size() const = 0;
    virtual ZPixelFormat get_pixel_format() const = 0;
    virtual ZDataRef     get_pixel_data() const = 0;
};

typedef std::shared_ptr<ZImage> ZImageRef;

END_ZGE_NAMESPACE
