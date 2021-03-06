/*
 * text_node.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 10/18/2014
 */

#pragma once

#include <zge/core/foundation.h>
#include <zge/text/font.h>
#include <zge/text/glyph.h>
#include <zge/graph/node.h>

ZGE_BEGIN_NAMESPACE

ZGE_FORWARD_DECLARE_SREF(ZSpriteNode);

class ZTextNode : public ZNode {
public:
    ZTextNode(const std::wstring &text = L"", ZFontRef font = nullptr);
    ZTextNode(const std::string &text, ZFontRef font = nullptr);
    ~ZTextNode();
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZTextNode);
    
    std::wstring get_text() const;
    void set_text(const std::wstring &text);
    void set_text(const std::string &text);
    
    ZFontRef get_font() const;
    void set_font(ZFontRef font);
    
    ZColor get_text_color() const;
    void set_text_color(const ZColor &color);
    
    ZLineBreakMode get_line_break_mode() const;
    void set_line_break_mode(ZLineBreakMode mode);
    
    float get_line_height() const;
    void set_line_height(float height);
    
    /* Layout */
    ZRect get_bounds() const override;
    void set_bounds(const ZRect &bounds) override;
    
private:
    void _render_glyphs(bool force = false);
    
private:
    std::wstring                _text;
    std::wstring                _rendered_text;
    ZFontRef                    _font;
    ZColor                      _text_color;
    ZSize2D                     _size;
    ZLineBreakMode              _line_break_mode;
    float                       _line_height;
    std::vector<ZSpriteNodeRef> _glyph_nodes;
};

ZGE_DEFINE_SREF_TYPE(ZTextNode);

ZGE_END_NAMESPACE
