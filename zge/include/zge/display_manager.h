/*
 * display_manager.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/09/2012
 */
 
#pragma once

#include "zge/display.h"
#include "zge/noncopyable.h"
#include "zge/schedulable_interface.h"

#include <memory>

namespace zge {

enum ZRenderingAPIType {
    kSoftware,
    kOpenGL,
    kDirectX
};

typedef std::shared_ptr<class ZDisplayManager> ZDisplayManagerRef;

class ZDisplayManager : public ZSchedulableInterface, ZNonCopyable {
    ZDisplay *_currentDisplay;
    
public:
    ZDisplayManager();
    ~ZDisplayManager();
    
    /** Creating the Display **/
    ZDisplay* createDisplay(const ZDisplayMode &mode, ZRenderingAPIType api);
    ZDisplay* getCurrentDisplay() { return _currentDisplay; }
    
    /** Schedulable **/
    void run(unsigned dtime) override;
};

} // namespace zge
