/*
 * schedulable.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include <memory>
#include <zge/foundation.h>

BEGIN_ZGE_NAMESPACE

typedef std::shared_ptr<class ZSchedulable> ZSchedulableRef;
class ZRunloop;

class ZSchedulable {
protected:
    ZTime _last_update;
    ZRunloop *_run_loop = nullptr; // weak
    
public:
    virtual ~ZSchedulable() {}
    virtual void run(uint32_t dtime) = 0;
    
    // Callbacks from the runloop.
    virtual void on_schedule() {}
    virtual void on_unschedule() {}
    
    friend class ZRunloop;
};

class ZWorkSchedulable : public ZSchedulable, public std::enable_shared_from_this<ZWorkSchedulable> {
public:
    ZWorkSchedulable(std::function<void()> work);
    void run(uint32_t dtime) override;
    
private:
    std::function<void()> _work;
};

template<typename T>
class ZWeakSchedulable : public ZSchedulable {
public:
    ZWeakSchedulable(std::weak_ptr<T> weak);
    ZWeakSchedulable(std::shared_ptr<T> shared);
    
    void run(uint32_t dtime) override;
    
private:
    std::weak_ptr<T> _ref;
};

END_ZGE_NAMESPACE

#define __ZGE_ZSCHEDULABLE_IMPL_GUARD__
#include <zge/schedulable.hpp>
#undef __ZGE_ZSCHEDULABLE_IMPL_GUARD__
