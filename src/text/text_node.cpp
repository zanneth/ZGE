/*
 * text_node.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 10/18/2014
 */

#include "text_node.h"
#include "material.h"
#include "quad.h"
#include "sprite_node.h"
#include "texture.h"
#include <codecvt>
#include <limits>

ZGE_BEGIN_NAMESPACE

class ZGlyphNode : public ZSpriteNode {
public:
    using ZSpriteNode::ZSpriteNode;
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZGlyphNode);
    
    const ZGlyph& get_glyph() const
    {
        return _glyph;
    }
    
    void set_glyph(const ZGlyph &glyph)
    {
        _glyph = glyph;
    }
    
private:
    ZGlyph _glyph;
};

ZGE_DEFINE_SREF_TYPE(ZGlyphNode);

// -----------------------------------------------------------------------------

ZTextNode::ZTextNode(const std::wstring &text, ZFontRef font) :
    _text(text),
    _font(font),
    _text_color(ZColor::white),
    _size({std::numeric_limits<float>::max(), std::numeric_limits<float>::max()}),
    _line_break_mode(ZLINE_BREAK_NONE),
    _line_height(0.0)
{
    _render_glyphs();
}

ZTextNode::ZTextNode(const std::string &text, ZFontRef font) :
    _font(font),
    _text_color(ZColor::white),
    _size({std::numeric_limits<float>::max(), std::numeric_limits<float>::max()}),
    _line_break_mode(ZLINE_BREAK_NONE),
    _line_height(0.0)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    _text = converter.from_bytes(text);
    
    _render_glyphs();
}

ZTextNode::~ZTextNode()
{}

#pragma mark - Accessors

std::wstring ZTextNode::get_text() const { return _text; }

ZFontRef ZTextNode::get_font() const { return _font; }

ZColor ZTextNode::get_text_color() const { return _text_color; }

void ZTextNode::set_text(const std::wstring &text)
{
    _text = text;
    _render_glyphs();
}

void ZTextNode::set_text(const std::string &text)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    _text = converter.from_bytes(text);
    _render_glyphs();
}

void ZTextNode::set_font(ZFontRef font)
{
    _font = font;
    _render_glyphs(true);
}

void ZTextNode::set_text_color(const ZColor &color)
{
    _text_color = color;
    _render_glyphs(true);
}

ZLineBreakMode ZTextNode::get_line_break_mode() const
{
    return _line_break_mode;
}

void ZTextNode::set_line_break_mode(ZLineBreakMode mode)
{
    _line_break_mode = mode;
    _render_glyphs(true);
}

float ZTextNode::get_line_height() const
{
    return _line_height;
}

void ZTextNode::set_line_height(float height)
{
    _line_height = height;
    _render_glyphs(true);
}

#pragma mark - API

ZRect ZTextNode::get_bounds() const
{
    ZRect box;
    
    for (ZSpriteNodeRef glyph_node : _glyph_nodes) {
        ZRect frame = glyph_node->get_bounds();
        box.size.width = std::max(box.size.width, frame.origin.x + frame.size.width);
        box.size.height = std::max(box.size.height, frame.origin.y + frame.size.height);
    }
    
    return box;
}

void ZTextNode::set_bounds(const ZRect &bounds)
{
    _size = bounds.size;
    set_position(bounds.origin);
    _render_glyphs(true);
}

#pragma mark - Internal

void ZTextNode::_render_glyphs(bool force)
{
    if (!_font || (_rendered_text == _text && !force)) {
        return;
    }
    
    // clear current rendering
    remove_all_children();
    _glyph_nodes.clear();
    
    // create glyphs using provided font
    std::vector<ZGlyph> glyphs;
    for (const auto &character : _text) {
        ZGlyph glyph = _font->create_glyph(character);
        glyphs.push_back(glyph);
    }
    
    // create textures and nodes for glyph
    ZRenderContext *ctx = ZRenderContext::get_current_context();
    const size_t bytes_per_pixel = 4;
    const ZImageFormat format = {
        .bytes_per_pixel = bytes_per_pixel,
        .pixel_format = ZPIXEL_FORMAT_RGBA
    };
    
    const float line_height = _font->get_line_height();
    const size_t len = _text.size();
    std::vector<ZGlyphNodeRef> word_nodes;
    unsigned char_idx = 0;
    float last_glyph_max_x = 0.0;
    float offset_y = 0.0;
    
    // render each glyph
    for (const ZGlyph &glyph : glyphs) {
        size_t num_pixels = (size_t)glyph.size.width * (size_t)glyph.size.height;
        ZDataRef dst_pixbuf_data = std::make_shared<ZData>(nullptr, bytes_per_pixel * num_pixels);
        uint8_t *src_pixbuf = (uint8_t *)glyph.bitmap->get_data();
        uint8_t *dst_pixbuf = (uint8_t *)dst_pixbuf_data->get_data();
        size_t width = (size_t)glyph.size.width;
        size_t height = (size_t)glyph.size.height;
        
        for (unsigned y = 0; y < height; ++y) {
            for (unsigned x = 0; x < width; ++x) {
                size_t src_off = (y * width) + x;
                size_t dst_off = 4 * ((y * width) + x);
                uint8_t src_pixval = src_pixbuf[src_off];
                
                dst_pixbuf[dst_off + 0] =
                dst_pixbuf[dst_off + 1] =
                dst_pixbuf[dst_off + 2] =
                    src_pixval;
                
                dst_pixbuf[dst_off + 3] = (src_pixval > 128 ? 0xff : 0x00);
            }
        }
        
        ZImageRef texture_image = ZImage::create(dst_pixbuf_data, glyph.size, format);
        ZTextureRef texture = ctx->create_texture(texture_image);
        ZGlyphNodeRef glyph_node = ZGlyphNode::create(texture);
        glyph_node->set_glyph(glyph);
        glyph_node->set_size(glyph.size);
        glyph_node->set_color(_text_color);
        
        // if we exceeded the drawing bounds and a line break mode is set, enact
        // the rules of the line break mode.
        // for word-breaking, we may have to back-track into chars that were
        // already rendered and positioned
        bool char_exceeds_bounds = (last_glyph_max_x + glyph.insets.left + glyph.advance.width >= _size.width);
        if (_line_break_mode == ZLINE_BREAK_WORD) {
            if (glyph.character != L' ' && char_idx != len - 1) {
                word_nodes.push_back(glyph_node);
            } else {
                if (char_exceeds_bounds) {
                    last_glyph_max_x = 0.0;
                    offset_y += line_height + _line_height;
                    
                    for (const ZGlyphNodeRef &word_char_node : word_nodes) {
                        const ZGlyph &word_char_glyph = word_char_node->get_glyph();
                        ZVector charpos = word_char_node->get_position();
                        charpos.x() = last_glyph_max_x + word_char_glyph.insets.left;
                        charpos.y() += line_height + _line_height;
                        word_char_node->set_position(charpos);
                        
                        last_glyph_max_x = charpos.x() + word_char_glyph.advance.width;
                    }
                }
                
                word_nodes.clear();
            }
        } else if (_line_break_mode == ZLINE_BREAK_CHAR) {
            if (char_exceeds_bounds) {
                last_glyph_max_x = 0.0;
                offset_y += line_height + _line_height;
            }
        }
        
        // compute glyph position
        ZVector position = {last_glyph_max_x + glyph.insets.left, line_height - glyph.insets.top + offset_y};
        last_glyph_max_x = position.x() + glyph.advance.width;
        glyph_node->set_position(position);
        
        // add to scene graph
        add_child(glyph_node);
        _glyph_nodes.push_back(glyph_node);
        ++char_idx;
    }
    
    _rendered_text = _text;
}

ZGE_END_NAMESPACE
