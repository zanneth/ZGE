/*
 * scene.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 04/20/2012
 */
 
#pragma once

#include "zge/node.h"

namespace zge {

typedef ZNodeRef ZSceneRef;

class ZScene : public ZNode {
public:
    ZScene();
};

} // namespace zge

