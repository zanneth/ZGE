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
    ZFont(const std::string &font_path, float size = 16.f);
    ZFont(const ZFont &cp);
    ZFont(ZFont &&mv);
    ~ZFont();
    
    /// path to the font file
    std::string get_font_path() const;
    
    /// font size in points
    float get_font_size() const;
    
    /// vertical distance between two consecutive baselines, expressed in pixels
    float get_line_height() const;
    
    /// a bounding box representing the largest possible glyph that can be
    /// created using this font face, expressed in pixels
    ZRect get_bounding_box() const;
    
    /// topmost y-coordinate offset from the baseline, representing the font's
    /// longest ascender, expressed in pixels
    float get_ascender() const;
    
    /// bottommost y-coordinate offset from the baseline, representing the
    /// font's longest descender, expressed in pixels
    float get_descender() const;
    
    /// create a glyph from a specified character
    ZGlyph create_glyph(char character);
    
private:
    std::unique_ptr<struct _ZFontImpl> _impl;
};

typedef std::shared_ptr<ZFont> ZFontRef;

END_ZGE_NAMESPACE
