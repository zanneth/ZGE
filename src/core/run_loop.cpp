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

BEGIN_ZGE_NAMESPACE

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
    
    while (_running) {
        std::vector<ZSchedulableRef> schedulables;
        
        {
            std::lock_guard<std::mutex> lock(_mutex);
            schedulables = _schedulables;
        }
        
        for (ZSchedulableRef schedulable : schedulables) {
            ZTime time = ZUtil::get_current_time();
            ZTime last_update = schedulable->_last_update;
            ZTimeInterval dtime = time - last_update;
            uint32_t millseconds = duration_cast<milliseconds>(dtime).count();
            
            schedulable->run(millseconds);
            schedulable->_last_update = time;
        }
        
        // sleep so we don't peg at 100%
        std::this_thread::sleep_for(milliseconds(1));
    }
}

END_ZGE_NAMESPACE
