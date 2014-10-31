/*
 * text_node.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 10/18/2014
 */

#pragma once

#include <zge/foundation.h>
#include <zge/font.h>
#include <zge/glyph.h>
#include <zge/node.h>

ZGE_BEGIN_NAMESPACE

class ZTextNode : public ZNode {
public:
    ZTextNode(const std::string &text = "", ZFontRef font = nullptr);
    ~ZTextNode();
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZTextNode);
    
    std::string get_text() const;
    void set_text(const std::string &text);
    
    ZFontRef get_font() const;
    void set_font(ZFontRef font);
    
private:
    void _render_glyphs();
    
private:
    std::string _text;
    ZFontRef    _font;
    std::vector<ZGlyph> _glyphs;
};

ZGE_DEFINE_SREF_TYPE(ZTextNode);

ZGE_END_NAMESPACE