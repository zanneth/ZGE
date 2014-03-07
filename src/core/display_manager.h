/*
 * display_manager.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/09/2012
 */
 
#pragma once

#include <zge/defines.h>
#include <zge/display.h>
#include <zge/noncopyable.h>
#include <zge/schedulable.h>
#include <memory>

BEGIN_ZGE_NAMESPACE

class ZDisplayManager : public ZSchedulable, ZNoncopyable {
    ZDisplayRef _current_display;
    
public:
    ZDisplayManager();
    ~ZDisplayManager();
    
    /* Creating the Display */
    ZDisplayRef create_display(const ZDisplayMode &mode);
    ZDisplayRef get_current_display() { return _current_display; }
    
    /* schedulable */
    void run(uint32_t dtime) override;
};

typedef std::shared_ptr<ZDisplayManager> ZDisplayManagerRef;

END_ZGE_NAMESPACE
