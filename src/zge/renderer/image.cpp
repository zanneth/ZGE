/*
 * image.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/08/2014
 */

#include <zge/renderer/image.h>
#include <zge/core/color.h>
#include <zge/util/logger.h>
#include <SDL2/SDL_image.h>
#include <algorithm>

ZGE_BEGIN_NAMESPACE

static ZPixelFormat _pixel_frmt_from_sdl_frmt(SDL_PixelFormat *sdl_frmt);
static ZDataRef _pixel_data_from_sdl_surface(SDL_Surface *surface, ZImageFormat orig_format, ZImageFormat dest_format);

struct _ZImageImpl {
    SDL_Surface *img_surface;
    ZImageFormat img_format;
    ZDataRef     img_data;
    ZSize2D      img_size;
};

ZImage::ZImage(const std::string &path) :
    _impl(new _ZImageImpl)
{
    // create SDL surface from image at the specified path
    SDL_Surface *surface = IMG_Load(path.c_str());
    if (!surface) {
        ZException exception(ZFILE_EXCEPTION_CODE);
        exception.extra_info = "Could not load image file at path " + path;
        throw exception;
    }
    
    _impl->img_surface = surface;
    
    // convert pixel format to something usable
    ZPixelFormat pixel_frmt = ZPIXEL_FORMAT_RGBA;
    SDL_PixelFormat *sdl_frmt = (_impl->img_surface ? _impl->img_surface->format : nullptr);
    if (sdl_frmt) {
        pixel_frmt = _pixel_frmt_from_sdl_frmt(sdl_frmt);
    }
    
    ZImageFormat format = {
        .bytes_per_pixel = 4,
        .pixel_format = pixel_frmt
    };
    
    ZImageFormat dest_img_format = format;
#if OPENGL_ES
    // OpenGL ES does not support BGRA pixel formats. we need to convert
    dest_img_format.pixel_format = ZPIXEL_FORMAT_RGBA;
#endif
    
    // store image data from surface, converting if necessary
    _impl->img_data = _pixel_data_from_sdl_surface(surface, format, dest_img_format);
    _impl->img_size = ZSize2D{float(surface->w), float(surface->h)};
    _impl->img_format = dest_img_format;
}

ZImage::ZImage(ZDataRef image_data, ZSize2D size, ZImageFormat image_format) :
    _impl(new _ZImageImpl)
{
    _impl->img_data = image_data;
    _impl->img_format = image_format;
    _impl->img_surface = nullptr;
    _impl->img_size = size;
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
    return _impl->img_size;
}

ZImageFormat ZImage::get_format() const
{
    return _impl->img_format;
}

ZDataRef ZImage::get_pixel_data() const
{
    return _impl->img_data;
}

#pragma mark - Internal

ZPixelFormat _pixel_frmt_from_sdl_frmt(SDL_PixelFormat *sdl_frmt)
{
    ZPixelFormat format = ZPIXEL_FORMAT_RGBA;
    uint32_t rmask = sdl_frmt->Rmask;
    
    if (rmask == 0x0) {
        format = ZPIXEL_FORMAT_RGBA;
    } else if (rmask == 0xff0000) {
        format = ZPIXEL_FORMAT_BGRA;
    }
    
    return format;
}

ZDataRef _pixel_data_from_sdl_surface(SDL_Surface *surface, ZImageFormat orig_format, ZImageFormat dest_format)
{
    ZDataRef pixel_data;
    
    int width = surface->w;
    int height = surface->h;
    size_t num_components = width * height;
    uint8_t bytes_per_pixel = orig_format.bytes_per_pixel;
    size_t pixel_buffer_sz = num_components * bytes_per_pixel;
    
    if (orig_format.pixel_format == dest_format.pixel_format) {
        pixel_data = ZData::create(surface->pixels, pixel_buffer_sz);
    } else {
        pixel_data = ZData::create(nullptr, pixel_buffer_sz);
        const uint8_t *src_buffer = (const uint8_t *)surface->pixels;
        
        for (unsigned long i = 0; i < pixel_buffer_sz; i += bytes_per_pixel) {
            uint8_t pixel_cmps[bytes_per_pixel];
            std::copy(src_buffer + i, src_buffer + i + bytes_per_pixel, pixel_cmps);
            
            if ((orig_format.pixel_format == ZPIXEL_FORMAT_RGBA && dest_format.pixel_format == ZPIXEL_FORMAT_BGRA) ||
                (orig_format.pixel_format == ZPIXEL_FORMAT_BGRA && dest_format.pixel_format == ZPIXEL_FORMAT_RGBA)) {
                (*pixel_data)[i + 0] = pixel_cmps[2];
                (*pixel_data)[i + 1] = pixel_cmps[1];
                (*pixel_data)[i + 2] = pixel_cmps[0];
                (*pixel_data)[i + 3] = pixel_cmps[3];
            } else {
                size_t bytes_to_copy = std::min(bytes_per_pixel, dest_format.bytes_per_pixel);
                for (unsigned j = 0; j < bytes_to_copy; ++j) {
                    (*pixel_data)[i + j] = pixel_cmps[j];
                }
            }
        }
    }
    
    return pixel_data;
}

ZGE_END_NAMESPACE
