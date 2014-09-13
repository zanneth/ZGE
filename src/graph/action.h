/*
 * action.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/24/2014
 */

#pragma once

#include <zge/foundation.h>
#include <zge/vector.h>

BEGIN_ZGE_NAMESPACE

class ZNode;

class ZAction {
public:
    ZAction();
    ZAction(const ZAction &cp) = default;
    ZAction(ZAction &&mv) = default;
    virtual ~ZAction() = default;
    
    ZTimeInterval get_duration() const;
    void set_duration(ZTimeInterval duration);
    
    uint64_t get_repeat_count() const;
    void set_repeat_count(uint64_t repeat_count);
    
    ZTime get_start_time() const;
    
    virtual bool is_finished() const = 0;
    virtual void step(std::shared_ptr<ZNode> node) = 0;
    
public:
    static const uint64_t repeat_count_infinity;
    
protected:
    void _set_start_time(ZTime start_time);
    friend class ZNode;
    
protected:
    ZTimeInterval _duration;
    uint64_t      _repeat_count;
    uint64_t      _num_repeats;
    ZTime         _start_time;
};

typedef std::shared_ptr<ZAction> ZActionRef;

// -----------------------------------------------------------------------------

class ZTranslationAction : public ZAction {
public:
    ZTranslationAction(const ZVector &start = ZVector::zero, const ZVector &end = ZVector::zero);
    
    ZVector get_start_position() const;
    void set_start_position(const ZVector &start);
    
    ZVector get_end_position() const;
    void set_end_position(const ZVector &end);
    
    bool is_finished() const override;
    void step(std::shared_ptr<ZNode> node) override;
    
private:
    ZVector _start;
    ZVector _end;
    bool    _finished;
};

typedef std::shared_ptr<ZTranslationAction> ZTranslationActionRef;

END_ZGE_NAMESPACE
