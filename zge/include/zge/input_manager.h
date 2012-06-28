/*
 * input_manager.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include "zge/schedulable_interface.h"
#include "zge/noncopyable.h"
#include <memory>

namespace zge {

typedef std::shared_ptr<class ZInputManager> ZInputManagerRef;

class ZInputManager : public ZSchedulableInterface, ZNonCopyable {
public:    
    void run(unsigned dtime) override;
};

} // namespace zge
