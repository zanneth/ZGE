/*
 * material.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 12/30/2013
 */

#pragma once

#include <zge/color.h>
#include <zge/noncopyable.h>
#include <memory>

namespace zge {

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
    ZMaterialProperty<ZColor>* get_color();
    
private:
    ZMaterialProperty<ZColor> _color;
};

typedef std::shared_ptr<ZMaterial> ZMaterialRef;

} // namespace zge

#include <zge/material.hpp>
