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
    
    T get_contents() const;
    void set_contents(const T &contents);
    
    std::string get_name() const;
    
    bool is_dirty() const;
    void clear_dirty();
    
private:
    T _contents;
    std::string _name;
    bool _dirty;
};

class ZMaterial : ZNoncopyable {
public:
    ZMaterial();
    ~ZMaterial();
    
    // returns true if any of the material properties are dirty.
    bool is_dirty() const;
    void clear_dirty();
    
    // these properties are mutable
    ZMaterialProperty<ZColor>* get_ambient();
    
private:
    ZMaterialProperty<ZColor> _ambient;
};

typedef std::shared_ptr<ZMaterial> ZMaterialRef;

} // namespace zge

#include <zge/material.hpp>
