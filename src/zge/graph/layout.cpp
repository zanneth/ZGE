/*
 * layout.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/05/2015
 */

#include "layout.h"
#include <algorithm>

ZGE_BEGIN_NAMESPACE

#pragma mark - ZLayoutComponent

ZLayoutComponent::~ZLayoutComponent()
{}

#pragma mark - ZLayout

ZLayout::ZLayout()
{}

ZLayout::~ZLayout()
{}

std::vector<ZLayoutComponentRef> ZLayout::get_components() const
{
    return _components;
}

void ZLayout::add_component(ZLayoutComponentRef component)
{
    _components.push_back(component);
}

void ZLayout::remove_component(ZLayoutComponentRef component)
{
    auto itr = std::find(_components.begin(), _components.end(), component);
    if (itr != _components.end()) {
        _components.erase(itr);
    }
}

void ZLayout::clear_components()
{
    _components.clear();
}

void ZLayout::layout_components()
{}

ZGE_END_NAMESPACE
