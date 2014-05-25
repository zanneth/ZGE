/*
 * timer.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/06/2013
 */

#pragma once

#include <functional>
#include <memory>
#include <zge/defines.h>
#include <zge/noncopyable.h>
#include <zge/schedulable.h>
#include <zge/types.h>

BEGIN_ZGE_NAMESPACE

typedef std::shared_ptr<class ZTimer> ZTimerRef;
typedef std::function<void(ZTimerRef)> ZTimerFunction;
    
class ZTimer : public ZSchedulable, ZNoncopyable, public std::enable_shared_from_this<ZTimer> {
protected:
    ZTimerFunction _function;
    ZTimeInterval _interval;
    bool _repeats;
    
    uint32_t _time_scheduled;
    uint32_t _time_last_fired;
    
public:
    ZTimer(const ZTimerFunction &func = [](ZTimerRef){});
    virtual ~ZTimer();
    
    // Sets the function to be called when the timer fires.
    void set_function(const ZTimerFunction &function);
    
    // How often the timer should fire once scheduled.
    ZTimeInterval get_interval() const;
    void          set_interval(ZTimeInterval interval);
    
    // Whether the timer should repeat or not (default is false).
    bool repeats() const;
    void set_repeats(bool repeats);
    
    // Fires the timer.
    void fire();
    
    // Removes the timer from its runloop.
    void invalidate();
    
    /* Overrides */
    void run(uint32_t dtime) override;
    void on_schedule() override;
};

END_ZGE_NAMESPACE
