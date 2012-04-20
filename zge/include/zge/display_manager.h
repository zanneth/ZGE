/*
 * display_manager.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/09/2012
 */
 
#pragma once

#include "zge/runnable_interface.h"
#include "zge/display.h"
#include <memory>

namespace zge {

typedef std::shared_ptr<class ZDisplayManager> ZDisplayManagerRef;

class ZDisplayManager : public ZRunnableInterface {
    ZDisplayRef _currentDisplay;
    
public:
    /** Accessors **/
    ZDisplayRef getCurrentDisplay() const { return _currentDisplay; }
    void setCurrentDisplay(ZDisplayRef display);
    
    
    /** Runnable **/
    void run(unsigned dtime) override;
};

} // namespace zge
