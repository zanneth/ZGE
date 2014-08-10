/*
 * image.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/08/2014
 */

#include <zge/image.h>
#include <zge/color.h>
#include <SDL2/SDL_image.h>

BEGIN_ZGE_NAMESPACE

struct _ZImageImpl {
    SDL_Surface *img_surface;
};

ZImage::ZImage(std::string path) :
    _impl(new _ZImageImpl)
{
    SDL_Surface *surface = IMG_Load(path.c_str());
    if (!surface) {
        ZException exception(ZFILE_EXCEPTION_CODE);
        exception.extra_info = "Could not load image file at path " + path;
        throw exception;
    }
    
    _impl->img_surface = surface;
}

ZImage::~ZImage()
{
    if (_impl->img_surface) {
        SDL_FreeSurface(_impl->img_surface);
    }
}

#pragma mark -

ZSize2D ZImage::get_size() const
{
    int width = _impl->img_surface->w;
    int height = _impl->img_surface->h;
    return {(float)width, (float)height};
}

ZPixelFormat ZImage::get_pixel_format() const
{
    ZPixelFormat format = {
        .bytes_per_pixel = 4
    };
    return format;
}

ZDataRef ZImage::get_pixel_data() const
{
    ZPixelFormat format = get_pixel_format();
    SDL_Surface *surface = _impl->img_surface;
    int width = surface->w;
    int height = surface->h;
    size_t num_components = width * height;
    size_t pixel_buffer_sz = num_components * format.bytes_per_pixel;
    
    ZDataRef pixel_data = std::make_shared<ZData>(surface->pixels, pixel_buffer_sz);
    return pixel_data;
}

END_ZGE_NAMESPACE
