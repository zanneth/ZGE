/*
 * box_layout.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/05/2015
 */

#pragma once

#include <zge/foundation.h>
#include <zge/layout.h>

ZGE_BEGIN_NAMESPACE

enum ZBoxLayoutAxis {
    ZBOX_LAYOUT_AXIS_X,
    ZBOX_LAYOUT_AXIS_Y
};

enum ZBoxLayoutAlignment {
    ZBOX_LAYOUT_ALIGNMENT_LEFT,
    ZBOX_LAYOUT_ALIGNMENT_RIGHT,
    ZBOX_LAYOUT_ALIGNMENT_TOP,
    ZBOX_LAYOUT_ALIGNMENT_BOTTOM,
    ZBOX_LAYOUT_ALIGNMENT_CENTER,
};

class ZBoxLayout : public ZLayout {
public:
    ZBoxLayout(ZLayoutComponentRef target, ZBoxLayoutAxis axis);
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZBoxLayout);
    
    ZLayoutComponentRef get_target() const;
    void set_target(ZLayoutComponentRef target);
    
    ZBoxLayoutAxis get_axis() const;
    void set_axis(ZBoxLayoutAxis axis);
    
    ZBoxLayoutAlignment get_alignment() const;
    void set_alignment(ZBoxLayoutAlignment alignment);
    
    void layout_components() override;
    
private:
    float _compute_nonaxis_position(float nonaxis_component_size);
    
private:
    ZLayoutComponentRef _target;
    ZBoxLayoutAxis      _axis;
    ZBoxLayoutAlignment _alignment;
};

ZGE_DEFINE_SREF_TYPE(ZBoxLayout);

ZGE_END_NAMESPACE
