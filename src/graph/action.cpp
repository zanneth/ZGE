/*
 * action.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/24/2014
 */

#include <zge/action.h>
#include <zge/node.h>
#include <cfloat>
#include <cmath>

BEGIN_ZGE_NAMESPACE

ZAction::ZAction() :
    _duration(0.0)
{}

#pragma mark - Accessors

ZTimeInterval ZAction::get_duration() const { return _duration; }
void ZAction::set_duration(ZTimeInterval duration) { _duration = duration; }
ZTime ZAction::get_start_time() const { return _start_time; }

#pragma mark - Private

void ZAction::_set_start_time(ZTime start_time)
{
    _start_time = start_time;
}

#pragma mark - ZTranslationAction

ZTranslationAction::ZTranslationAction(const ZVector &start, const ZVector &end) :
    _start(start),
    _end(end),
    _finished(false)
{}

#pragma mark - Accessors

ZVector ZTranslationAction::get_start_position() const { return _start; }
void ZTranslationAction::set_start_position(const ZVector &start) { _start = start; }
ZVector ZTranslationAction::get_end_position() const { return _end; }
void ZTranslationAction::set_end_position(const ZVector &end) { _end = end; }

bool ZTranslationAction::is_finished() const
{
    return _finished;
}

void ZTranslationAction::step(std::shared_ptr<ZNode> node)
{
    using namespace std::chrono;
    
    microseconds duration = duration_cast<microseconds>(get_duration());
    ZTime start_time = get_start_time();
    ZTime curtime = ZUtil::get_current_time();
    microseconds elapsed = duration_cast<microseconds>(curtime - start_time);
    float progress = (float)(elapsed.count()) / (float)(duration.count());
    
    ZVector newpos = _start * (1.0 - progress) + _end * progress;
    node->set_position(newpos);
    
    if (progress >= 1.0) {
        _finished = true;
    }
}

END_ZGE_NAMESPACE
