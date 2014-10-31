/*
 * scene.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 04/20/2012
 */
 
#include <zge/scene.h>
#include <zge/light.h>
#include <zge/logger.h>
#include <typeinfo>

ZGE_BEGIN_NAMESPACE

ZScene::ZScene() : ZNode()
{
    _scene = this;
    set_position({0.0, 0.0, 0.0});
}

ZScene::~ZScene()
{
    _evict_scene(this);
}

#pragma mark - Private

void ZScene::_evict_scene(ZNode *curnode)
{
    curnode->_scene = nullptr;
    for (ZNodeRef node : curnode->_children) {
        _evict_scene(node.get());
    }
}

ZGE_END_NAMESPACE
