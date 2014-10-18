/*
 * font.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 10/17/2014
 */

#include "font.h"
#include <mutex>
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H

BEGIN_ZGE_NAMESPACE

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
    size_t height;
    FT_Face face;
};

ZFont::ZFont(const std::string &font_path, size_t height) :
    _impl(new _ZFontImpl)
{
    _impl->path = font_path;
    _impl->height = height;
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
    
    FT_Set_Char_Size(face, height * 64, height * 64, 96, 96);
}

ZFont::ZFont(const ZFont &cp) :
    ZFont(cp.get_font_path(), cp.get_font_height())
{}

ZFont::ZFont(ZFont &&mv) :
    _impl(mv._impl.release())
{}

ZFont::~ZFont()
{
    if (_impl) {
        FT_Done_Face(_impl->face);
    }
}

#pragma mark - Accessors

std::string ZFont::get_font_path() const { return _impl->path; }

size_t ZFont::get_font_height() const { return _impl->height; }

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

END_ZGE_NAMESPACE
