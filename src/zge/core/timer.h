/*
 * timer.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/06/2013
 */

#pragma once

#include <functional>
#include <memory>
#include <zge/core/defines.h>
#include <zge/core/noncopyable.h>
#include <zge/core/schedulable.h>
#include <zge/core/types.h>

ZGE_BEGIN_NAMESPACE

ZGE_FORWARD_DECLARE_SREF(ZTimer);
typedef std::function<void(ZTimerRef)> ZTimerFunction;

class ZTimer : public ZSchedulable, ZNoncopyable, public std::enable_shared_from_this<ZTimer> {
public:
    ZTimer(const ZTimerFunction &func = [](ZTimerRef){});
    virtual ~ZTimer();
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZTimer);
    
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
    
private:
    ZTimerFunction _function;
    ZTimeInterval  _interval;
    ZTime          _time_scheduled;
    ZTime          _time_last_fired;
    bool           _repeats;
    bool           _valid;
};

ZGE_DEFINE_SREF_TYPE(ZTimer);

ZGE_END_NAMESPACE
