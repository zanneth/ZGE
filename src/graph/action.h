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
    
    ZTime get_start_time() const;
    
    virtual bool is_finished() const = 0;
    virtual void step(std::shared_ptr<ZNode> node) = 0;
    
protected:
    void _set_start_time(ZTime start_time);
    friend class ZNode;
    
private:
    ZTimeInterval _duration;
    ZTime         _start_time;
};

typedef std::shared_ptr<ZAction> ZActionRef;

// -----------------------------------------------------------------------------

class ZTranslationAction : public ZAction {
public:
    ZTranslationAction(const ZVector &start = ZVecZero, const ZVector &end = ZVecZero);
    
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

END_ZGE_NAMESPACE
