/*
 * mesh_node.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/19/2013
 */

#include <zge/mesh_node.h>

namespace zge {

ZMeshNode::ZMeshNode(ZModelRef model) :
    _model(model)
{}

ZMeshNode::~ZMeshNode()
{}

void ZMeshNode::draw(ZRenderContextRef context)
{
    if (_model != nullptr) {
        _model->draw();
    }
}

} // namespace zge
