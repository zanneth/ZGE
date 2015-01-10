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

ZScene::ZScene() :
    _update_reentr(false)
{
    _scene = this;
    set_position({0.0, 0.0, 0.0});
}

ZScene::~ZScene()
{
    _evict_scene(this);
}

void ZScene::update()
{
    if (!_update_reentr) {
        _update_reentr = true;
        _update_internal();
        _update_reentr = false;
    }
}

void ZScene::draw(ZRenderContextRef context)
{
    if (context) {
        context->make_current();
        _draw(context);
    }
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
