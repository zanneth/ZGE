/*
 * bmp_image.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/08/2014
 */

#include <zge/bmp_image.h>
#include <zge/color.h>
#include <SDL2/SDL.h>

BEGIN_ZGE_NAMESPACE

static void _get_pixel_value(uint8_t *bytes, SDL_PixelFormat *format, ZColorb *out_color);

struct _ZBMPImageImpl {
    SDL_Surface *bmp_surface;
};

ZBMPImage::ZBMPImage(std::string path) :
    _impl(new _ZBMPImageImpl)
{
    SDL_Surface *surface = SDL_LoadBMP(path.c_str());
    if (!surface) {
        ZException exception(ZFILE_EXCEPTION_CODE);
        exception.extra_info = "Could not load BMP file at path " + path;
        throw exception;
    }
    
    _impl->bmp_surface = surface;
}

ZBMPImage::~ZBMPImage()
{
    SDL_FreeSurface(_impl->bmp_surface);
}

#pragma mark -

ZSize2D ZBMPImage::get_size() const
{
    int width = _impl->bmp_surface->w;
    int height = _impl->bmp_surface->h;
    return {(float)width, (float)height};
}

ZPixelFormat ZBMPImage::get_pixel_format() const
{
    ZPixelFormat format = {
        .bytes_per_pixel = _impl->bmp_surface->format->BytesPerPixel
    };
    return format;
}

ZDataRef ZBMPImage::get_pixel_data() const
{
    const unsigned dst_bytes_per_pixel = 4;
    
    SDL_Surface *surface = _impl->bmp_surface;
    SDL_PixelFormat *format = surface->format;
    int width = surface->w;
    int height = surface->h;
    
    size_t num_components = width * height;
    size_t pixel_buffer_sz = num_components * dst_bytes_per_pixel;
    uint8_t *pixel_buffer = new uint8_t[pixel_buffer_sz];
    size_t pixel_buffer_length = 0;
    
    ZColorb cur_color;
    uint8_t *cur_byte_ptr = (uint8_t *)surface->pixels;
    
    SDL_LockSurface(surface);
    for (unsigned i = 0; i < num_components; ++i) {
        _get_pixel_value(cur_byte_ptr, format, &cur_color);
        pixel_buffer[pixel_buffer_length++] = cur_color.r;
        pixel_buffer[pixel_buffer_length++] = cur_color.g;
        pixel_buffer[pixel_buffer_length++] = cur_color.b;
        pixel_buffer[pixel_buffer_length++] = 0xFF;
        
        cur_byte_ptr += format->BytesPerPixel;
    }
    SDL_UnlockSurface(surface);
    
    ZDataRef pixel_data = ZDataRef(new ZData(pixel_buffer, pixel_buffer_sz));
    delete[] pixel_buffer;
    return pixel_data;
}

void _get_pixel_value(uint8_t *bytes, SDL_PixelFormat *format, ZColorb *out_color)
{
    uint32_t pixel = 0;
    switch (format->BytesPerPixel) {
        case 1:
            pixel = (uint32_t)*bytes;
            break;
        case 2:
            pixel = (bytes[0]) + (bytes[1] << 8);
            break;
        case 3:
            pixel = (bytes[0]) + (bytes[1] << 8) + (bytes[2] << 16);
            break;
        case 4:
            pixel = (bytes[0]) + (bytes[1] << 8) + (bytes[2] << 16) + (bytes[3] << 24);
            break;
        default:
            break;
    }
    
    out_color->r = (((pixel & format->Rmask) >> format->Rshift) << format->Rloss);
    out_color->g = (((pixel & format->Gmask) >> format->Gshift) << format->Gloss);
    out_color->b = (((pixel & format->Bmask) >> format->Bshift) << format->Bloss);
    out_color->a = (((pixel & format->Amask) >> format->Ashift) << format->Aloss);
}

END_ZGE_NAMESPACE
