/*
 * font.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 10/17/2014
 */

#pragma once

#include <zge/foundation.h>
#include <zge/glyph.h>

BEGIN_ZGE_NAMESPACE

class ZFont {
public:
    ZFont(const std::string &font_path, size_t height = 16);
    ZFont(const ZFont &cp);
    ZFont(ZFont &&mv);
    ~ZFont();
    
    std::string get_font_path() const;
    size_t get_font_height() const;
    
    ZGlyph create_glyph(char character);
    
private:
    std::unique_ptr<struct _ZFontImpl> _impl;
};

typedef std::shared_ptr<ZFont> ZFontRef;

END_ZGE_NAMESPACE
