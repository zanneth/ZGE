/*
 * material.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 12/30/2013
 */

#pragma once

#include <zge/core/foundation.h>
#include <zge/core/color.h>
#include <zge/renderer/render_context.h>
#include <zge/renderer/texture.h>

ZGE_BEGIN_NAMESPACE

class ZMaterial {
public:
    ZMaterial() = default;
    ZMaterial(const ZMaterial &cp) = default;
    ZMaterial(ZMaterial &&mv) = default;
    virtual ~ZMaterial();
    
    virtual std::string get_shader_name() const = 0;
    virtual const void* get_contents_data() const = 0;
    virtual void prepare_for_draw(ZRenderContextRef context);
    virtual void finalize_draw(ZRenderContextRef context);
};

ZGE_DEFINE_SREF_TYPE(ZMaterial);

class ZColorMaterial : public ZMaterial {
public:
    ZColorMaterial(const ZColor &col = ZColor::white);
    ZColorMaterial(const ZColorMaterial &cp) = default;
    ZColorMaterial(ZColorMaterial &&mv) = default;
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZColorMaterial);
    
    ZColor get_color() const;
    void set_color(const ZColor &color);
    
    // material overrides
    std::string get_shader_name() const override;
    const void* get_contents_data() const override;
    
private:
    ZColor _color;
};

ZGE_DEFINE_SREF_TYPE(ZColorMaterial);

class ZTextureMaterial : public ZMaterial {
public:
    ZTextureMaterial(ZTextureRef texture = nullptr);
    ZTextureMaterial(const ZTextureMaterial &cp) = default;
    ZTextureMaterial(ZTextureMaterial &&mv) = default;
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZTextureMaterial);
    
    ZTextureRef get_texture() const;
    void set_texture(ZTextureRef texture);
    
    // material overrides
    std::string get_shader_name() const override;
    const void* get_contents_data() const override;
    void prepare_for_draw(ZRenderContextRef context) override;
    void finalize_draw(ZRenderContextRef context) override;
    
private:
    ZTextureRef _texture;
    uint32_t _cached_texture_name;
};

ZGE_DEFINE_SREF_TYPE(ZTextureMaterial);

ZGE_END_NAMESPACE
