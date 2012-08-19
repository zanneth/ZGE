/*
 * display_manager.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/09/2012
 */
 
#pragma once

#include "zge/noncopyable.h"
#include "zge/schedulable.h"

#include <memory>

namespace zge {

class ZDisplay;
struct ZDisplayMode;

typedef std::shared_ptr<class ZDisplayManager> ZDisplayManagerRef;

class ZDisplayManager : public ZSchedulable, ZNonCopyable {
    ZDisplay *_currentDisplay;
    
public:
    ZDisplayManager();
    ~ZDisplayManager();
    
    /** Creating the Display **/
    ZDisplay* createDisplay(const ZDisplayMode &mode);
    ZDisplay* getCurrentDisplay() { return _currentDisplay; }
    
    /** ZSchedulable **/
    void run(unsigned dtime) override;
};

} // namespace zge
