/*
 * box_layout.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/05/2015
 */

#include "box_layout.h"
#include <algorithm>
#include <cmath>

ZGE_BEGIN_NAMESPACE

ZBoxLayout::ZBoxLayout(ZLayoutComponentRef target, ZBoxLayoutAxis axis) :
    _target(target),
    _axis(axis),
    _alignment(ZBOX_LAYOUT_ALIGNMENT_CENTER)
{}

#pragma mark - Accessors

ZLayoutComponentRef ZBoxLayout::get_target() const { return _target; }
void ZBoxLayout::set_target(ZLayoutComponentRef target) { _target = target; }
ZBoxLayoutAxis ZBoxLayout::get_axis() const { return _axis; }
void ZBoxLayout::set_axis(ZBoxLayoutAxis axis) { _axis = axis; }
ZBoxLayoutAlignment ZBoxLayout::get_alignment() const { return _alignment; }
void ZBoxLayout::set_alignment(ZBoxLayoutAlignment alignment) { _alignment = alignment; }

#pragma mark - Layout

void ZBoxLayout::layout_components()
{
    if (!_target) {
        return;
    }
    
    std::vector<ZLayoutComponentRef> components = get_components();
    const size_t components_count = components.size();
    const ZRect target_bounds = _target->get_bounds();
    const float target_axis_size = (_axis == ZBOX_LAYOUT_AXIS_X ? target_bounds.size.width : target_bounds.size.height);
    
    // calculate the padding for each element
    float total_cmps_size = 0.0;
    for (ZLayoutComponentRef component : components) {
        ZSize2D cmp_size = component->get_bounds().size;
        total_cmps_size += (_axis == ZBOX_LAYOUT_AXIS_X ? cmp_size.width : cmp_size.height);
    }
    const float empty_space = std::abs(target_axis_size - total_cmps_size);
    const float padding = std::rint(empty_space / float(components_count > 0 ? components_count - 1 : 1));
    
    float cur_axis_pos = 0.0;
    unsigned component_idx = 0;
    for (ZLayoutComponentRef component : components) {
        ZRect bounds = component->get_bounds();
        float axis_size = (_axis == ZBOX_LAYOUT_AXIS_X ? bounds.size.width : bounds.size.height);
        float non_axis_size = (_axis == ZBOX_LAYOUT_AXIS_X ? bounds.size.height : bounds.size.width);
        float non_axis_pos = _compute_nonaxis_position(non_axis_size);
        
        if (_axis == ZBOX_LAYOUT_AXIS_X) {
            bounds.origin.x = cur_axis_pos;
            bounds.origin.y = non_axis_pos;
        } else if (_axis == ZBOX_LAYOUT_AXIS_Y) {
            bounds.origin.x = non_axis_pos;
            bounds.origin.y = cur_axis_pos;
        }
        
        component->set_bounds(bounds);
        
        cur_axis_pos += axis_size + padding;
        ++component_idx;
    }
}

#pragma mark - Internal

float ZBoxLayout::_compute_nonaxis_position(float nonaxis_component_size)
{
    const ZRect target_bounds = _target->get_bounds();
    const float target_non_axis_size = (_axis == ZBOX_LAYOUT_AXIS_X ? target_bounds.size.height : target_bounds.size.width);
    float pos = 0.0;
    
    switch (_alignment) {
        case ZBOX_LAYOUT_ALIGNMENT_LEFT:
        case ZBOX_LAYOUT_ALIGNMENT_TOP:
            pos = 0.0;
            break;
        case ZBOX_LAYOUT_ALIGNMENT_RIGHT:
        case ZBOX_LAYOUT_ALIGNMENT_BOTTOM:
            pos = target_non_axis_size - nonaxis_component_size;
            break;
        case ZBOX_LAYOUT_ALIGNMENT_CENTER:
            pos = std::rint(target_non_axis_size / 2.0 - nonaxis_component_size / 2.0);
            break;
        default:
            break;
    }
    
    return pos;
}

ZGE_END_NAMESPACE
