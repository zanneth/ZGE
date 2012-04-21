/*
 * display_manager.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/09/2012
 */
 
#pragma once

#include "zge/runnable_interface.h"
#include "zge/display.h"
#include "zge/noncopyable.h"
#include <memory>

namespace zge {

enum ZRenderingAPIType {
    kSoftware,
    kOpenGL,
    kDirectX
};

typedef std::shared_ptr<class ZDisplayManager> ZDisplayManagerRef;

class ZDisplayManager : public ZRunnableInterface, ZNonCopyable {
    ZDisplay *_currentDisplay;
    
public:
    ZDisplayManager();
    ~ZDisplayManager();
    
    /** Creating the Display **/
    ZDisplay* createDisplay(const ZDisplayMode &mode, ZRenderingAPIType api);
    ZDisplay* getCurrentDisplay() const { return _currentDisplay; }
    
    /** Runnable **/
    void run(unsigned dtime) override;
};

} // namespace zge
