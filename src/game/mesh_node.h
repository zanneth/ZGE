/*
 * mesh_node.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/19/2013
 */

#pragma once

#include <memory>
#include <zge/model.h>
#include <zge/node.h>
#include <zge/render_context.h>

namespace zge {

class ZMeshNode : public ZNode {
protected:
    ZModelRef _model;
    
public:
    ZMeshNode(ZModelRef model = nullptr);
    virtual ~ZMeshNode();
    
    /* Node Overrides */
    void draw(ZRenderContextRef context) override;
};

typedef std::shared_ptr<ZMeshNode> ZMeshNodeRef;

} // namespace zge
