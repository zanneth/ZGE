/*
 * font.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 10/17/2014
 */

#include "font.h"
#include "util.h"
#include <mutex>
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

ZGE_BEGIN_NAMESPACE

class ZFontLibrary {
public:
    ZFontLibrary();
    ~ZFontLibrary();
    
    static ZFontLibrary* instance();
    
    FT_Library* get_freetype_library();
    
private:
    FT_Library _freetype_library;
};

struct _ZFontImpl {
    std::string path;
    float       size;
    FT_Face     face;
};

ZFont::ZFont(const std::string &font_path, float size) :
    _impl(new _ZFontImpl)
{
    _impl->path = font_path;
    _impl->size = size;
    _impl->face = nullptr;
    
    ZFontLibrary *library = ZFontLibrary::instance();
    FT_Library *freetype = library->get_freetype_library();
    
    FT_Face face;
    FT_Error err = FT_New_Face(*freetype, font_path.c_str(), 0, &face);
    if (err != 0) {
        ZException ex(ZFILE_EXCEPTION_CODE);
        ex.extra_info = ZUtil::format("Font not found at path %s", font_path.c_str());
        throw ex;
    }
    
    FT_Set_Char_Size(face, size * 64, size * 64, 96, 96);
    _impl->face = face;
}

ZFont::ZFont(const ZFont &cp) :
    ZFont(cp.get_font_path(), cp.get_font_size())
{}

ZFont::ZFont(ZFont &&mv) :
    _impl(mv._impl.release())
{}

ZFont::~ZFont()
{
#if (ZDEBUG)
    zlog("Font %p destroyed.", this);
#endif
    
    if (_impl) {
        FT_Done_Face(_impl->face);
    }
}

#pragma mark - Accessors

std::string ZFont::get_font_path() const { return _impl->path; }

float ZFont::get_font_size() const { return _impl->size; }

float ZFont::get_line_height() const
{
    ZRect bounds = get_bounding_box();
    float descender = get_descender();
    
    return float(bounds.size.height - descender);
}

ZRect ZFont::get_bounding_box() const
{
    FT_BBox ft_box = _impl->face->bbox;
    
    // convert to pixels by dividing each value by 64
    ft_box.xMax /= 64;
    ft_box.xMin /= 64;
    ft_box.yMax /= 64;
    ft_box.yMin /= 64;
    
    return ZRect(
        ZPoint2D{0.0, 0.0},
        ZSize2D{float(ft_box.xMax - ft_box.xMin), float(ft_box.yMax - ft_box.yMin)}
    );
}

float ZFont::get_ascender() const
{
    return float(_impl->face->ascender / 64);
}

float ZFont::get_descender() const
{
    return float(_impl->face->descender / 64);
}

#pragma mark - API

ZGlyph ZFont::create_glyph(char character)
{
    FT_Error error = 0;
    FT_Face face = _impl->face;
    
    unsigned glyph_index = FT_Get_Char_Index(face, character);
    error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
    if (error != 0) {
        ZException ex(ZENGINE_EXCEPTION_CODE);
        ex.extra_info = ZUtil::format("Font %p failed to load glyph for character '%c'", this, character);
        throw ex;
    }
    
    FT_Glyph freetype_glyph;
    error = FT_Get_Glyph(face->glyph, &freetype_glyph);
    if (error != 0) {
        ZException ex(ZENGINE_EXCEPTION_CODE);
        ex.extra_info = ZUtil::format("Font %p failed to get glyph for character '%c'", this, character);
        throw ex;
    }
    
    FT_Glyph_To_Bitmap(&freetype_glyph, FT_RENDER_MODE_NORMAL, 0, 1);
    FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)freetype_glyph;
    FT_Bitmap bitmap = bitmap_glyph->bitmap;
    
    int width = bitmap.width;
    int height = bitmap.rows;
    size_t bitmap_length = width * height;
    ZDataRef bitmap_data = std::make_shared<ZData>(bitmap.buffer, bitmap_length);
    
    ZGlyph glyph = {
        .character = character,
        .size = { float(width), float(height) },
        .advance = ZSize2D{face->glyph->advance.x / 64.f, face->glyph->advance.y / 64.f},
        .insets = ZEdgeInsets{(float)bitmap_glyph->top, (float)bitmap_glyph->left, 0.f, 0.f},
        .bitmap = bitmap_data,
    };
    return glyph;
}

#pragma mark - ZFontLibrary

ZFontLibrary::ZFontLibrary()
{
    FT_Error err = FT_Init_FreeType(&_freetype_library);
    if (err != 0) {
        ZException ex(ZENGINE_EXCEPTION_CODE);
        ex.extra_info = "Failed to initialize FreeType library.";
        throw ex;
    }
}

ZFontLibrary::~ZFontLibrary()
{
    FT_Done_FreeType(_freetype_library);
}

ZFontLibrary* ZFontLibrary::instance()
{
    static ZFontLibrary *__shared_library;
    static std::once_flag __once;
    std::call_once(__once, [&] {
        __shared_library = new ZFontLibrary;
    });
    return __shared_library;
}

FT_Library* ZFontLibrary::get_freetype_library()
{
    return &_freetype_library;
}

ZGE_END_NAMESPACE
