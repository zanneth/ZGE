/*
 * runnable_interface.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include <memory>

namespace zge {

typedef std::shared_ptr<class ZRunnableInterface> ZRunnableInterfaceRef;

class ZRunnableInterface {
    unsigned _lastUpdate;
    
public:
    virtual ~ZRunnableInterface() {}
    virtual void run(unsigned dtime) = 0;
    
    friend class ZRunLoop;
};

} // namespace zge
