/*
 * action.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/24/2014
 */

#include <zge/graph/action.h>
#include <zge/graph/node.h>
#include <cfloat>
#include <cmath>

ZGE_BEGIN_NAMESPACE

static float __linear_timing_function(float time);

extern const ZTimingFunction ZLinearTimingFunction(__linear_timing_function);

const uint64_t ZAction::repeat_count_infinity = -1;

ZAction::ZAction() :
    _duration(0.0),
    _timing_function(ZLinearTimingFunction),
    _repeat_count(0),
    _num_repeats(0),
    _finished(false)
{}

#pragma mark - Accessors

ZTimeInterval ZAction::get_duration() const { return _duration; }
void ZAction::set_duration(ZTimeInterval duration) { _duration = duration; }
uint64_t ZAction::get_repeat_count() const { return _repeat_count; }
void ZAction::set_repeat_count(uint64_t repeat_count) { _repeat_count = repeat_count; }
ZTimingFunction ZAction::get_timing_function() const { return _timing_function; }
void ZAction::set_timing_function(ZTimingFunction function) { _timing_function = function; }
ZTime ZAction::get_start_time() const { return _start_time; }
bool ZAction::is_finished() const { return _finished; }

#pragma mark - API

void ZAction::step(std::shared_ptr<ZNode> node)
{
    float progress = _timing_function(_get_normalized_progress());
    
    apply_progress(node, progress);
    
    if (progress >= 1.0) {
        if (_repeat_count != ZAction::repeat_count_infinity && _num_repeats >= _repeat_count) {
            _finished = true;
        } else {
            ++_num_repeats;
        }
    }
}

#pragma mark - Private

void ZAction::_set_start_time(ZTime start_time)
{
    _start_time = start_time;
}

float ZAction::_get_normalized_progress()
{
    using namespace std::chrono;
    
    microseconds duration = duration_cast<microseconds>(get_duration());
    ZTime start_time = get_start_time();
    ZTime curtime = ZUtil::get_current_time();
    microseconds elapsed = duration_cast<microseconds>(curtime - start_time);
    float progress = (float)(elapsed.count() - (duration.count() * _num_repeats)) / (float)(duration.count());
    
    return progress;
}

#pragma mark - ZTranslationAction

ZTranslationAction::ZTranslationAction(const ZVector &start, const ZVector &end) :
    _start(start),
    _end(end)
{}

#pragma mark - Accessors

ZVector ZTranslationAction::get_start_position() const { return _start; }
void ZTranslationAction::set_start_position(const ZVector &start) { _start = start; }
ZVector ZTranslationAction::get_end_position() const { return _end; }
void ZTranslationAction::set_end_position(const ZVector &end) { _end = end; }

void ZTranslationAction::apply_progress(std::shared_ptr<ZNode> node, float progress)
{
    ZVector newpos = _start * (1.0 - progress) + _end * progress;
    node->set_position(newpos);
}

#pragma mark - ZRotationAction

ZRotationAction::ZRotationAction(float radians, ZVector axis) :
    _radians(radians),
    _axis(axis),
    _anchor_point(ZVector::zero)
{}

float ZRotationAction::get_radians() const { return _radians; }
void ZRotationAction::set_radians(float radians) { _radians = radians; }
ZVector ZRotationAction::get_rotation_axis() const { return _axis; }
void ZRotationAction::set_rotation_axis(const ZVector &axis) { _axis = axis; }
ZVector ZRotationAction::get_anchor_point() const { return _anchor_point; }
void ZRotationAction::set_anchor_point(const ZVector &anchor_point) { _anchor_point = anchor_point; }

void ZRotationAction::apply_progress(std::shared_ptr<ZNode> node, float normalized_progress)
{
    float new_radians = normalized_progress * _radians;
    ZMatrix transform(ZMatrix::identity());
    
    if (_anchor_point == ZVector::zero) {
        transform = ZMatrix::rotation(new_radians, _axis.x(), _axis.y(), _axis.z());
    } else {
        transform = transform.translate(_anchor_point)
                             .rotate(new_radians, _axis.x(), _axis.y(), _axis.z())
                             .translate(-_anchor_point);
    }
    
    node->set_transform(transform);
}

#pragma mark - Timing Functions

float __linear_timing_function(float time)
{
    return time;
}

ZGE_END_NAMESPACE
