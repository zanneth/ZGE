/*
 * game_manager.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include "zge/runnable_interface.h"
#include <memory>

namespace zge {

typedef std::shared_ptr<class ZGameManager> ZGameManagerRef;

class ZGameManager : public ZRunnableInterface {
    
public:
    // TODO
};

} // namespace zge
