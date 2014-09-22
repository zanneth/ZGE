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

typedef std::function<float(float)> ZTimingFunction;

extern const ZTimingFunction ZLinearTimingFunction;

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
    
    ZTimingFunction get_timing_function() const;
    void set_timing_function(ZTimingFunction function);
    
    ZTime get_start_time() const;
    
    bool is_finished() const;
    void step(std::shared_ptr<ZNode> node);
    
    virtual void apply_progress(std::shared_ptr<ZNode> node, float normalized_progress) = 0;
    
public:
    static const uint64_t repeat_count_infinity;
    
protected:
    void _set_start_time(ZTime start_time);
    friend class ZNode;
    
    float _get_normalized_progress();
    
protected:
    ZTimeInterval   _duration;
    ZTimingFunction _timing_function;
    uint64_t        _repeat_count;
    uint64_t        _num_repeats;
    ZTime           _start_time;
    bool            _finished;
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
    
    void apply_progress(std::shared_ptr<ZNode> node, float normalized_progress) override;
    
private:
    ZVector _start;
    ZVector _end;
};

typedef std::shared_ptr<ZTranslationAction> ZTranslationActionRef;

// -----------------------------------------------------------------------------

class ZRotationAction : public ZAction {
public:
    ZRotationAction(float radians, ZVector axis = ZVector({0.0, 0.0, 1.0}));
    
    float get_radians() const;
    void set_radians(float radians);
    
    ZVector get_rotation_axis() const;
    void set_rotation_axis(const ZVector &axis);
    
    void apply_progress(std::shared_ptr<ZNode> node, float normalized_progress) override;
    
private:
    float _radians;
    ZVector _axis;
};

typedef std::shared_ptr<ZRotationAction> ZRotationActionRef;

END_ZGE_NAMESPACE
