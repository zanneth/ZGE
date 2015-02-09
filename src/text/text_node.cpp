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

ZGE_BEGIN_NAMESPACE

ZTextNode::ZTextNode(const std::wstring &text, ZFontRef font) :
    _text(text),
    _font(font),
    _text_color(ZColor::white)
{
    _render_glyphs();
}

ZTextNode::ZTextNode(const std::string &text, ZFontRef font) :
    _font(font),
    _text_color(ZColor::white)
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
    _render_glyphs();
}

void ZTextNode::set_text_color(const ZColor &color)
{
    _text_color = color;
    _render_glyphs();
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
    set_position(bounds.origin);
}

#pragma mark - Internal

void ZTextNode::_render_glyphs()
{
    if (!_font || _rendered_text == _text) {
        return;
    }
    
    remove_all_children();
    _glyph_nodes.clear();
    
    // create glyphs using provided font
    std::vector<ZGlyph> glyphs;
    for (const auto &character : _text) {
        ZGlyph glyph = _font->create_glyph(character);
        glyphs.push_back(glyph);
    }
    
    // create textures and nodes for glyph
    const size_t bytes_per_pixel = 4;
    const ZImageFormat format = {
        .bytes_per_pixel = bytes_per_pixel,
        .pixel_format = ZPIXEL_FORMAT_RGBA
    };
    
    const float line_height = _font->get_line_height();
    float last_glyph_max_x = 0.0;
    
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
        
        ZImageRef texture_image = std::make_shared<ZImage>(dst_pixbuf_data, glyph.size, format);
        ZTextureRef texture = std::make_shared<ZTexture>(texture_image);
        ZSpriteNodeRef glyph_node = std::make_shared<ZSpriteNode>(texture);
        glyph_node->set_size(glyph.size);
        glyph_node->set_color(_text_color);
        
        ZVector position = {last_glyph_max_x + glyph.insets.left, line_height - glyph.insets.top};
        last_glyph_max_x = position.x() + glyph.advance.width;
        glyph_node->set_position(position);
        
        add_child(glyph_node);
        _glyph_nodes.push_back(glyph_node);
    }
    
    _rendered_text = _text;
}

ZGE_END_NAMESPACE
