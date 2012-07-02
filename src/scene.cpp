/*
 * scene.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 04/20/2012
 */
 
#include "zge/scene.h"
#include "zge/logger.h"
#include "zge/vector.h"

#include <typeinfo>

namespace zge {

ZScene::ZScene() : ZNode(),
    _activeCamera(nullptr)
{
    _scene = this;
    setPosition(ZVec3(0.0, 0.0, 0.0));
}


#pragma mark - Node Overrides

void ZScene::addChild(ZNodeRef node)
{
    if (auto cam = std::dynamic_pointer_cast<ZCamera>(node)) {
        _activeCamera = cam;
        ZLogger::log("Camera 0x%x added to scene.", _activeCamera.get());
    }
    
    ZNode::addChild(node);
}

void ZScene::_drawInternal()
{
    if (_activeCamera.get() == nullptr) {
        return;
    }
    
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    
    _viewport.open();
    _activeCamera->open();
    
    ZNode::_drawInternal();
    
    _activeCamera->close();
    _viewport.close();
}

} // namespace zge

