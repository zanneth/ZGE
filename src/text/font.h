/*
 * font.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 10/17/2014
 */

#pragma once

#include <zge/foundation.h>

BEGIN_ZGE_NAMESPACE

class ZFont {
public:
    ZFont(const std::string &font_path, size_t height = 16);
    ZFont(const ZFont &cp);
    ZFont(ZFont &&mv);
    ~ZFont();
    
    std::string get_font_path() const;
    size_t get_font_height() const;
    
private:
    std::unique_ptr<struct _ZFontImpl> _impl;
};

END_ZGE_NAMESPACE
