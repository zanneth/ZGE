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
    _running(false)
{}

ZRunloop::~ZRunloop()
{
    _running = false;
}

#pragma mark - Starting the Run Loop

void ZRunloop::run()
{
    _running = true;
    _main();
}

void ZRunloop::stop()
{
    _running = false;
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

void ZRunloop::_main()
{
    using namespace std::chrono;
    static const ZTimeInterval __fps_interval(1.0 / (double)FRAMES_PER_SECOND);
    
    while (_running) {
        std::vector<ZSchedulableRef> schedulables;
        
        {
            std::lock_guard<std::mutex> lock(_mutex);
            schedulables = _schedulables;
        }
        
        ZTime loop_start_time = ZUtil::get_current_time();
        
        for (ZSchedulableRef schedulable : schedulables) {
            ZTime time = ZUtil::get_current_time();
            ZTime last_update = schedulable->_last_update;
            ZTimeInterval dtime = time - last_update;
            uint32_t millseconds = (uint32_t)duration_cast<milliseconds>(dtime).count();
            
            schedulable->run(millseconds);
            schedulable->_last_update = time;
        }
        
        ZTime loop_end_time = ZUtil::get_current_time();
        milliseconds loop_duration = duration_cast<milliseconds>(loop_end_time - loop_start_time);
        
        if (__fps_interval > loop_duration) {
            std::this_thread::sleep_for(__fps_interval - loop_duration);
        }
    }
}

ZGE_END_NAMESPACE
