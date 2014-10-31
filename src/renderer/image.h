/*
 * image.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/08/2014
 */

#pragma once

#include <zge/foundation.h>
#include <zge/data.h>

ZGE_BEGIN_NAMESPACE

class ZImage : ZNoncopyable {
public:
    ZImage(const std::string &path);
    ZImage(ZDataRef image_data, ZSize2D size, ZImageFormat image_format);
    ~ZImage();
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZImage);
    
    ZSize2D      get_size() const;
    ZImageFormat get_format() const;
    ZDataRef     get_pixel_data() const;
    
private:
    std::auto_ptr<struct _ZImageImpl> _impl;
};

ZGE_DEFINE_SREF_TYPE(ZImage);

ZGE_END_NAMESPACE
