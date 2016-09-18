/*
 * schedulable.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include <memory>
#include <zge/core/foundation.h>

ZGE_BEGIN_NAMESPACE

typedef std::shared_ptr<class ZSchedulable> ZSchedulableRef;
class ZRunloop;

class ZSchedulable {
public:
    ZSchedulable();
    virtual ~ZSchedulable() = default;
    
    // Run
    virtual void run(uint32_t dtime) = 0;
    
    // Callbacks from the runloop.
    virtual void on_schedule() {}
    virtual void on_unschedule() {}
    
    // Accessors
    bool unschedule_after_run() const;
    void set_unschedule_after_run(bool unschedule_after_run);
    
    friend class ZRunloop;
    
protected:
    bool  _unschedule_after_run;
    ZTime _last_update;
    ZRunloop *_run_loop = nullptr; // weak
};

// -----------------------------------------------------------------------------

class ZWorkSchedulable : public ZSchedulable, public std::enable_shared_from_this<ZWorkSchedulable> {
public:
    ZWorkSchedulable(std::function<void(uint32_t)> work);
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZWorkSchedulable);
    
    void run(uint32_t dtime) override;
    
private:
    std::function<void(uint32_t)> _work;
};

ZGE_DEFINE_SREF_TYPE(ZWorkSchedulable);

// -----------------------------------------------------------------------------

template<typename T>
class ZWeakSchedulable : public ZSchedulable {
public:
    ZWeakSchedulable(std::weak_ptr<T> weak);
    ZWeakSchedulable(std::shared_ptr<T> shared);
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZWeakSchedulable);
    
    void run(uint32_t dtime) override;
    
private:
    std::weak_ptr<T> _ref;
};

ZGE_END_NAMESPACE

#define __ZGE_ZSCHEDULABLE_IMPL_GUARD__
#include <zge/core/schedulable.hpp>
#undef __ZGE_ZSCHEDULABLE_IMPL_GUARD__
