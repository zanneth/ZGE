/*
 * material.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 12/30/2013
 */

#pragma once

#include <zge/color.h>
#include <zge/defines.h>
#include <zge/noncopyable.h>
#include <memory>

BEGIN_ZGE_NAMESPACE

template <typename T>
class ZMaterialProperty {
public:
    ZMaterialProperty(std::string name);
    ZMaterialProperty(const ZMaterialProperty &cp);
    ZMaterialProperty(ZMaterialProperty &&mv);
    ~ZMaterialProperty();
    
    T get_contents() const;
    void set_contents(const T &contents);
    
    std::string get_name() const;
    
private:
    T _contents;
    std::string _name;
};

class ZMaterial {
public:
    ZMaterial();
    ZMaterial(const ZMaterial &cp) = default;
    ZMaterial(ZMaterial &&mv) = default;
    ~ZMaterial();
    
    // these properties are mutable
    const ZMaterialProperty<ZColor>& get_color() const;
    void set_color(const ZColor &color);
    
private:
    ZMaterialProperty<ZColor> _color;
};

typedef std::shared_ptr<ZMaterial> ZMaterialRef;

END_ZGE_NAMESPACE

#include <zge/material.hpp>
