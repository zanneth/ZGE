/*
 * material.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 12/30/2013
 */

#pragma once

#include <zge/foundation.h>
#include <zge/color.h>
#include <zge/render_context.h>
#include <zge/texture.h>

BEGIN_ZGE_NAMESPACE

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

typedef std::shared_ptr<ZMaterial> ZMaterialRef;

class ZColorMaterial : public ZMaterial {
public:
    ZColorMaterial();
    ZColorMaterial(const ZColorMaterial &cp) = default;
    ZColorMaterial(ZColorMaterial &&mv) = default;
    
    ZColor get_color() const;
    void set_color(const ZColor &color);
    
    // material overrides
    std::string get_shader_name() const override;
    const void* get_contents_data() const override;
    
private:
    ZColor _color;
};

typedef std::shared_ptr<ZColorMaterial> ZColorMaterialRef;

class ZTextureMaterial : public ZMaterial {
public:
    ZTextureMaterial();
    ZTextureMaterial(const ZTextureMaterial &cp) = default;
    ZTextureMaterial(ZTextureMaterial &&mv) = default;
    
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

typedef std::shared_ptr<ZTextureMaterial> ZTextureMaterialRef;

END_ZGE_NAMESPACE
