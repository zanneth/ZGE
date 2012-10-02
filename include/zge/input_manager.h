/*
 * input_manager.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include "zge/schedulable.h"
#include "zge/noncopyable.h"

namespace zge {

typedef std::shared_ptr<class ZInputManager> ZInputManagerRef;

class ZInputManager : public ZSchedulable, ZNoncopyable {
public:    
    void run(unsigned dtime) override;
};

} // namespace zge
