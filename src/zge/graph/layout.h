/*
 * layout.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/05/2015
 */

#pragma once

#include <zge/core/foundation.h>
#include <zge/math/vector.h>

ZGE_BEGIN_NAMESPACE

class ZLayoutComponent {
public:
    virtual ~ZLayoutComponent();
    
    virtual ZRect get_bounds() const = 0;
    virtual void  set_bounds(const ZRect &bounds) = 0;
};

ZGE_DEFINE_SREF_TYPE(ZLayoutComponent);

class ZLayout {
public:
    ZLayout();
    virtual ~ZLayout();
    
    std::vector<ZLayoutComponentRef> get_components() const;
    void add_component(ZLayoutComponentRef component);
    void remove_component(ZLayoutComponentRef component);
    void clear_components();
    
    virtual void layout_components() = 0;
    
protected:
    std::vector<ZLayoutComponentRef> _components;
};

ZGE_DEFINE_SREF_TYPE(ZLayout);

ZGE_END_NAMESPACE
