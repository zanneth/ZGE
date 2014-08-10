/*
 * node.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#include <zge/node.h>
#include <zge/logger.h>
#include <zge/util.h>
#include <algorithm>
#include <unordered_set>
#include <sstream>
#include <typeinfo>

static unsigned __node_global_uid_count = 1;

BEGIN_ZGE_NAMESPACE

ZNode::ZNode(ZGeometryRef geometry) :
    _uid(__node_global_uid_count++),
    _position({ 0.0, 0.0, 0.0 }),
    _transform(ZMatrix::identity()),
    _parent(nullptr),
    _scene(nullptr),
    _pos_transform(ZMatrix::identity()),
    _geometry(geometry.get() ? geometry->copy() : nullptr) // copy geometry
{}

ZNode::~ZNode()
{
#if (ZDEBUG)
    ZLogger::log("%s destroyed", get_description().c_str());
#endif
}

#pragma mark - Operators

bool ZNode::operator==(const ZNode &other)
{
    return _uid == other._uid;
}

bool ZNode::operator!=(const ZNode &other)
{
    return !operator==(other);
}

#pragma mark - Accessors

ZNode* ZNode::get_parent() { return _parent; }
ZScene* ZNode::get_scene() { return _scene; }
std::string ZNode::get_name() const { return _name; }
void ZNode::set_name(const std::string &name) { _name = name; }
ZVector ZNode::get_position() const { return _position; }
ZMatrix ZNode::get_transform() const { return _transform; }
void ZNode::set_transform(const ZMatrix &transform) { _transform = transform; }
ZGeometryRef ZNode::get_geometry() const { return _geometry; }
void ZNode::set_geometry(ZGeometryRef geometry) { _geometry = geometry; }
std::vector<ZNodeRef> ZNode::get_children() { return _children; }

void ZNode::set_position(const ZVector &position)
{
    _position = position;
    _pos_transform = ZMatrix::translation(position.get_x(), position.get_y(), position.get_z());
}

#pragma mark - Manipulating Geometry

void ZNode::append_transform(const ZMatrix &transform)
{
    _transform *= transform;
}

#pragma mark - Managing Children

void ZNode::add_child(ZNodeRef node)
{
    node->_scene  = _scene;
    node->_parent = this;
    
    _children.push_back(node);
    node->_on_enter_internal();
}

bool ZNode::remove_child(ZNodeRef node)
{
    for (auto itr = _children.begin(); itr != _children.end(); ++itr) {
        if (**itr == *node) {
            node->_scene    = nullptr;
            node->_parent   = nullptr;
            
            _children.erase(itr);
            node->_on_exit_internal();
            
            return true;
        }
    }
    
    return false;
}

void ZNode::remove_from_parent()
{
    if (_parent != nullptr) {
        _parent->_remove_child_uid(_uid);
    }
}

#pragma mark - Actions

void ZNode::add_action(ZActionRef action)
{
    _actions.push_back(action);
    action->_set_start_time(ZUtil::get_current_time());
}

void ZNode::remove_action(ZActionRef action)
{
    auto rmaction = std::find(_actions.begin(), _actions.end(), action);
    if (rmaction != _actions.end()) {
        _actions.erase(rmaction);
    } else {
        zlog("Could not find action %p in node %s", action.get(), get_description().c_str());
    }
}

void ZNode::remove_all_actions()
{
    _actions.clear();
}

#pragma mark - Description

std::string ZNode::get_description()
{
    std::string description = ZUtil::format("<ZNode %p #%u \"%s\">", this, _uid, _name.c_str());
    return description;
}

#pragma mark - Private

void ZNode::_draw(ZRenderContextRef context)
{
    context->push_matrix(ZRENDER_MATRIX_MODELVIEW, (_pos_transform * _transform));
    
    for (ZNodeRef child : _children) {
        child->_draw(context);
    }
    
    if (_geometry.get()) {
        _geometry->prepare_render(context);
        _geometry->render(context);
        _geometry->finalize_render(context);
    }
    
    context->pop_matrix(ZRENDER_MATRIX_MODELVIEW);
}

void ZNode::_update_internal()
{
    // update children
    for (ZNodeRef child : _children) {
        child->_update_internal();
    }
    
    // update callback
    update();
    
    // step actions
    ZNodeRef selfptr = shared_from_this();
    for (ZActionRef action : _actions) {
        if (!action->is_finished()) {
            action->step(selfptr);
        }
    }
    
    // remove completed actions
    auto new_end = std::remove_if(_actions.begin(), _actions.end(), [](const ZActionRef &action) {
        bool finished = action->is_finished();
        if (finished) {
            zlog("Removing completed action %p", action.get());
        }
        return finished;
    });
    _actions.erase(new_end, _actions.end());
}

void ZNode::_remove_child_uid(unsigned uid)
{
    auto child = std::find_if(_children.begin(), _children.end(), [uid](ZNodeRef child) { return child->_uid == uid; });
    if (child != _children.end()) {
        ZNodeRef node = *child;
        node->_scene  = nullptr;
        node->_parent = nullptr;

        _children.erase(child);
        node->_on_exit_internal();
   }
}

void ZNode::_on_enter_internal()
{
    on_enter();
    
    for (ZNodeRef child : _children) {
        child->_on_enter_internal();
    }
}

void ZNode::_on_exit_internal()
{
    on_exit();
    
    for (ZNodeRef child : _children) {
        child->_on_exit_internal();
    }
}

END_ZGE_NAMESPACE
