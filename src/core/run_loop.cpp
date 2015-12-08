/*
 * run_loop.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#include <zge/run_loop.h>
#include <zge/util.h>
#include <algorithm>
#include <thread>
#include <SDL2/SDL.h>

#define FRAMES_PER_SECOND 60

ZGE_BEGIN_NAMESPACE

ZRunloop::ZRunloop() :
    _runloop(zrunloop_create()),
    _timer(nullptr),
    _on_main_thread(false),
    _running(false)
{}

ZRunloop::~ZRunloop()
{
    zrelease(_runloop);
    
    if (_timer) {
        zrelease(_timer);
    }
    
    _running = false;
}

#pragma mark - Accessors

bool ZRunloop::is_running() const { return _running; }
bool ZRunloop::is_on_main_thread() const { return _on_main_thread; }

#pragma mark - Starting the Run Loop

void ZRunloop::run()
{
    if (!_timer) {
        ZTimeInterval fps_interval(1.0 / (double)FRAMES_PER_SECOND);
        zcallbackfcn callback = [](void *context) {
            ZRunloop *rl = static_cast<ZRunloop *>(context);
            rl->_run();
        };
        _timer = ztimer_create(callback, this);
        ztimer_set_fire_time(_timer, zabsolutetime_get_current());
        ztimer_set_interval_ms(_timer, std::chrono::duration_cast<std::chrono::milliseconds>(fps_interval).count());
        ztimer_set_repeats(_timer, true);
        
        zrunloop_add_timer(_runloop, _timer);
    }
    
    _running = true;
    zrunloop_run(_runloop);
}

void ZRunloop::stop()
{
    _running = false;
    zrunloop_stop(_runloop);
}

#pragma mark - Managing schedulables in the Run Loop

void ZRunloop::schedule(ZSchedulableRef schedulable)
{
    std::lock_guard<std::mutex> lock(_mutex);
    
    schedulable->_run_loop = this;
    schedulable->on_schedule();
    
    _schedulables.push_back(schedulable);
}

void ZRunloop::unschedule(ZSchedulableRef schedulable)
{
    std::lock_guard<std::mutex> lock(_mutex);
    
    auto itr = std::find(_schedulables.begin(), _schedulables.end(), schedulable);
    if (itr != _schedulables.end()) {
        schedulable->on_unschedule();
        
        schedulable->_run_loop = nullptr;
        _schedulables.erase(itr);
    }
}

#pragma mark - Private Methods

void ZRunloop::_run()
{
    using namespace std::chrono;
    std::vector<ZSchedulableRef> schedulables;
    
    {
        std::lock_guard<std::mutex> lock(_mutex);
        schedulables = _schedulables;
    }
    
    for (ZSchedulableRef schedulable : schedulables) {
        ZTime time = ZUtil::get_current_time();
        ZTime last_update = schedulable->_last_update;
        ZTimeInterval dtime = time - last_update;
        uint32_t millseconds = (uint32_t)duration_cast<milliseconds>(dtime).count();
        
        schedulable->run(millseconds);
        schedulable->_last_update = time;
        
        if (schedulable->unschedule_after_run()) {
            unschedule(schedulable);
        }
    }
}

ZGE_END_NAMESPACE
