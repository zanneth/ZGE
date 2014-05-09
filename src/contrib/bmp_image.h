/*
 * bmp_image.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/08/2014
 */

#pragma once

#include <zge/foundation.h>
#include <zge/image.h>

BEGIN_ZGE_NAMESPACE

class ZBMPImage : public ZImage, ZNoncopyable {
public:
    ZBMPImage(std::string path);
    ~ZBMPImage();
    
    ZSize2D      get_size() const override;
    ZPixelFormat get_pixel_format() const override;
    ZDataRef     get_pixel_data() const override;
    
private:
    std::auto_ptr<struct _ZBMPImageImpl> _impl;
};

typedef std::shared_ptr<ZBMPImage> ZBMPImageRef;

END_ZGE_NAMESPACE
