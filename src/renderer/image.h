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

class ZImage : ZNoncopyable {
public:
    ZImage(std::string path);
    virtual ~ZImage();
    
    ZSize2D      get_size() const;
    ZImageFormat get_format() const;
    ZDataRef     get_pixel_data() const;
    
private:
    std::auto_ptr<struct _ZImageImpl> _impl;
};

typedef std::shared_ptr<ZImage> ZImageRef;

END_ZGE_NAMESPACE
