/*
 * display_manager.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/09/2012
 */
 
#pragma once

#include <zge/noncopyable.h>
#include <zge/schedulable.h>
#include <memory>

namespace zge {

class ZDisplay;
struct ZDisplayMode;

typedef std::shared_ptr<class ZDisplayManager> ZDisplayManagerRef;

class ZDisplayManager : public ZSchedulable, ZNoncopyable {
    ZDisplay *_current_display;
    
public:
    ZDisplayManager();
    ~ZDisplayManager();
    
    /** Creating the Display **/
    ZDisplay* create_display(const ZDisplayMode &mode);
    ZDisplay* get_current_display() { return _current_display; }
    
    /** schedulable **/
    void run(uint32_t dtime) override;
};

} // namespace zge
