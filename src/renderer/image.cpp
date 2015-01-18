/*
 * image.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/08/2014
 */

#include <zge/image.h>
#include <zge/color.h>
#include <zge/logger.h>
#include <SDL2/SDL_image.h>

ZGE_BEGIN_NAMESPACE

static ZPixelFormat _pixel_frmt_from_sdl_frmt(SDL_PixelFormat *sdl_frmt);
static ZDataRef _pixel_data_from_sdl_surface(SDL_Surface *surface, ZImageFormat format);

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
    _impl->img_format = format;
    _impl->img_size = ZSize2D{float(surface->w), float(surface->h)};
    
    // store image data from surface
    _impl->img_data = _pixel_data_from_sdl_surface(surface, format);
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
#if OPENGL_ES
        // this probably isn't the right thing to do...
        ZLogger::log_error("WARNING: Unsupported pixel format for GLES: %u", rmask);
        format = ZPIXEL_FORMAT_RGBA;
#else
        format = ZPIXEL_FORMAT_BGRA;
#endif
    }
    
    return format;
}

ZDataRef _pixel_data_from_sdl_surface(SDL_Surface *surface, ZImageFormat format)
{
    int width = surface->w;
    int height = surface->h;
    size_t num_components = width * height;
    size_t pixel_buffer_sz = num_components * format.bytes_per_pixel;
    
    ZDataRef pixel_data = std::make_shared<ZData>(surface->pixels, pixel_buffer_sz);
    return pixel_data;
}

ZGE_END_NAMESPACE
